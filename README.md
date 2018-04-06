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

#### AVX, no PGO

Algorithm | CL | TotalTime | CompRatio |  CompSpeed | DecompSpeed | Speed% | Ratio% | SpRank | CrRank |
---------:|---:|----------:|----------:|-----------:|------------:|-------:|-------:|-------:|-------:|
Zlib      |  1 |    0.34 s |      2.93 | 202.9 MB/s |  393.2 MB/s |  1.000 |  1.000 |     26 |     33 |
Zlib      |  2 |    0.54 s |      4.04 | 106.5 MB/s |  406.7 MB/s |  0.631 |  1.379 |     28 |     30 |
Zlib      |  3 |    0.59 s |      4.32 |  93.7 MB/s |  445.3 MB/s |  0.579 |  1.473 |     29 |     29 |
Zlib      |  4 |    0.71 s |      4.55 |  75.2 MB/s |  453.7 MB/s |  0.482 |  1.553 |     31 |     27 |
Zlib      |  5 |    0.83 s |      4.49 |  61.8 MB/s |  460.2 MB/s |  0.407 |  1.530 |     32 |     28 |
Zlib      |  6 |    0.98 s |      4.55 |  51.4 MB/s |  476.4 MB/s |  0.347 |  1.554 |     35 |     26 |
Zlib      |  7 |    1.41 s |      4.85 |  34.7 MB/s |  474.7 MB/s |  0.241 |  1.654 |     38 |     23 |
Zlib      |  8 |    2.35 s |      4.92 |  20.2 MB/s |  479.2 MB/s |  0.145 |  1.679 |     41 |     21 |
Zlib      |  9 |    2.42 s |      4.92 |  19.5 MB/s |  475.8 MB/s |  0.140 |  1.679 |     42 |     20 |
Zstd      |  1 |    0.25 s |      4.81 | 257.2 MB/s |  644.7 MB/s |  1.374 |  1.642 |     22 |     24 |
Zstd      |  2 |    0.29 s |      4.76 | 217.6 MB/s |  540.7 MB/s |  1.160 |  1.623 |     23 |     25 |
Zstd      |  3 |    0.32 s |      4.91 | 195.2 MB/s |  541.0 MB/s |  1.072 |  1.674 |     25 |     22 |
Zstd      |  4 |    0.31 s |      4.93 | 201.5 MB/s |  558.1 MB/s |  1.106 |  1.682 |     24 |     19 |
Zstd      |  5 |    0.49 s |      4.94 | 113.8 MB/s |  528.6 MB/s |  0.700 |  1.686 |     27 |     18 |
Zstd      |  6 |    0.68 s |      5.22 |  75.9 MB/s |  596.5 MB/s |  0.503 |  1.780 |     30 |     17 |
Zstd      |  7 |    0.84 s |      5.38 |  59.2 MB/s |  620.5 MB/s |  0.404 |  1.835 |     33 |     16 |
Zstd      |  8 |    1.09 s |      5.51 |  44.7 MB/s |  641.9 MB/s |  0.313 |  1.879 |     36 |     15 |
Zstd      |  9 |    1.17 s |      5.55 |  41.3 MB/s |  652.4 MB/s |  0.290 |  1.894 |     37 |     14 |
Zstd      | 10 |    1.64 s |      5.65 |  28.9 MB/s |  666.9 MB/s |  0.207 |  1.926 |     39 |     13 |
Zstd      | 11 |    1.91 s |      5.67 |  24.6 MB/s |  660.5 MB/s |  0.178 |  1.933 |     40 |     12 |
Zstd      | 12 |    2.80 s |      5.75 |  16.6 MB/s |  667.7 MB/s |  0.121 |  1.962 |     43 |     11 |
Zstd      | 13 |    3.45 s |      5.80 |  13.5 MB/s |  683.3 MB/s |  0.099 |  1.978 |     44 |     10 |
Zstd      | 14 |    5.47 s |      5.88 |   8.4 MB/s |  695.9 MB/s |  0.062 |  2.007 |     45 |      9 |
Zstd      | 15 |    7.43 s |      6.07 |   6.2 MB/s |  729.6 MB/s |  0.046 |  2.072 |     46 |      8 |
Zstd      | 16 |    9.59 s |      6.56 |   4.8 MB/s |  742.7 MB/s |  0.035 |  2.236 |     47 |      7 |
Zstd      | 17 |   11.13 s |      6.58 |   4.1 MB/s |  736.7 MB/s |  0.031 |  2.245 |     48 |      6 |
Zstd      | 18 |   15.06 s |      6.91 |   3.0 MB/s |  780.5 MB/s |  0.023 |  2.358 |     49 |      5 |
Zstd      | 19 |   20.27 s |      7.02 |   2.2 MB/s |  778.8 MB/s |  0.017 |  2.396 |     50 |      4 |
Zstd      | 20 |   30.53 s |      7.26 |   1.5 MB/s |  641.1 MB/s |  0.011 |  2.476 |     51 |      3 |
Zstd      | 21 |   30.66 s |      7.26 |   1.5 MB/s |  627.3 MB/s |  0.011 |  2.476 |     52 |      2 |
Zstd      | 22 |   40.09 s |      7.26 |   1.1 MB/s |  632.1 MB/s |  0.008 |  2.476 |     53 |      1 |
QuickLZ   |  3 |    0.90 s |      3.77 |  53.2 MB/s | 1022.6 MB/s |  0.378 |  1.287 |     34 |     31 |
Snappy    |  1 |    0.18 s |      2.83 | 315.4 MB/s |  1.165 GB/s |  1.864 |  0.966 |     21 |     35 |
LZ4       |  1 |    0.13 s |      2.96 | 438.0 MB/s |  1.812 GB/s |  2.647 |  1.009 |     20 |     32 |
LZ4       |  2 |    0.12 s |      2.89 | 455.0 MB/s |  1.837 GB/s |  2.738 |  0.985 |     19 |     34 |
LZ4       |  3 |    0.12 s |      2.82 | 473.7 MB/s |  1.844 GB/s |  2.831 |  0.963 |     18 |     36 |
LZ4       |  4 |    0.12 s |      2.79 | 488.4 MB/s |  1.880 GB/s |  2.912 |  0.950 |     16 |     37 |
LZ4       |  5 |    0.12 s |      2.75 | 483.7 MB/s |  1.770 GB/s |  2.853 |  0.938 |     17 |     38 |
LZ4       |  6 |    0.12 s |      2.70 | 492.7 MB/s |  1.837 GB/s |  2.919 |  0.922 |     15 |     39 |
LZ4       |  7 |    0.12 s |      2.57 | 506.4 MB/s |  1.756 GB/s |  2.953 |  0.876 |     14 |     40 |
LZ4       |  8 |    0.11 s |      2.47 | 547.8 MB/s |  1.751 GB/s |  3.136 |  0.843 |     11 |     41 |
LZ4       |  9 |    0.11 s |      2.43 | 548.5 MB/s |  1.691 GB/s |  3.113 |  0.828 |     13 |     42 |
LZ4       | 10 |    0.11 s |      2.39 | 549.5 MB/s |  1.708 GB/s |  3.125 |  0.816 |     12 |     43 |
LZ4       | 11 |    0.10 s |      2.36 | 569.9 MB/s |  1.802 GB/s |  3.255 |  0.803 |     10 |     44 |
LZ4       | 12 |    0.10 s |      2.35 | 586.4 MB/s |  1.907 GB/s |  3.371 |  0.802 |      3 |     45 |
LZ4       | 13 |    0.10 s |      2.30 | 584.9 MB/s |  1.678 GB/s |  3.261 |  0.785 |      9 |     46 |
LZ4       | 14 |    0.10 s |      2.26 | 583.3 MB/s |  1.694 GB/s |  3.263 |  0.772 |      8 |     47 |
LZ4       | 15 |    0.10 s |      2.23 | 599.3 MB/s |  1.701 GB/s |  3.333 |  0.761 |      5 |     48 |
LZ4       | 16 |    0.10 s |      2.20 | 604.1 MB/s |  1.688 GB/s |  3.346 |  0.749 |      4 |     49 |
LZ4       | 17 |    0.10 s |      2.18 | 593.7 MB/s |  1.655 GB/s |  3.286 |  0.745 |      7 |     50 |
LZ4       | 18 |    0.10 s |      2.15 | 597.0 MB/s |  1.682 GB/s |  3.312 |  0.732 |      6 |     51 |
LZ4       | 19 |    0.10 s |      2.14 | 611.6 MB/s |  1.710 GB/s |  3.388 |  0.729 |      2 |     52 |
LZ4       | 20 |    0.10 s |      2.09 | 617.8 MB/s |  1.723 GB/s |  3.420 |  0.714 |      1 |     53 |

#### no AVX, no PGO

#### AVX & PGO
