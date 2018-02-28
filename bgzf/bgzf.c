#include "bgzf.h"
#include <stdint.h>
#include <zlib.h>

#define BLOCK_HEADER_LENGTH 18
#define BLOCK_FOOTER_LENGTH 8

static const uint8_t g_magic[19] = "\037\213\010\4\0\0\0\0\0\377\6\0\102\103\2\0\0\0";

static inline void packInt32(uint8_t *buffer, uint32_t value)
{
	buffer[0] = value;
	buffer[1] = value >> 8;
	buffer[2] = value >> 16;
	buffer[3] = value >> 24;
}

static inline void packInt16(uint8_t *buffer, uint16_t value)
{
	buffer[0] = (uint8_t)value;
	buffer[1] = (uint8_t)(value >> 8);
}

int bgzf_compress(const char* destination, const int destinationLen, const char* source, const int sourceLen, const int compressionLevel)
{
	uint32_t crc;
	z_stream zs;
	uint8_t *dst = (uint8_t*)destination;
	int numCompressedBytes;

	// compress the body
	zs.zalloc    = NULL;
	zs.zfree     = NULL;
	zs.msg       = NULL;
	zs.next_in   = (Bytef*)source;
	zs.avail_in  = sourceLen;
	zs.next_out  = dst + BLOCK_HEADER_LENGTH;
	zs.avail_out = destinationLen - BLOCK_HEADER_LENGTH - BLOCK_FOOTER_LENGTH;
	int ret      = deflateInit2(&zs, compressionLevel, Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY); // -15 to disable zlib header/footer

	if (ret != Z_OK) return -1;
	if ((ret = deflate(&zs, Z_FINISH)) != Z_STREAM_END) return -2;
	if ((ret = deflateEnd(&zs)) != Z_OK) return -3;

	numCompressedBytes = (int)zs.total_out + BLOCK_HEADER_LENGTH + BLOCK_FOOTER_LENGTH;

	// write the header
	memcpy(dst, g_magic, BLOCK_HEADER_LENGTH); // the last two bytes are a place holder for the length of the block
	packInt16(&dst[16], numCompressedBytes - 1); // write the compressed length; -1 to fit 2 bytes

	// write the footer
	crc = crc32(crc32(0L, NULL, 0L), (Bytef*)source, sourceLen);
	packInt32((uint8_t*)&dst[numCompressedBytes - 8], crc);
	packInt32((uint8_t*)&dst[numCompressedBytes - 4], sourceLen);

	return numCompressedBytes;
}

int bgzf_decompress(const char* destination, const int destinationLen, const char* source, const int sourceLen)
{
	z_stream zs;
	zs.zalloc    = NULL;
	zs.zfree     = NULL;
	zs.next_in   = (Bytef*)source + 18;
	zs.avail_in  = sourceLen - 16;
	zs.next_out  = (Bytef*)destination;
	zs.avail_out = destinationLen;

	if (inflateInit2(&zs, -15) != Z_OK) return -1;

	if (inflate(&zs, Z_FINISH) != Z_STREAM_END) {
		inflateEnd(&zs);
		return -2;
	}

	if (inflateEnd(&zs) != Z_OK) return -3;

	return (int)zs.total_out;
}