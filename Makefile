BENCHMARK = NAS-NPB
SUB-BENCHMARK = FT  # list of supported binaries
sub-bench = `echo $(SUB-BENCHMARK) | tr A-Z a-z`
CLASS=C

init: prepare_gitrepo  Nautilus_rtk linux_epcc  linux_npb-nas


prepare_gitrepo:

	git clone https://github.com/MJChku/Paths_to_OpenMP_in_the_Kernel_SC21/ all_in_one

Nautilus_rtk:

	cp -r all_in_one nautilus_rtk;

	cd nautilus_rtk; git checkout RTK;

	cd nautilus_rtk; cp configs/rtk.config .config


build_nautilus:
	cd nautilus_rtk; cp configs/rtk.config .config
ifeq ($(BENCHMARK),EPCC)
	cd nautilus_rtk; cd ./src/test/openmp/; rm BENCHMARK; ln -sf openmpbench_C_v31/ BENCHMARK
else
	cd nautilus_rtk; cd ./src/test/openmp/; rm BENCHMARK; ln -sf NPB-NAS/  BENCHMARK
	cd nautilus_rtk; cd ./src/test/openmp/NPB-NAS/; rm SUB-BENCHMARK; ln -sf $(SUB-BENCHMARK) SUB-BENCHMARK
endif
	cd nautilus_rtk && make clean && make isoimage

run_nautilus: 

ifeq ($(BENCHMARK),EPCC)
	@echo "At the root-shell> prompt"
	@echo "type ompb to launch EPCC\n"
	@echo "For example: \n"
	@echo "root-shell> ompb \n"
	@sleep 10
else

	@echo "At the root-shell> prompt"
	@echo "omp_num_threads N  to set the number of threads to use\n"
	@echo "For example: \n"
	@echo "root-shell> omp_num_threads 16 \n"
	@echo "nas-$(sub-bench) test to run the test of $(BENCHMARK) $(SUB-BENCHMARK)\n"
	@echo "For example: \n"
	@echo "root-shell> nas-$(sub-bench) \n"
	@sleep 10
endif

	@cd nautilus_rtk; ./run


linux_epcc:

	cp -r all_in_one linux_epcc;

	cd linux_epcc; git checkout EPCC;


build_linux_epcc:
	
	cd linux_epcc; make clean; make

run_linux_epcc:

	@echo "If error happens, comply to the following"
	@echo "set SUB-BENCHMARK to be one of arraybench_59049 synchbench schedbench taskbench"
	@sleep 5
	cd linux_epcc; ./$(SUB-BENCHMARK)


linux_npb-nas:

	cp -r all_in_one linux_npb-nas;
	cd linux_npb-nas; git checkout NPB3.0-omp-c;

build_linux_npb-nas:

	@echo "If error happens, comply to the following"
	@echo "set SUB-BENCHMARK to be one of FT BT CG MG LU SP EP IS" 
	@echo "set CLASS to be B or C"
	@sleep 5

	cd linux_npb-nas; make clean; make $(SUB-BENCHMARK) CLASS=$(CLASS);


run_linux_npb-nas:

	cd linux_npb-nas/bin; ./$(sub-bench).$(CLASS)



clean:
	-rm -rf nautilus_rtk linux_npb-nas linux_epcc all_in_one

.PHONY: clean

