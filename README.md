## BlockCompression library

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
