#!/bin/bash
set -e

function usage() {
  local name='run_pass_and_compile.sh'
  echo "Run all passes to analyze and transform the specified IR"
  echo "USAGE: ${name} ${IR}"
  echo ""
}

CURR=$(readlink -f "$0")
ROOT=$(dirname "$CURR")
PLUGIN="${ROOT}/../install/libInstrumentationReduction.so"
PASS="function(loop-rotate),instrumentation-reduction"
if [ $# -lt 1 ]; then
  usage
  exit 1
fi

TRANS="${1}-transformed.bc"
TRANS_LL="${1}-transformed.ll"
ORIG_LL="${1}"
echo "==============================Transform LLVM IR========================================"
echo "opt -load-pass-plugin \"${PLUGIN}\" --passes=${PASS}"
#-debug-pass-manager
opt --passes=licm "${ORIG_LL}" -o "${ORIG_LL}" #run licm first
opt -load-pass-plugin "${PLUGIN}" --passes=${PASS} "${ORIG_LL}" -o "${TRANS}"
#gdb --args opt -load-pass-plugin "${PLUGIN}" --passes=${PASS} "${ORIG_LL}" -o "${TRANS}"
echo "=========================Generate Human-Readable Format================================"
echo "llvm-dis ${TRANS} -o ${TRANS_LL}"
llvm-dis ${TRANS} -o ${TRANS_LL}
echo ""
echo "Successfully transformed the LLVM IR"
echo "Output:"
echo "Transformed LLVM IR:                            ${TRANS}"
echo "Transformed LLVM IR in human-readable format:   ${TRANS_LL}"
echo "Original LLVM IR in human-readable format:      ${ORIG_LL}"