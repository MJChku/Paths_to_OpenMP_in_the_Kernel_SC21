# Paths_to_OpenMP_in_the_Kernel_SC21
Repository contains mainly RTK approach in "Paths to OpenMP in the kernel" submitted to SuperComputing21; But also some code of PIK/CCK but instructions may not be updated on this repo;

For PIK ---> 

For CCK --->

# RTK(RunTime in Kernel)

This is the top-level git repository for the Run time in Kernel(RTK)

Different branches include different things we built described as below, and in README of different branch, detailed description on how to use and what to test is provided (except for PIK, CCK, which are supposed to appear on other repo)
 Branch  | content |
| ------------- | ------------- |
| OpenMP | OpenMP library source code, able to compile OpenMP library |
| LibOMP  | Compiled OpenMP library |
| RTK | Runtime in Kernel, and benchmarks run with kernel |
| EPCC | EPCC benchmarks source code for linux |
| NPB3.0-omp-c | NAS-NPB source code for linux |
| PIK | Process in kernel source |
| CCK | Custom Compilation in kernel, source code on Nautilus side |

## Alternatively, even without going to each branch, we provide top-level make command that will compile different things.

## Fetch EPCC, NAS Parallel Benchmarks (NPB), and RTK source code
Run from the top directory
```shell
make init
```

---

## Nautilus with EPCC Benchmarks

### Build Nautilus with EPCC Benchmarks

```shell
make BENCH-NAME=EPCC build_nautilus
```

### Run EPCC Benchmarks from within Nautilus (on QEMU)

```shell
make run_nautilus BENCH-NAME=EPCC
```

To start running benchmarks, use the following commands at the root-shell prompt:
```
root-shell> ompb
```

To test on a physical machine, write the nautilus_rtk/nautilus.iso to a CD or USB stick and boot the machine.   Alternatively, add nautilus_rtk/nautilus.bin to your grub configuration as described elsewhere, or PXE boot it.

---

## Nautilus with NAS Parallel Benchmarks (NPB)

### Build Nautilus with NPB

#### We included eight of NAParallel BenchmarkS Parallel Benchmarks (BT, FT, CG, EP, LU, MG, IS, SP) in RTK. FT is used as an example below:

To build Nautilus with one NAS Parallel Benchmark (e.g. FT), use the following command:

```shell
make build_nautilus BENCH-NAME=NAS BENCHMARK=FT 
```

### Run NPB from within Nautilus (on QEMU)
#### note, to quit from qemu, use "Alt+2", then type "quit"

```shell
make run_nautilus BENCH-NAME=NAS BENCHMARK=FT 
```

To start running that benchmark (e.g. FT), use the following commands at the root-shell prompt:
```
root-shell> nas-ft
```
To change the number of threads, for example to 16 threads, before running the test, run following:
```
root-shell> omp_num_threads 16
```

Or

```
root-shell> set-omp-num-threads 16
```

---



## Compile and Run Benchmarks on Linux

To compile the same test suite as RTK's:

```shell
make build_linux
```

This will compile BT, FT in B Class; CG, EP, MG, LU, IS, SP in C Class for NPB; this will also compile all the EPCC Benchmarks.

To run them all:

```shell
make run_linux
```

**WARNING: This would take hours to finish.** 

---

### EPCC benchmarks

To compile EPCC benchmarks for Linux:

``` sh
make build_linux_epcc
```

To run all the EPCC benchmarks:

```shell
make run_linux_epcc	
```



---

To run one of the EPCC benchmarks (syncbench, schedbench, taskbench, arraybench_59049), run the following:
(e.g. arraybench_59049)

```  shell
make run_linux_epcc BENCHMARK=arraybench_59049
```



---

### NAS Parallel Benchmarks (NPB)

To compile the same test suite as RTK/CCK's:

```shell
make build_linux_nas
```

To run this test suite:

```shell
make run_linux_nas
```

**WARNING: This would take hours to finish.** 

---

All available NAS Parallel Benchmarks include FT, CG, BT, LU, IS, EP, SP, MG available at 4 scales/classes (S, A, B, C)

To compile a specific NAS Parallel Benchmark (e.g. FT) with CLASS B, run following:

```sh
make build_linux_nas BENCHMARK=FT CLASS=B
```

To run a specific NAS Parallel Benchmark (e.g. FT) with CLASS B after build:

```sh
make run_linux_nas BENCHMARK=FT CLASS=B
```

---

If you want to compile a different test suite with different CLASSes from the test suite we are using for the paper, do the following:

```shell
vi linux_npb-nas/config/suite.def	
```

and uncomment the benchmarks you want to include in the test suite for Linux.

