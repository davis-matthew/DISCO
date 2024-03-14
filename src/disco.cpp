#include "disco.h"

namespace llvm {

/*
Find all instances of puts() or other print functions and stick a call to our function on top:
   
--> checkStringSpelling(s);
    puts(s);
  
    // PSEUDOCODE
    void checkStringSpelling(char* s){
      for key in globaldictionary:
        if s.lowercase().find(key.lowercase()) != string::npos:
          throw exception("Found Spelling Error! {s} -> {s.replace(key, globaldictionary[key])}");
    }
*/

PreservedAnalyses Disco::run(Module &M, ModuleAnalysisManager &MAM) {
  LLVMContext &globalContext = M.getContext();

  // Insert call to atexit(printSpellcheckStats)
  std::vector<Type*> spellCheckStatsParameters = {Type::getVoidTy(globalContext)};
  FunctionType *spellCheckStatsFuncType = FunctionType::get(Type::getVoidType(globalContext), spellCheckStatsParameters, false);
  Function *spellCheckStatsFunc = cast<Function>(M.getOrInsertFunction("printSpellcheckStats"), spellCheckStatsFuncType).getCallee();
  
  std::vector<Type*> atExitParameters = {PointerType::getUnqual(spellCheckStatsFuncType)};
  FunctionType *atExitFuncType = FunctionType::get(Type::getVoidType(globalContext), atExitParameters, false);
  Function *atExitFunc = cast<Function>(M.getOrInsertFunction("atexit"), atExitFuncType).getCallee();

  CallInst *atExitSpellCheckStats = CallInst::Create(atExitFunc, spellCheckStatsFunc, 
                                      M.getOrInsertFunction("main").begin().begin()); // Start of main

  // Insert call to checkStringSpelling above each puts() call
  std::unordered_set<std::string> outputFunctions = ({
    "@puts"
  });

  std::vector<Type*> spellCheckParameters = {Type::getInt8PtrTy(globalContext)};
  FunctionType *spellCheckFuncType = FunctionType::get(Type::getVoidTy(globalContext), spellCheckParameters, false);
  Function *spellCheckFunc = cast<Function>(M.getOrInsertFunction("checkStringSpelling", spellCheckFuncType).getCallee());

  for(Function &F : M)
  for(BasicBlock &BB : F)
  for(Instruction &I: BB)
    if(CallInst* call = dyn_cast<CallInst>(&I)) {
      StringRef calledFuncName = call->getCalledFunction()->getName();
      if(outputFunctions.find(calledFuncName.str()) != container.end())
        CallInst *spellCheck = CallInst::Create(spellCheckFunc, call->getArgOperand(0), I);
    }

  return PreservedAnalyses::all();
}

}