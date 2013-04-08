# Image Processing and Computer Vision Benchmarks #

## About ##
The benchmark is hosted at
[https://github.com/tue-es/benchmarks](https://github.com/tue-es/benchmarks)

The following web pages contain the up-to-date information of this benchmark:
*   [Overview](https://github.com/tue-es/benchmarks/wiki/overview "Overview")
*   [People](https://github.com/tue-es/benchmarks/wiki/people "People")
*   [License](https://github.com/tue-es/benchmarks/wiki/license "License")
*   [Download](https://github.com/tue-es/benchmarks/wiki/download "Download")
*   [Documentation](https://github.com/tue-es/benchmarks/wiki/documentation "Documentation")
*   [Publications](https://github.com/tue-es/benchmarks/wiki/publications "Publications")

## Prerequisite ##
This code has been tested under Linux, but is intended to be cross-platform. Additionally, cmake is used to configure the compilation script. In short, what you need is:
* Linux (or Linux-like) system
* cmake (version 2.6 or higher)

## Quick Start ##
For a quick start, below is a short description to compile and run the benchmark.

To obtain the source code, you can clone the repository or download and unzip the package. 
After that, you can go to the top directory of the source code (where the README locates) and execute the following command.

First, create a directory, say, a "build" directory, and generate a compilation script within that directory.
<pre>
mkdir build
cd build
cmake ..
</pre>
If no error is thrown out, then will be a "Makefile" generated within the build directory.

After that, in the build directory (when the Makefile is generated earlier), you can issue the following comamnd to compile the code and the run the tests.
<pre>
make
make run
</pre>

If the tests do not report error, you should be able to find the output within the directory of each kernel. For example, the output of the gaussian filter is
<pre>
build/kernels/gaussian5x5int/out.pgm
</pre>
