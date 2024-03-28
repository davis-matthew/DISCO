#include "disco.h"
#include <iostream>
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include <llvm/IR/PassManager.h>

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

  // // Insert call to atexit(printSpellcheckStats)
  // std::vector<Type*> spellCheckStatsParameters = {Type::getVoidTy(globalContext)};
  // FunctionType *spellCheckStatsFuncType = FunctionType::get(Type::getVoidTy(globalContext), spellCheckStatsParameters, false);
  // Function *spellCheckStatsFunc = cast<Function>(M.getOrInsertFunction(StringRef("printSpellcheckStats"), spellCheckStatsFuncType).getCallee());
  
  // std::vector<Type*> atExitParameters = {PointerType::getUnqual(spellCheckStatsFuncType)};
  // FunctionType *atExitFuncType = FunctionType::get(Type::getVoidTy(globalContext), atExitParameters, false);
  // Function *atExitFunc = cast<Function>(M.getOrInsertFunction(StringRef("atexit"), atExitFuncType).getCallee());

  // std::vector<Value*> atExitArgs;
  // atExitArgs.push_back(spellCheckStatsFunc);
  IRBuilder<> builder(globalContext);
  // builder.SetInsertPoint(&(*(M.getFunction(StringRef("main"))->begin()->begin()))); // Start of main
  // CallInst *atExitSpellCheckStats = builder.CreateCall(atExitFunc, atExitArgs);

  // // Insert call to checkStringSpelling above each puts() call
  std::unordered_set<std::string> outputFunctions = {
    "puts"
  };

  std::vector<Type*> spellCheckParameters = {Type::getInt8PtrTy(globalContext)};
  auto *spellCheckFuncType = FunctionType::get(Type::getVoidTy(globalContext), {Type::getInt8PtrTy(globalContext)}, false);
  auto *spellCheckFunc = cast<Function>(M.getOrInsertFunction("spellcheck_io", spellCheckFuncType).getCallee());

  for(Function &F : M)
  for(BasicBlock &BB : F)
  for(Instruction &I: BB)
    if(CallInst* call = dyn_cast<CallInst>(&I)) {
      StringRef calledFuncName = call->getCalledFunction()->getName();
      std::cout << calledFuncName.str() << "\n";
      if(outputFunctions.find(calledFuncName.str()) != outputFunctions.end()){
        builder.SetInsertPoint(&I);
        std::vector<Value*> spellCheckArgs;
        spellCheckArgs.push_back(call->getArgOperand(0));
        CallInst *spellCheck = builder.CreateCall(spellCheckFunc, spellCheckArgs);      }
    }

  return PreservedAnalyses::all();
}

}

llvm::PassPluginLibraryInfo getDiscoPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "Disco", LLVM_VERSION_STRING,
          [](llvm::PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](llvm::StringRef Name, llvm::ModulePassManager &MPM,
                   llvm::ArrayRef<llvm::PassBuilder::PipelineElement>) {
                  if (Name == "disco") {
                    MPM.addPass(llvm::Disco());
                    return true; 
                  }
                  return false;
                });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getDiscoPluginInfo();
}
