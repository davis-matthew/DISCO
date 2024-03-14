#!/bin/bash
set -e

function usage() {
  local name='run_pass.sh'
  echo "Run all passes to analyze and transform the specified IR"
  echo "USAGE: ${name} ${IR}"
  echo ""
}

CURR=$(readlink -f "$0")
ROOT=$(dirname "$CURR")
PLUGIN="${ROOT}/../build/src/libDISCO.so"
PASS="disco"
if [ $# -lt 1 ]; then
  usage
  exit 1
fi

TRANS="${1}-transformed.bc"
TRANS_LL="${1}-transformed.ll"
ORIG_LL="${1}"


#opt --passes=licm "${ORIG_LL}" -o "${ORIG_LL}" # If we need to run any passes first


opt -load-pass-plugin "${PLUGIN}" --passes=${PASS} "${ORIG_LL}" -o "${TRANS}" # Run disco


llvm-dis ${TRANS} -o ${TRANS_LL}
echo ""
echo "Successfully transformed the LLVM IR"
echo "Output:"
echo "Transformed LLVM IR:                            ${TRANS}"
echo "Transformed LLVM IR in human-readable format:   ${TRANS_LL}"
echo "Original LLVM IR in human-readable format:      ${ORIG_LL}"