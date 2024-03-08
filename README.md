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