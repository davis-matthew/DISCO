#include "disco.h"

namespace llvm { 

PreservedAnalyses Disco::run(Module &M, ModuleAnalysisManager &MAM) {

  // generate global data structure (dictionary) from replacements.txt

  // wrap puts() or other print functions with something like:
  
  /* 
  void newPuts(char* s){
    checkStringSpelling(s);
    puts(s);
  }
  void checkStringSpelling(char* s){
    for key in globaldictionary:
      if s.lowercase().find(key.lowercase()) != string::npos:
        throw exception("Found Spelling Error! {s} -> {s.replace(key, globaldictionary[key])}");
  }
  */

  return PreservedAnalyses::all();
}

}