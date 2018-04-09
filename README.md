# BlockCompression library

This library contains high-performance versions of the following compression algorithms:

* zlib-ng
* QuickLZ (level 3)
* Zstd
* snappy
* lz4

## Building

### Windows (Windows 10)

Compile using BlockCompression.sln in Visual Studio 2017

### Linux (Ubuntu 17.10)

```
make -j
```

### Mac OS X (High Sierra)

```
make -j -f Makefile.MacOSX
```

## Benchmarking

* Intel Core i7-2600K CPU @ 3.40GHz
* Ubuntu 17.10
* using Mother.vcf

### Zlib

This library is 103.5% faster than the system zlib library for compression level 1. For the remaining
compression levels, it's an average of 12.8% (range: 1.5% - 27.1%) faster than the system zlib library. 

Decompression is an average of 22.3% (range: 15.4% - 26.5%) faster than the system zlib library. 

### Insights

Enabling AVX auto-vectorization did little to improve performance and in the case of Zstd and LZ4, it
actually hurt performance.

Profile-guided optimization (PGO) improved decompression speed by an average of 6.28% (range: -1.5% - 15.5%).
PGO has a slightly detrimental effect on compression speed by and average of -0.95% (range: -6.7% - 6.7%).

We also evaluated PGO code produced by Clang/LLVM and gcc/g++. gcc produced slightly faster code.

### Benchmark

Native optimization (no AVX), PGO, using SIMD improvements for Zlib

Algorithm | CL | TotalTime | CompRatio |  CompSpeed | DecompSpeed | Speed% | Ratio% | SpRank | CrRank |
---------:|---:|----------:|----------:|-----------:|------------:|-------:|-------:|-------:|-------:|
Zlib      |  1 |    2.53 s |      2.94 | 199.2 MB/s |  433.1 MB/s |  1.000 |  1.000 |     26 |     33 |
Zlib      |  2 |    4.02 s |      4.06 | 105.7 MB/s |  455.0 MB/s |  0.629 |  1.379 |     28 |     30 |
Zlib      |  3 |    4.40 s |      4.34 |  93.0 MB/s |  492.2 MB/s |  0.573 |  1.473 |     29 |     29 |
Zlib      |  4 |    5.19 s |      4.58 |  76.8 MB/s |  493.8 MB/s |  0.487 |  1.554 |     31 |     27 |
Zlib      |  5 |    6.22 s |      4.51 |  62.4 MB/s |  499.2 MB/s |  0.406 |  1.532 |     33 |     28 |
Zlib      |  6 |    7.30 s |      4.58 |  52.0 MB/s |  513.7 MB/s |  0.346 |  1.555 |     35 |     26 |
Zlib      |  7 |   10.75 s |      4.88 |  34.2 MB/s |  521.8 MB/s |  0.235 |  1.656 |     38 |     23 |
Zlib      |  8 |   17.72 s |      4.95 |  20.2 MB/s |  524.4 MB/s |  0.143 |  1.681 |     41 |     21 |
Zlib      |  9 |   18.26 s |      4.95 |  19.6 MB/s |  521.6 MB/s |  0.138 |  1.681 |     42 |     20 |
Zstd      |  1 |    1.72 s |      4.84 | 273.8 MB/s |  742.4 MB/s |  1.466 |  1.644 |     22 |     24 |
Zstd      |  2 |    1.99 s |      4.78 | 233.8 MB/s |  669.3 MB/s |  1.270 |  1.624 |     23 |     25 |
Zstd      |  3 |    2.12 s |      4.94 | 212.5 MB/s |  695.8 MB/s |  1.193 |  1.676 |     24 |     22 |
Zstd      |  4 |    2.12 s |      4.96 | 212.5 MB/s |  694.8 MB/s |  1.193 |  1.684 |     25 |     19 |
Zstd      |  5 |    3.32 s |      4.97 | 122.7 MB/s |  669.8 MB/s |  0.760 |  1.688 |     27 |     18 |
Zstd      |  6 |    4.70 s |      5.25 |  81.3 MB/s |  742.2 MB/s |  0.537 |  1.783 |     30 |     17 |
Zstd      |  7 |    5.98 s |      5.41 |  62.2 MB/s |  789.1 MB/s |  0.423 |  1.838 |     32 |     16 |
Zstd      |  8 |    7.82 s |      5.54 |  46.6 MB/s |  807.5 MB/s |  0.323 |  1.882 |     36 |     15 |
Zstd      |  9 |    8.42 s |      5.59 |  43.0 MB/s |  828.5 MB/s |  0.300 |  1.897 |     37 |     14 |
Zstd      | 10 |   12.06 s |      5.68 |  29.6 MB/s |  852.6 MB/s |  0.210 |  1.930 |     39 |     13 |
Zstd      | 11 |   14.11 s |      5.70 |  25.2 MB/s |  837.5 MB/s |  0.179 |  1.937 |     40 |     12 |
Zstd      | 12 |   20.85 s |      5.79 |  16.9 MB/s |  847.6 MB/s |  0.121 |  1.966 |     43 |     11 |
Zstd      | 13 |   25.78 s |      5.83 |  13.6 MB/s |  858.7 MB/s |  0.098 |  1.981 |     44 |     10 |
Zstd      | 14 |   41.08 s |      5.92 |   8.5 MB/s |  865.4 MB/s |  0.061 |  2.010 |     45 |      9 |
Zstd      | 15 |   55.16 s |      6.12 |   6.3 MB/s |  910.6 MB/s |  0.046 |  2.077 |     46 |      8 |
Zstd      | 16 |  1.18 min |      6.60 |   4.9 MB/s |  901.8 MB/s |  0.036 |  2.242 |     47 |      7 |
Zstd      | 17 |  1.37 min |      6.63 |   4.2 MB/s |  888.8 MB/s |  0.031 |  2.251 |     48 |      6 |
Zstd      | 18 |  1.87 min |      6.96 |   3.1 MB/s |  956.5 MB/s |  0.022 |  2.365 |     49 |      5 |
Zstd      | 19 |  2.51 min |      7.07 |   2.3 MB/s |  925.4 MB/s |  0.017 |  2.402 |     50 |      4 |
Zstd      | 20 |  3.68 min |      7.32 |   1.6 MB/s |  715.9 MB/s |  0.011 |  2.486 |     51 |      3 |
Zstd      | 21 |  3.69 min |      7.32 |   1.6 MB/s |  715.6 MB/s |  0.011 |  2.486 |     52 |      2 |
Zstd      | 22 |  4.78 min |      7.32 |   1.2 MB/s |  715.2 MB/s |  0.009 |  2.486 |     53 |      1 |
QuickLZ   |  3 |    6.97 s |      3.80 |  51.8 MB/s |  1.062 GB/s |  0.362 |  1.289 |     34 |     31 |
Snappy    |  1 |    1.35 s |      2.84 | 321.9 MB/s |  1.218 GB/s |  1.875 |  0.966 |     21 |     35 |
LZ4       |  1 |    0.94 s |      2.98 | 436.6 MB/s |  2.274 GB/s |  2.695 |  1.010 |     20 |     32 |
LZ4       |  2 |    0.89 s |      2.90 | 460.7 MB/s |  2.375 GB/s |  2.839 |  0.986 |     19 |     34 |
LZ4       |  3 |    0.87 s |      2.84 | 475.8 MB/s |  2.356 GB/s |  2.912 |  0.964 |     18 |     36 |
LZ4       |  4 |    0.85 s |      2.80 | 483.3 MB/s |  2.433 GB/s |  2.966 |  0.952 |     16 |     37 |
LZ4       |  5 |    0.86 s |      2.76 | 481.0 MB/s |  2.318 GB/s |  2.931 |  0.939 |     17 |     38 |
LZ4       |  6 |    0.84 s |      2.72 | 491.2 MB/s |  2.434 GB/s |  3.007 |  0.923 |     15 |     39 |
LZ4       |  7 |    0.83 s |      2.58 | 502.7 MB/s |  2.346 GB/s |  3.047 |  0.877 |     14 |     40 |
LZ4       |  8 |    0.82 s |      2.49 | 511.7 MB/s |  2.290 GB/s |  3.078 |  0.845 |     12 |     41 |
LZ4       |  9 |    0.82 s |      2.44 | 513.5 MB/s |  2.241 GB/s |  3.075 |  0.830 |     13 |     42 |
LZ4       | 10 |    0.81 s |      2.41 | 522.9 MB/s |  2.282 GB/s |  3.131 |  0.819 |     11 |     43 |
LZ4       | 11 |    0.78 s |      2.37 | 538.1 MB/s |  2.370 GB/s |  3.228 |  0.806 |     10 |     44 |
LZ4       | 12 |    0.76 s |      2.37 | 553.2 MB/s |  2.431 GB/s |  3.316 |  0.804 |      8 |     45 |
LZ4       | 13 |    0.76 s |      2.32 | 567.3 MB/s |  2.235 GB/s |  3.331 |  0.787 |      6 |     46 |
LZ4       | 14 |    0.76 s |      2.28 | 564.2 MB/s |  2.252 GB/s |  3.322 |  0.774 |      7 |     47 |
LZ4       | 15 |    0.77 s |      2.25 | 559.7 MB/s |  2.186 GB/s |  3.281 |  0.763 |      9 |     48 |
LZ4       | 16 |    0.75 s |      2.21 | 576.6 MB/s |  2.189 GB/s |  3.361 |  0.750 |      4 |     49 |
LZ4       | 17 |    0.76 s |      2.20 | 571.0 MB/s |  2.185 GB/s |  3.334 |  0.746 |      5 |     50 |
LZ4       | 18 |    0.74 s |      2.16 | 585.7 MB/s |  2.223 GB/s |  3.414 |  0.732 |      3 |     51 |
LZ4       | 19 |    0.73 s |      2.15 | 596.6 MB/s |  2.245 GB/s |  3.471 |  0.730 |      2 |     52 |
LZ4       | 20 |    0.72 s |      2.11 | 601.3 MB/s |  2.270 GB/s |  3.501 |  0.716 |      1 |     53 |
