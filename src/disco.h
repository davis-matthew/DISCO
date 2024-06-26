#ifndef DISCO_H
#define DISCO_H

#include "llvm/ADT/SmallSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Analysis/AliasSetTracker.h"
#include "llvm/Analysis/MemoryLocation.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/BasicAliasAnalysis.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Transforms/InstCombine/InstCombiner.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Pass.h"
#include "llvm/Analysis/LoopInfo.h"

#include <vector>
#include <unordered_set>

namespace llvm {

class Disco : public PassInfoMixin<Disco> {
  friend AnalysisInfoMixin<Disco>;
public:

  void insertStringSpellingChecks(Module &);

  PreservedAnalyses run(Module &, ModuleAnalysisManager &);
  static bool isRequired() { return true; }
};

}

#endif