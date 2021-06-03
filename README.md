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

## Even without going to each branch, we provide top-level make command that will compile different things.

## Fetch EPCC, NAS-NPB benchmark, and fetch RTK source code
Run from the top directory
```
make init
```

## Build Nautilus with EPCC benchmark
```
make BENCHMARK=EPCC build_nautilus
```

## Run the benchmark from within Nautilus (on QEMU)
```
make run_nautilus BENCHMARK=EPCC
```

To start things, use the following commands at the root-shell prompt:
```
root-shell> ompb
```

To test on a physical machine, write the nautilus_rtk/nautilus.iso to a CD or USB stick and boot the machine.   Alternatively, add nautilus_rtk/nautilus.bin to your grub configuration as described elsewhere, or PXE boot it.


## Build Nautilus with NAS-NPB benchmark

### NAS-NPB includes 8 sub-benchmarks including FT, BT, CG, EP, LU, SP, IS, MG, EP, use the following to build for FT as an example.
```
make BENCHMARK=NAS-NPB SUB-BENCHMARK=FT build_nautilus
```

## Run the benchmark from within Nautilus (on QEMU)
```
make run_nautilus BENCHMARK=NAS-NPB SUB-BENCHMARK=FT
```

To start things, use the following commands at the root-shell prompt:
```
root-shell> nas-ft
```
To change number of threads, for example to 16 threads, run following
```
root-shell> omp_num_threads 16
```

## Compile the benchmarks to run Linux

### NAS-NPB(NAS) benchmarks
To compile NAS benchmarks for Linux, run from the top directory with sub-benchmark and class set properly; You can choose from 8 sub-benchmarks (BT, LU, SP, IS, MG, FT, SP. EP) and CLASS from 4 scales (S, A, B, C). 
To build FT CLASS B for example, use the following
``` 
make build_linux_npb-nas  SUB-BENCHMARK=FT CLASS=B
```

To run NAS benchmarks just compiled, run following
```  
make run_linux_npb-nas  SUB-BENCHMARK=FT CLASS=B
```


### EPCC benchmarks
To compile EPCC benchmarks for Linux, run from the top directory the following. 
``` 
make build_linux_epcc
```

To run EPCC benchmarks just compiled, you should choose from 4 sub-benchmarks (syncbench, schedbench, taskbench, arraybench_59049)
To run arraybench_59049 for example, use following
```  
make run_linux_epcc  SUB-BENCHMARK=arraybench_59049
```

