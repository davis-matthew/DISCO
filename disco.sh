#!/bin/bash

# Pass in .bc or .ll as first argument

HOME=$PWD
INSTALLDIR="../llvm-project/build/install/"

# Setup LLVM (from llvmsetup script)
export ORIGINAL_PATH=${PATH}
export ORIGINAL_LIBRARY_PATH=${LIBRARY_PATH}
export ORIGINAL_LD_LIBRARY_PATH=${LD_LIBRARY_PATH}

export PATH="${INSTALLDIR}bin:${PATH}"
#export LIBRARY_PATH="/home/lyu/Software/llvm-install/${BRANCH}/lib:/home/lyu/Software/llvm-install/${BRANCH}/lib/x86_64-unknown-linux-gnu${ORIGINAL_LIBRARY_PATH:+:${ORIGINAL_LIBRARY_PATH}}"
export LD_LIBRARY_PATH="${INSTALLDIR}lib:${INSTALLDIR}lib/x86_64-unknown-linux-gnu${ORIGINAL_LD_LIBRARY_PATH:+:${ORIGINAL_LD_LIBRARY_PATH}}"
export TSAN_OPTIONS='ignore_noninstrumented_modules=1 log_path=ArbalestReport.txt'

# Build
if [ ! -d "$HOME/build" ]; then
    mkdir $HOME/build
fi
cd $HOME/build && make -j12

# Run Pass on .ll
cd $HOME && ./script/run_pass.sh $1