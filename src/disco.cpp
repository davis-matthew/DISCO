#include "disco.h"

namespace llvm { 

PreservedAnalyses Disco::run(Module &M, ModuleAnalysisManager &MAM){
  return PreservedAnalyses::all();
}

}