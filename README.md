# EPCC OpenMP micro-benchmark suite

These microbenchmarks are intended to measure the overheads of synchronisation, loop scheduling and array operations in the OpenMP runtime library.

For full introduction of EPCC see [epcc-openmp-micro-benchmark-suite](https://www.epcc.ed.ac.uk/research/computing/performance-characterisation-and-benchmarking/epcc-openmp-micro-benchmark-suite)

This is intended to run on Linux, to provide fair comparison to Nautilus, we supply a libomp library compiled with Nautilus compilation flags. And linux_libomp.a can be downloaded [here](https://github.com/MJChku/Paths_to_OpenMP_in_the_Kernel_SC21/tree/LibOMP)

1. Before run make; Point in the Makefile.defs where `libomp.a` resides by change the line start with `LIBS` to  `LIBS= <path-to-linux-libomp.a>/linux_libomp.a -lm -lpthread -ldl`

1. Then `make` and run any benchmarks compiled.

Also see [README.txt](https://github.com/MJChku/Paths_to_OpenMP_in_the_Kernel_SC21/blob/EPCC/README.txt) for original readme of EPCC.
