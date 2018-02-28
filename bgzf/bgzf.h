#pragma once

int bgzf_compress(const char* destination, const int destinationLen, const char* source, const int sourceLen, const int compressionLevel);
int bgzf_decompress(const char* destination, const int destinationLen, const char* source, const int sourceLen);