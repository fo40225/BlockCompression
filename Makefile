# define our object and binary directories
TOP_DIR=$(PWD)
OBJ_DIR=obj
BIN_DIR=bin

# define our directories
BENCHMARK_DIR=RunBenchmark
BGZF_DIR=bgzf
UTILITIES_DIR=utilities
ZLIB_DIR=zlib-ng
ZSTD_DIR=zstd

# define our include directories
BENCHMARK_INCLUDE=-I $(TOP_DIR)/$(BENCHMARK_DIR)
BGZF_INCLUDE=-I $(TOP_DIR)/$(BGZF_DIR) -I $(TOP_DIR)/$(ZLIB_DIR)
UTILITIES_INCLUDE=-I $(TOP_DIR)/$(UTILITIES_DIR)
ZLIB_INCLUDE=-I $(TOP_DIR)/$(ZLIB_DIR) -I  $(TOP_DIR)/$(ZLIB_DIR)/arch/x86
ZSTD_INCLUDE=-I $(TOP_DIR)/$(ZSTD_DIR)/lib -I $(TOP_DIR)/$(ZSTD_DIR)/lib/common -I $(TOP_DIR)/$(ZSTD_DIR)/lib/decompress -I $(TOP_DIR)/$(ZSTD_DIR)/lib/compress
BENCHMARK_INCLUDE=-I $(TOP_DIR)/$(BENCHMARK_DIR) $(BGZF_INCLUDE) $(UTILITIES_INCLUDE) $(ZLIB_INCLUDE) $(ZSTD_INCLUDE)

# defines
ZLIB_DEFINES=-D ZLIB_COMPAT -D HAVE_BUILTIN_CTZL -D MEDIUM_STRATEGY -D X86_64 -D X86_NOCHECK_SSE2 -D UNALIGNED_OK -D UNROLL_LESS -D X86_CPUID -D X86_SSE2_FILL_WINDOW -D X86_SSE4_2_CRC_HASH -D X86_PCLMULQDQ_CRC -D X86_QUICK_STRATEGY -D ZLIB_DLL
ZSTD_DEFINES=-D ZSTD_LEGACY_SUPPORT=0 -D ZSTD_MULTITHREAD

# define our output library
SHAREDLIB=libBlockCompression.so

# define our output program
RUNBENCHMARK=$(BIN_DIR)/RunBenchmark
LIBS=-L$(TOP_DIR)/$(BIN_DIR) -Wl,-rpath,$(TOP_DIR)/$(BIN_DIR) -lBlockCompression

# define some default flags
CC=gcc
CPP=g++
CFLAGS=-O3 -fPIC
CPPFLAGS=-std=c++11
MARCH=-march=native
LDFLAGS=-Wl,-Bstatic -static-libgcc -Wl,-Bdynamic
LDSHARED=gcc -shared -Wl,-soname,$(SHAREDLIB),--version-script,BlockCompression.map

# define our source files
BGZF_SOURCES=$(BGZF_DIR)/bgzf.c
BGZF_OBJS=$(addprefix obj/,$(notdir $(BGZF_SOURCES:.c=.o)))

UTILITIES_SOURCES=$(UTILITIES_DIR)/get_library_id.c
UTILITIES_OBJS=$(addprefix obj/,$(notdir $(UTILITIES_SOURCES:.c=.o)))

ZLIB_SOURCES=$(ZLIB_DIR)/adler32.c $(ZLIB_DIR)/compress.c $(ZLIB_DIR)/crc32.c $(ZLIB_DIR)/deflate.c $(ZLIB_DIR)/deflate_fast.c $(ZLIB_DIR)/deflate_medium.c $(ZLIB_DIR)/deflate_slow.c $(ZLIB_DIR)/functable.c $(ZLIB_DIR)/infback.c $(ZLIB_DIR)/inffast.c $(ZLIB_DIR)/inflate.c $(ZLIB_DIR)/inftrees.c $(ZLIB_DIR)/match.c $(ZLIB_DIR)/trees.c $(ZLIB_DIR)/uncompr.c $(ZLIB_DIR)/zutil.c $(ZLIB_DIR)/arch/x86/x86.c $(ZLIB_DIR)/arch/x86/crc_folding.c $(ZLIB_DIR)/arch/x86/crc_pclmulqdq.c $(ZLIB_DIR)/arch/x86/deflate_quick.c $(ZLIB_DIR)/arch/x86/fill_window_sse.c $(ZLIB_DIR)/arch/x86/insert_string_sse.c
ZLIB_OBJS=$(addprefix obj/,$(notdir $(ZLIB_SOURCES:.c=.o)))

ZSTD_SOURCES=$(ZSTD_DIR)/lib/common/entropy_common.c $(ZSTD_DIR)/lib/common/error_private.c $(ZSTD_DIR)/lib/common/fse_decompress.c $(ZSTD_DIR)/lib/common/pool.c $(ZSTD_DIR)/lib/common/threading.c $(ZSTD_DIR)/lib/common/zstd_common.c $(ZSTD_DIR)/lib/compress/fse_compress.c $(ZSTD_DIR)/lib/compress/huf_compress.c $(ZSTD_DIR)/lib/compress/zstdmt_compress.c $(ZSTD_DIR)/lib/compress/zstd_compress.c $(ZSTD_DIR)/lib/compress/zstd_double_fast.c $(ZSTD_DIR)/lib/compress/zstd_fast.c $(ZSTD_DIR)/lib/compress/zstd_lazy.c $(ZSTD_DIR)/lib/compress/zstd_ldm.c $(ZSTD_DIR)/lib/compress/zstd_opt.c $(ZSTD_DIR)/lib/decompress/huf_decompress.c $(ZSTD_DIR)/lib/decompress/zstd_decompress.c
ZSTD_OBJS=$(addprefix obj/,$(notdir $(ZSTD_SOURCES:.c=.o)))

BENCHMARK_SOURCES=$(BENCHMARK_DIR)/Benchmark.cpp $(BENCHMARK_DIR)/BenchmarkStatistics.cpp $(BENCHMARK_DIR)/CompressionData.cpp  $(BENCHMARK_DIR)/MemoryUtilities.cpp $(BENCHMARK_DIR)/RunBenchmark.cpp $(BENCHMARK_DIR)/Runner.cpp $(BENCHMARK_DIR)/ZlibNextGen.cpp $(BENCHMARK_DIR)/Zstandard.cpp $(BENCHMARK_DIR)/ZstandardDict.cpp
BENCHMARK_OBJS=$(addprefix obj/,$(notdir $(BENCHMARK_SOURCES:.cpp=.o)))

all: $(SHAREDLIB) $(RUNBENCHMARK)
	@true

clean:
	@-rm -f $(SHAREDLIB) $(OBJS)

$(SHAREDLIB): $(BGZF_OBJS) $(UTILITIES_OBJS) $(ZLIB_OBJS) $(ZSTD_OBJS)
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	@test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	@echo "- creating the shared library"
	@$(LDSHARED) $(CFLAGS) $(DEFINES) -o bin/$@ $(BGZF_OBJS) $(UTILITIES_OBJS) $(ZLIB_OBJS) $(ZSTD_OBJS) -lc $(LDFLAGS)

$(RUNBENCHMARK): $(SHAREDLIB) $(BENCHMARK_OBJS)
	@echo "- creating RunBenchmark"
	@$(CPP) $(CFLAGS) $(CPPFLAGS) $(MARCH) $(BENCHMARK_INCLUDE) -o $(RUNBENCHMARK) $(BENCHMARK_OBJS) $(LIBS) -lstdc++ -lm -lpthread

obj/%.o : $(BGZF_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "- compiling" $(*F).c
	@$(CC) $(CFLAGS) $(MARCH) $(BGZF_INCLUDE) -c $< -o $@

obj/%.o : $(UTILITIES_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "- compiling" $(*F).c
	@$(CC) $(CFLAGS) $(MARCH) $(UTILITIES_INCLUDE) -c $< -o $@

obj/%.o : $(ZSTD_DIR)/lib/common/%.c
	@mkdir -p $(dir $@)
	@echo "- compiling" $(*F).c
	@$(CC) $(CFLAGS) $(MARCH) $(ZSTD_INCLUDE) $(ZSTD_DEFINES) -c $< -o $@

obj/%.o : $(ZSTD_DIR)/lib/compress/%.c
	@mkdir -p $(dir $@)
	@echo "- compiling" $(*F).c
	@$(CC) $(CFLAGS) $(MARCH) $(ZSTD_INCLUDE) $(ZSTD_DEFINES) -c $< -o $@

obj/%.o : $(ZSTD_DIR)/lib/decompress/%.c
	@mkdir -p $(dir $@)
	@echo "- compiling" $(*F).c
	@$(CC) $(CFLAGS) $(MARCH) $(ZSTD_INCLUDE) $(ZSTD_DEFINES) -c $< -o $@

obj/%.o : $(ZLIB_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "- compiling" $(*F).c
	@$(CC) $(CFLAGS) $(MARCH) $(ZLIB_INCLUDE) $(ZLIB_DEFINES) -c $< -o $@

obj/%.o : $(ZLIB_DIR)/arch/x86/%.c
	@mkdir -p $(dir $@)
	@echo "- compiling" $(*F).c
	@$(CC) $(CFLAGS) $(MARCH) $(ZLIB_INCLUDE) $(ZLIB_DEFINES) -c $< -o $@

obj/crc_folding.o : $(ZLIB_DIR)/arch/x86/crc_folding.c
	@mkdir -p $(dir $@)
	@echo "- compiling" $(*F).c
	@$(CC) $(CFLAGS) -mpclmul -msse4 $(ZLIB_INCLUDE) $(ZLIB_DEFINES) -c $< -o $@

obj/%.o : $(BENCHMARK_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "- compiling" $(*F).cpp
	@$(CPP) $(CFLAGS) $(CPPFLAGS) $(MARCH) $(BENCHMARK_INCLUDE) -c $< -o $@
