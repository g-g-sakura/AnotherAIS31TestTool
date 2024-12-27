# AnotherAIS31TestTool
This tool provides tests based on [A Proposal for Functionality Classes for Random Number Generators - Version 3.0](https://www.bsi.bund.de/SharedDocs/Downloads/EN/BSI/Certification/Interpretations/AIS_31_Functionality_classes_for_random_number_generators_e_2024.pdf?__blob=publicationFile&v=3), which provides the cryptographic basis for BSI AIS 20 / AIS 31.
### Test tool supporting AIS 20 / 31 version 2011
Please refer to [version 1 branch](https://github.com/g-g-sakura/AnotherAIS31TestTool/tree/version1).

### To Do
debugging

# Features
- Automatic report generation with graphs
  - Supports report generation capability, in XeLaTeX source file (see ```-x``` option), where relevant intermediate results are also contained to gain confidence and support characterization of input data (or of entropy source).
# Usage
```
.\AIS31TestTool.exe --input <file name for tests through T4> [-w <number of bits per sample>] [-x] [--MSb|--LSb]
```

- ```--input``` specifies the file name of the input data.  The file path must be relative path to a binary file with at least 4,080,000 bits. In order to support max 2 trials, the value is twice the specified value by [A Proposal for Functionality Classes for Random Number Generators - Version 3.0](https://www.bsi.bund.de/SharedDocs/Downloads/EN/BSI/Certification/Interpretations/AIS_31_Functionality_classes_for_random_number_generators_e_2024.pdf?__blob=publicationFile&v=3).
- ```-w``` specifies the number of bits per sample.  This shall be between 1-8, inclusive.  By default, this value is 8.
- ```-x``` requests to generate a XeLaTeX source file of entropy estimation report, in the same folder as the specified acquisition data (see ```--input```).
- ```--MSb``` specifies the conversion from sample to bitstring in Most Significant bit first (**default**). 
- ```--LSb``` specifies the conversion from sample to bitstring in Least Significant bit first.

# Examples of test results
[test_report_v3_sample_input_data_for_T1-T4.pdf](https://github.com/g-g-sakura/AnotherAIS31TestTool/blob/AIS20_31_Version3_2024/tool_validation_evidence/test_report_v3_sample_input_data_for_T1-T4.pdf)

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
