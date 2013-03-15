# Image Processing and Computer Vision Benchmarks #
The following web pages contains the up-to-date information of this benchmark:
*   [Overview](https://github.com/tue-es/benchmarks/wiki/overview "Overview")
*   [License](https://github.com/tue-es/benchmarks/wiki/license "License")
*   [Download](https://github.com/tue-es/benchmarks/wiki/download "Download")
*   [Documentation](https://github.com/tue-es/benchmarks/wiki/documentation "Documentation")
*   [Publications](https://github.com/tue-es/benchmarks/wiki/publications "Publications")

For a quick start, below is a short description to compile and run the benchmark.

To obtain the source code, you can clone the repository or download and unzip the package. 
After that, you can go to the top directory of the source code (where the README locates) and execute the following command.

First, create a directory, say, a "build" directory, and generate a compilation script within that directory.
<pre>
mkdir build
cd build
cmake ..
</pre>

After that, you can compile the code and the run some tests by the commands below.
<pre>
make
make run-kernel
</pre>

If the tests do not report error, you should be able to find the output within the directory of each kernel. For example, the output of the gaussian filter is
<pre>
benchmarks/build/kernels/gaussian5x5int/out.pgm
</pre>
