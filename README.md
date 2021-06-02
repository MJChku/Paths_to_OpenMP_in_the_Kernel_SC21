# OpenMP 

### This branch describes how to compile OpenMP library statically. The source code is cloned from [llvm/openmp](https://github.com/llvm/llvm-project/tree/main/openmp)

1. `mkdir build` to create `build` dicrectory  

1. `bash run.sh` to build openmp library, the libomp.a will be in `build/runtime/src/`

### For Nautilus and Linux
The source code need to be changed slightly to compile for Nautilus or Linux, the only modificatoin is in `runtime/src/kmp_environment.cpp`.
The code segment to find is 
```
//IF you compile for nautilus, enable below;
#define environ (nk_environ())
extern "C"{
extern char **nk_environ(void);
}

//IF you compile for linux, enable below;
extern char **environ;
```
Basically, enable different `environ` definition for Nautilus or Linux; and run `run.sh` 

The compiled libomp.a is in branch **LibOMP**.

* For Nautilus use:
```
//IF you compile for nautilus, enable below;
#define environ (nk_environ())
extern "C"{
extern char **nk_environ(void);
}

//IF you compile for linux, enable below;
//extern char **environ;
```

* For Linux use:
```
//IF you compile for nautilus, enable below;
/*
#define environ (nk_environ())
extern "C"{
extern char **nk_environ(void);
}
*/

//IF you compile for linux, enable below;
extern char **environ;
```


