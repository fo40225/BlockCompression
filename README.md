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
Zlib      |  1 |    2.59 s |      2.94 | 201.5 MB/s |  393.2 MB/s |  1.000 |  1.000 |     26 |     33 |
Zlib      |  2 |    4.00 s |      4.06 | 108.4 MB/s |  420.4 MB/s |  0.647 |  1.379 |     28 |     30 |
Zlib      |  3 |    4.44 s |      4.34 |  93.8 MB/s |  451.1 MB/s |  0.583 |  1.473 |     29 |     29 |
Zlib      |  4 |    5.33 s |      4.58 |  75.2 MB/s |  459.2 MB/s |  0.485 |  1.554 |     31 |     27 |
Zlib      |  5 |    6.27 s |      4.51 |  62.3 MB/s |  470.6 MB/s |  0.413 |  1.532 |     32 |     28 |
Zlib      |  6 |    7.40 s |      4.58 |  51.6 MB/s |  479.6 MB/s |  0.350 |  1.555 |     35 |     26 |
Zlib      |  7 |   10.64 s |      4.88 |  34.7 MB/s |  479.5 MB/s |  0.243 |  1.656 |     38 |     23 |
Zlib      |  8 |   17.62 s |      4.95 |  20.4 MB/s |  485.8 MB/s |  0.147 |  1.681 |     41 |     21 |
Zlib      |  9 |   18.30 s |      4.95 |  19.6 MB/s |  482.5 MB/s |  0.141 |  1.681 |     42 |     20 |
Zstd      |  1 |    1.82 s |      4.84 | 266.4 MB/s |  651.9 MB/s |  1.420 |  1.644 |     22 |     24 |
Zstd      |  2 |    2.17 s |      4.78 | 223.8 MB/s |  549.5 MB/s |  1.194 |  1.624 |     23 |     25 |
Zstd      |  3 |    2.34 s |      4.94 | 201.5 MB/s |  551.5 MB/s |  1.108 |  1.676 |     25 |     22 |
Zstd      |  4 |    2.32 s |      4.96 | 202.2 MB/s |  558.1 MB/s |  1.114 |  1.684 |     24 |     19 |
Zstd      |  5 |    3.67 s |      4.97 | 113.9 MB/s |  533.3 MB/s |  0.704 |  1.688 |     27 |     18 |
Zstd      |  6 |    5.09 s |      5.25 |  76.2 MB/s |  601.6 MB/s |  0.508 |  1.783 |     30 |     17 |
Zstd      |  7 |    6.37 s |      5.41 |  59.2 MB/s |  621.3 MB/s |  0.406 |  1.838 |     33 |     16 |
Zstd      |  8 |    8.16 s |      5.54 |  45.1 MB/s |  657.6 MB/s |  0.317 |  1.882 |     36 |     15 |
Zstd      |  9 |    8.74 s |      5.59 |  42.0 MB/s |  650.7 MB/s |  0.296 |  1.897 |     37 |     14 |
Zstd      | 10 |   12.31 s |      5.68 |  29.2 MB/s |  665.4 MB/s |  0.210 |  1.930 |     39 |     13 |
Zstd      | 11 |   14.38 s |      5.70 |  24.8 MB/s |  670.8 MB/s |  0.180 |  1.937 |     40 |     12 |
Zstd      | 12 |   21.01 s |      5.79 |  16.8 MB/s |  674.0 MB/s |  0.123 |  1.966 |     43 |     11 |
Zstd      | 13 |   25.92 s |      5.83 |  13.6 MB/s |  676.5 MB/s |  0.100 |  1.981 |     44 |     10 |
Zstd      | 14 |   41.19 s |      5.92 |   8.5 MB/s |  697.8 MB/s |  0.063 |  2.010 |     45 |      9 |
Zstd      | 15 |   56.15 s |      6.12 |   6.2 MB/s |  735.2 MB/s |  0.046 |  2.077 |     46 |      8 |
Zstd      | 16 |  1.20 min |      6.60 |   4.8 MB/s |  743.3 MB/s |  0.036 |  2.242 |     47 |      7 |
Zstd      | 17 |  1.40 min |      6.63 |   4.1 MB/s |  741.2 MB/s |  0.031 |  2.251 |     48 |      6 |
Zstd      | 18 |  1.90 min |      6.96 |   3.0 MB/s |  783.8 MB/s |  0.023 |  2.365 |     49 |      5 |
Zstd      | 19 |  2.54 min |      7.07 |   2.3 MB/s |  780.0 MB/s |  0.017 |  2.402 |     50 |      4 |
Zstd      | 20 |  3.78 min |      7.32 |   1.5 MB/s |  636.7 MB/s |  0.011 |  2.486 |     51 |      3 |
Zstd      | 21 |  3.81 min |      7.32 |   1.5 MB/s |  634.8 MB/s |  0.011 |  2.486 |     52 |      2 |
Zstd      | 22 |  4.91 min |      7.32 |   1.2 MB/s |  641.4 MB/s |  0.009 |  2.486 |     53 |      1 |
QuickLZ   |  3 |    6.95 s |      3.80 |  52.2 MB/s | 1012.4 MB/s |  0.372 |  1.289 |     34 |     31 |
Snappy    |  1 |    1.39 s |      2.84 | 314.3 MB/s |  1.160 GB/s |  1.866 |  0.966 |     21 |     35 |
LZ4       |  1 |    0.96 s |      2.98 | 444.0 MB/s |  1.861 GB/s |  2.703 |  1.010 |     20 |     32 |
LZ4       |  2 |    0.93 s |      2.90 | 459.6 MB/s |  1.860 GB/s |  2.779 |  0.986 |     19 |     34 |
LZ4       |  3 |    0.91 s |      2.84 | 475.4 MB/s |  1.836 GB/s |  2.848 |  0.964 |     18 |     36 |
LZ4       |  4 |    0.89 s |      2.80 | 487.0 MB/s |  1.849 GB/s |  2.908 |  0.952 |     17 |     37 |
LZ4       |  5 |    0.88 s |      2.76 | 493.6 MB/s |  1.802 GB/s |  2.923 |  0.939 |     16 |     38 |
LZ4       |  6 |    0.86 s |      2.72 | 505.8 MB/s |  1.898 GB/s |  3.013 |  0.923 |     15 |     39 |
LZ4       |  7 |    0.85 s |      2.58 | 522.5 MB/s |  1.802 GB/s |  3.057 |  0.877 |     14 |     40 |
LZ4       |  8 |    0.84 s |      2.49 | 532.6 MB/s |  1.710 GB/s |  3.065 |  0.845 |     13 |     41 |
LZ4       |  9 |    0.84 s |      2.44 | 539.2 MB/s |  1.682 GB/s |  3.083 |  0.830 |     12 |     42 |
LZ4       | 10 |    0.82 s |      2.41 | 550.0 MB/s |  1.699 GB/s |  3.137 |  0.819 |     11 |     43 |
LZ4       | 11 |    0.81 s |      2.37 | 559.3 MB/s |  1.768 GB/s |  3.207 |  0.806 |     10 |     44 |
LZ4       | 12 |    0.78 s |      2.37 | 572.7 MB/s |  1.851 GB/s |  3.301 |  0.804 |      8 |     45 |
LZ4       | 13 |    0.78 s |      2.32 | 587.8 MB/s |  1.706 GB/s |  3.301 |  0.787 |      7 |     46 |
LZ4       | 14 |    0.78 s |      2.28 | 588.2 MB/s |  1.722 GB/s |  3.311 |  0.774 |      6 |     47 |
LZ4       | 15 |    0.78 s |      2.25 | 595.3 MB/s |  1.686 GB/s |  3.323 |  0.763 |      4 |     48 |
LZ4       | 16 |    0.78 s |      2.21 | 596.9 MB/s |  1.658 GB/s |  3.315 |  0.750 |      5 |     49 |
LZ4       | 17 |    0.78 s |      2.20 | 592.8 MB/s |  1.655 GB/s |  3.296 |  0.746 |      9 |     50 |
LZ4       | 18 |    0.77 s |      2.16 | 604.0 MB/s |  1.679 GB/s |  3.355 |  0.732 |      2 |     51 |
LZ4       | 19 |    0.77 s |      2.15 | 605.9 MB/s |  1.691 GB/s |  3.369 |  0.730 |      1 |     52 |
LZ4       | 20 |    0.77 s |      2.11 | 600.4 MB/s |  1.698 GB/s |  3.349 |  0.716 |      3 |     53 |

#### no AVX, no PGO

Algorithm | CL | TotalTime | CompRatio |  CompSpeed | DecompSpeed | Speed% | Ratio% | SpRank | CrRank |
---------:|---:|----------:|----------:|-----------:|------------:|-------:|-------:|-------:|-------:|
Zlib      |  1 |    2.62 s |      2.94 | 201.7 MB/s |  380.0 MB/s |  1.000 |  1.000 |     26 |     33 |
Zlib      |  2 |    4.07 s |      4.06 | 107.1 MB/s |  402.3 MB/s |  0.642 |  1.379 |     28 |     30 |
Zlib      |  3 |    4.51 s |      4.34 |  92.7 MB/s |  434.0 MB/s |  0.580 |  1.473 |     29 |     29 |
Zlib      |  4 |    5.36 s |      4.58 |  75.5 MB/s |  434.5 MB/s |  0.488 |  1.554 |     31 |     27 |
Zlib      |  5 |    6.30 s |      4.51 |  62.3 MB/s |  450.4 MB/s |  0.415 |  1.532 |     33 |     28 |
Zlib      |  6 |    7.41 s |      4.58 |  51.9 MB/s |  452.2 MB/s |  0.353 |  1.555 |     35 |     26 |
Zlib      |  7 |   10.63 s |      4.88 |  34.9 MB/s |  457.9 MB/s |  0.246 |  1.656 |     38 |     23 |
Zlib      |  8 |   17.61 s |      4.95 |  20.4 MB/s |  460.3 MB/s |  0.149 |  1.681 |     41 |     21 |
Zlib      |  9 |   18.17 s |      4.95 |  19.8 MB/s |  462.1 MB/s |  0.144 |  1.681 |     42 |     20 |
Zstd      |  1 |    1.74 s |      4.84 | 275.5 MB/s |  708.4 MB/s |  1.505 |  1.644 |     22 |     24 |
Zstd      |  2 |    2.03 s |      4.78 | 231.5 MB/s |  635.6 MB/s |  1.288 |  1.624 |     23 |     25 |
Zstd      |  3 |    2.15 s |      4.94 | 211.4 MB/s |  667.6 MB/s |  1.219 |  1.676 |     24 |     22 |
Zstd      |  4 |    2.15 s |      4.96 | 211.8 MB/s |  661.0 MB/s |  1.218 |  1.684 |     25 |     19 |
Zstd      |  5 |    3.50 s |      4.97 | 116.7 MB/s |  634.8 MB/s |  0.748 |  1.688 |     27 |     18 |
Zstd      |  6 |    4.84 s |      5.25 |  79.0 MB/s |  720.7 MB/s |  0.541 |  1.783 |     30 |     17 |
Zstd      |  7 |    6.18 s |      5.41 |  60.3 MB/s |  743.6 MB/s |  0.423 |  1.838 |     32 |     16 |
Zstd      |  8 |    8.01 s |      5.54 |  45.6 MB/s |  773.2 MB/s |  0.327 |  1.882 |     36 |     15 |
Zstd      |  9 |    8.55 s |      5.59 |  42.5 MB/s |  779.8 MB/s |  0.306 |  1.897 |     37 |     14 |
Zstd      | 10 |   12.20 s |      5.68 |  29.3 MB/s |  801.3 MB/s |  0.214 |  1.930 |     39 |     13 |
Zstd      | 11 |   14.26 s |      5.70 |  24.9 MB/s |  805.0 MB/s |  0.184 |  1.937 |     40 |     12 |
Zstd      | 12 |   20.95 s |      5.79 |  16.8 MB/s |  815.1 MB/s |  0.125 |  1.966 |     43 |     11 |
Zstd      | 13 |   25.73 s |      5.83 |  13.6 MB/s |  817.1 MB/s |  0.102 |  1.981 |     44 |     10 |
Zstd      | 14 |   40.93 s |      5.92 |   8.5 MB/s |  833.6 MB/s |  0.064 |  2.010 |     45 |      9 |
Zstd      | 15 |   55.46 s |      6.12 |   6.3 MB/s |  884.8 MB/s |  0.047 |  2.077 |     46 |      8 |
Zstd      | 16 |  1.19 min |      6.60 |   4.9 MB/s |  887.9 MB/s |  0.037 |  2.242 |     47 |      7 |
Zstd      | 17 |  1.40 min |      6.63 |   4.1 MB/s |  868.6 MB/s |  0.031 |  2.251 |     48 |      6 |
Zstd      | 18 |  1.88 min |      6.96 |   3.1 MB/s |  927.7 MB/s |  0.023 |  2.365 |     49 |      5 |
Zstd      | 19 |  2.52 min |      7.07 |   2.3 MB/s |  928.5 MB/s |  0.017 |  2.402 |     50 |      4 |
Zstd      | 20 |  3.71 min |      7.32 |   1.6 MB/s |  719.7 MB/s |  0.012 |  2.486 |     51 |      3 |
Zstd      | 21 |  3.72 min |      7.32 |   1.5 MB/s |  726.2 MB/s |  0.012 |  2.486 |     52 |      2 |
Zstd      | 22 |  4.84 min |      7.32 |   1.2 MB/s |  716.3 MB/s |  0.009 |  2.486 |     53 |      1 |
QuickLZ   |  3 |    6.98 s |      3.80 |  51.9 MB/s |  983.1 MB/s |  0.375 |  1.289 |     34 |     31 |
Snappy    |  1 |    1.41 s |      2.84 | 309.0 MB/s |  1.148 GB/s |  1.857 |  0.966 |     21 |     35 |
LZ4       |  1 |    0.94 s |      2.98 | 441.9 MB/s |  2.169 GB/s |  2.798 |  1.010 |     20 |     32 |
LZ4       |  2 |    0.89 s |      2.90 | 466.0 MB/s |  2.218 GB/s |  2.935 |  0.986 |     19 |     34 |
LZ4       |  3 |    0.87 s |      2.84 | 478.7 MB/s |  2.218 GB/s |  3.001 |  0.964 |     18 |     36 |
LZ4       |  4 |    0.85 s |      2.80 | 490.4 MB/s |  2.249 GB/s |  3.069 |  0.952 |     17 |     37 |
LZ4       |  5 |    0.84 s |      2.76 | 502.4 MB/s |  2.214 GB/s |  3.122 |  0.939 |     16 |     38 |
LZ4       |  6 |    0.82 s |      2.72 | 514.4 MB/s |  2.288 GB/s |  3.201 |  0.923 |     15 |     39 |
LZ4       |  7 |    0.81 s |      2.58 | 525.7 MB/s |  2.226 GB/s |  3.243 |  0.877 |     14 |     40 |
LZ4       |  8 |    0.79 s |      2.49 | 546.7 MB/s |  2.172 GB/s |  3.331 |  0.845 |     13 |     41 |
LZ4       |  9 |    0.78 s |      2.44 | 550.2 MB/s |  2.127 GB/s |  3.334 |  0.830 |     12 |     42 |
LZ4       | 10 |    0.78 s |      2.41 | 554.2 MB/s |  2.146 GB/s |  3.359 |  0.819 |     11 |     43 |
LZ4       | 11 |    0.77 s |      2.37 | 560.7 MB/s |  2.213 GB/s |  3.412 |  0.806 |     10 |     44 |
LZ4       | 12 |    0.73 s |      2.37 | 586.0 MB/s |  2.340 GB/s |  3.574 |  0.804 |      5 |     45 |
LZ4       | 13 |    0.75 s |      2.32 | 586.5 MB/s |  2.129 GB/s |  3.508 |  0.787 |      9 |     46 |
LZ4       | 14 |    0.74 s |      2.28 | 594.2 MB/s |  2.168 GB/s |  3.558 |  0.774 |      6 |     47 |
LZ4       | 15 |    0.74 s |      2.25 | 594.9 MB/s |  2.109 GB/s |  3.540 |  0.763 |      7 |     48 |
LZ4       | 16 |    0.74 s |      2.21 | 596.6 MB/s |  2.082 GB/s |  3.538 |  0.750 |      8 |     49 |
LZ4       | 17 |    0.73 s |      2.20 | 603.4 MB/s |  2.097 GB/s |  3.575 |  0.746 |      4 |     50 |
LZ4       | 18 |    0.72 s |      2.16 | 612.1 MB/s |  2.093 GB/s |  3.614 |  0.732 |      2 |     51 |
LZ4       | 19 |    0.73 s |      2.15 | 608.0 MB/s |  2.106 GB/s |  3.600 |  0.730 |      3 |     52 |
LZ4       | 20 |    0.72 s |      2.11 | 611.3 MB/s |  2.137 GB/s |  3.627 |  0.716 |      1 |     53 |

#### no AVX & PGO
