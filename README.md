# RTK `RunTime in Kernel`

#### This branch provides detailed description of how to configure/compile/run "Runtime in Kernel" approach in the paper.

1. Checkout **LibOMP** branch to download compiled openmp runtime libraries (**libomp.a**)([Shortcut link here](https://github.com/MJChku/Paths_to_OpenMP_in_the_Kernel_SC21/tree/LibOMP) ). 

1. Pull the main branch and checkout to RTK (this is the one).

1. Copy nautilus kernel config by ```cp ./configs/rtk.config .config```

1. Create folder called openmp/lib/ by ```mkdir openmp/lib/```; and put **libomp.a** downloaded under `openmp/lib/`

1. Finally to build Nautilus kernel, in root folder of this repo, do `make isoimage -j` (-j to enable parallelism)
  * Now for a simple test, you can run it in qemu with *nautilus.iso* by
  ```
qemu-system-x86_64 --enable-kvm -cpu host -smp 4,cores=4 -m 8G -curses -serial file:serial1.out -serial file:serial2.out -vga std -cdrom nautilus.iso -gdb tcp::1234
  ```
 *--enable-kvm* is an option.

  * To run on bare metal, under linux system, in grub.cfg create an option to boot nautilus, and put *nautilus.bin* under `/boot/`. 
For example in `grub.cfg` add :  
  ```
menuentry "Nautilus" {
  multiboot2 /boot/nautilus.bin
  boot
}
  ```
  Then reboot, and select `Nautilus` at boot menu.


#### Now you can start to build kernel with its benchmarks

* For EPCC benchmarks ([description see here](https://github.com/MJChku/Paths_to_OpenMP_in_the_Kernel_SC21/tree/EPCC))
  
  1. In *src/test/openmp/Makefile*. Add `obj-y += openmpbench_C_v31/`, comment out `obj-y +=  NPB-NAS/`

  1. In root folder of this repo, do `make isoimage -j` (-j to enable parallelism) again.
  
  1. Test in either qemu or bare metal, after kernel boots, type `ompb` and this will launch EPCC benchmarks.
  
* For NPB-NAS benchmarks ([description see here](https://github.com/MJChku/Paths_to_OpenMP_in_the_Kernel_SC21/tree/NPB3.0-omp-c))
  
  1. In *src/test/openmp/Makefile*. Add `obj-y += NPB-NAS/`, comment out `obj-y +=  openmpbench_C_v31/`
  
  1. NPB-NAS benchmark is slightly more complicated than EPCC, NPB-NAS includes 8 sub-benchmarks include *CG, LU, IS, FT, MG, EP, BT, SP*, some of them conflict with 
  each other, so they can't be compiled together. A save approach is to add `obj-y += <sub-BENCH>` in `src/test/openmp/NPB-NAS/Makefile`; replace `<sub-BENCH>` with either of the eight, and comment out all other 7 sub-benchmarks.
  To run it, type `nas-<sub-BENCH-in-lowercase>` after kernel boots; For example, to compile `LU`, add `obj-y += LU` and comment out all other 7 in Makefile, and type `nas-lu` (lower case) after kernel starts.

  1. In root folder of this repo, do `make isoimage -j` (-j to enable parallelism) again.
  
  1. Test in either qemu or bare metal, after kernel boots, type `nas-<sub-BENCH-in-lowercase>` and this will launch EPCC benchmarks.
  
  1. To change  number of cores/threads the benchmark runs with, type `omp_num_threads <thread_number>` to change threads before run benchmarks.
  
  
  
    
  
  
  
  
  




