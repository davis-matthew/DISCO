cmake_minimum_required(VERSION 3.18)
project(InstrumentationReduction)

set(CMAKE_CXX_STANDARD 14)

#this doesn't work :( using -DLLVM_ROOT instead
#cmake -DLLVM_ROOT=~/AIR/llvm-project/build/lib/cmake/llvm -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Debug -B build -S . -G Ninja
#set(LLVM_ROOT ../llvm-project/build) #set location to CMAKEFiles path 

find_package(LLVM 15 REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

add_subdirectory(src)