# BlockCompression library

This library contains high-performance versions of the following compression algorithms:

* zlib-ng
* Zstd

## Building

### Windows (Windows 10)

Compile using BlockCompression.sln in Visual Studio 2019

### Linux (Ubuntu 18.04)

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

We also evaluated PGO code produced by Clang/LLVM and gcc/g++. gcc produced 1.8% faster code for compression
and 6.6% faster code for decompression.

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
