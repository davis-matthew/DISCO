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

  std::unordered_set<std::string> outputFunctions = ({
    "@puts"
  });

  LLVMContext &globalContext = M.getContext();

  std::vector<Type*> parameters = {Type::getInt8PtrTy(globalContext)};
  FunctionType *spellCheckFuncType = FunctionType::get(Type::getVoidTy(M.getContext()), parameters, false);
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