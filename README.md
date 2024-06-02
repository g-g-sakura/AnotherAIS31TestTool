# AnotherAIS31TestTool
This tool provides tests specified by [BSI AIS 20 / AIS 31](https://www.bsi.bund.de/dok/ais-20-31-appx-2011).

As of today, [A proposal for: Functionality classes for random number generators - Version 2.35 - Draft](https://www.bsi.bund.de/SharedDocs/Downloads/EN/BSI/Certification/Interpretations/AIS_31_Functionality_classes_for_random_number_generators_e.pdf?__blob=publicationFile&v=7) is posted on BSI Web site, yet its final version is not yet released.
The specification of tests will be subject to change in its final version, so the implementation of tests T6 through T8 are suspended.

# Features
- Automatic report generation with graphs
  - Supports report generation capability, in XeLaTeX source file (see ```-x``` option), where relevant intermediate results are also contained to gain confidence and support characterization of input data (or of entropy source).
# Usage
```
.\AIS31TestTool.exe --inputT0 <file name for test T0> --inputT1 <initial file name for tests T1 through T5> [-w] [-x] [--MSb|--LSb]
```

- ```--inputT0``` specifies the file name of the input data.  The file path must be relative path to a binary file with at least 3145728 bits as per [BSI AIS 20 / AIS 31](https://www.bsi.bund.de/dok/ais-20-31-appx-2011).
- ```--inputT1``` specifies the initial file name of the input data of 257 sets for tests T1 through T5.  The file name must contain at least 3 digits which identifies the index of 257 sets, at the end.  The file path must be relative path to a binary file with at least 20000 bits as per [BSI AIS 20 / AIS 31](https://www.bsi.bund.de/dok/ais-20-31-appx-2011).
- ```-w``` specifies the number of bits per sample.  This shall be between 1-8, inclusive.  By default, this value is 8.
- ```-x``` requests to generate a XeLaTeX source file of entropy estimation report, in the same folder as the specified acquisition data (see ```--inputT0``` or ```--inputT1```).
- ```--MSb``` specifies the conversion from sample to bitstring in Most Significant bit first (**default**). 
- ```--LSb``` specifies the conversion from sample to bitstring in Least Significant bit first.

# Examples of test results
[test_report_sample_input_data_8-bit.pdf](https://github.com/g-g-sakura/AnotherAIS31TestTool/blob/main/tool_validation_evidence/test_report_sample_input_data_8-bit.pdf)

# System equirements for runtime environment
- OS : Windows 10 or newer with 64-bit
- RAM : 8GB or more main memory
- [TeX Live](https://www.tug.org/texlive/) (optional for compiling automatically generated XeLaTeX source file)

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
  - for array indexing, referencing subarray
