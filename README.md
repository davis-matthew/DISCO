# DISCO: Dependent-type Inspection for String Correctness On-the-fly

We propose DISCO, a dependently typed string and runtime LLVM compiler pass that detects string formatting issues, such as typos. Our approach can be extended to ensure form fields such as emails, phone numbers, passwords, dates, etc. are valid based on universal formatting conventions. Whenever a string deviates from the expected pattern, the runtime will identify this as a mismatch. This helps reduce usability issues arising from cultural variations in input and output validation. More details can be found in the [paper](https://github.com/davis-matthew/DISCO/blob/main/assets/final-report.pdf).

![image](https://raw.githubusercontent.com/davis-matthew/DISCO/main/assets/logic.png)
![image](https://raw.githubusercontent.com/davis-matthew/DISCO/main/assets/results.png)

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

Create human-readable LLVM from a test file and run pass on it: 
```bash
clang -emit-llvm -S test.c -o test.ll
./test.sh test.ll
```

Add Spellchecking to Binary: 
```bash
clang++ test.ll-transformed.bc external/spellcheck.cpp external/dictionary.cpp -o transformed-binary
./transformed-binary
```

Run Binary:
```bash
./transformed-binary
```
