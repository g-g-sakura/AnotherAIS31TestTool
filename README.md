# AnotherAIS31TestTool


# Usage
```
.\AIS31TestTool.exe --inputT0 <file name for test T0> --inputT1 <initial file name for tests T1 through T5> [-w] [-x] [--MSb|--LSb]
```

- ```--inputT0``` specifies the file name of the input data.  The file path must be relative path to a binary file with at least 3145728 bits as per [BSI AIS 20 / AIS 31](https://www.bsi.bund.de/dok/ais-20-31-appx-2011).
- ```--inputT1``` specifies the initial file name of the input data of 257 sets for tests T1 through T5.  The file name must contain at least 3 digits which identifies the index of 257 sets, at the end.  The file path must be relative path to a binary file with at least 20000 bits as per [BSI AIS 20 / AIS 31](https://www.bsi.bund.de/dok/ais-20-31-appx-2011).
- ```-w``` specifies the number of bits per sample.  This shall be between 1-8, inclusive.  By default, this value is 8.
- ```-x``` requests to generate a XeLaTeX source file of entropy estimation report, in the same folder as the specified acquisition data (see ```-f```).
- ```--MSb``` specifies the conversion from sample to bitstring in Most Significant bit first (**default**). 
- ```--LSb``` specifies the conversion from sample to bitstring in Least Significant bit first.

# System equirements for runtime environment
- OS : Windows 10 or newer with 64-bit
- RAM : 8GB or more main memory

# System requirements for development environment
## Compiler
Visual Studio 2019 or newer, or Intel oneAPI compiler

## Prerequisite libraries
- [Boost C++ libraries](https://www.boost.org/)
  - Boost.Filesystem for manipulation of file path.
  - Boost.Histogram for autocorrelation test.
  - Boost.Multi-Index for disjointness test.
  - Boost.Program Options for parsing command line options.
- [Blitz++ library](https://github.com/blitzpp/blitz)
  - for array indexing, referencing subarray, and for perform array reductions (e.g. mean, sum) briefly
