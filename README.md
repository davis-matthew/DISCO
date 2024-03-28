# DISCO:


## Setup:
```bash
#  build llvm
cd llvm-project
mkdir build && cd build
cmake \
    -DLLVM_TARGETS_TO_BUILD="X86" \
    -DCMAKE_CXX_STANDARD="17" \
    -DLLVM_INCLUDE_EXAMPLES=OFF \
    -DLLVM_INCLUDE_TESTS=OFF \
    -DLLVM_INCLUDE_BENCHMARKS=OFF \
    -DLLVM_APPEND_VC_REV=OFF \
    -DLLVM_OPTIMIZED_TABLEGEN=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=install \
    -DLLVM_ENABLE_PROJECTS='clang' \
    -G Ninja \
    ../llvm
cmake --build . --parallel
cmake --build . --target install

# build pass
mkdir build && cd build
cmake ../
make
```

for mac use:
```cmake .. -Dzstd_INCLUDE_DIR="path" -Dzstd_LIBRARY="path"```

## Usage:
Setup LLVM in environment:
```bash
source ./env.sh
```
Create LLVM IR w/ Static C & C++ Standard Libraries:
```bash
clang++ -stdlib=libc++ -c -emit-llvm file.cpp
```
Add Spellchecking to Binary: 
```bash
clang transformed.bc spellcheck_map.c spellcheck.c
```