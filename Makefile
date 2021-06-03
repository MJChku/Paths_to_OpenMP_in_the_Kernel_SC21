BENCHMARK = NAS-NPB
SUB-BENCHMARK = FT  # list of supported binaries
sub-bench = `echo $(SUB-BENCHMARK) | tr A-Z a-z`

init: Nautilus_rtk


Nautilus_rtk:
	git clone https://github.com/MJChku/Paths_to_OpenMP_in_the_Kernel_SC21/ nautilus_rtk
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

clean:
	-rm -rf nautilus_rtk

.PHONY: clean

