#include "disco.h"

namespace llvm { 

PreservedAnalyses Disco::run(Module &M, ModuleAnalysisManager &MAM) {

  // generate global data structure (dictionary) from replacements.txt

  // find all instances of puts() or other print functions and stick a call to our function on top:
  
  
  /* 
    --> checkStringSpelling(s);
    puts(s);

  
  void checkStringSpelling(char* s){
    for key in globaldictionary:
      if s.lowercase().find(key.lowercase()) != string::npos:
        throw exception("Found Spelling Error! {s} -> {s.replace(key, globaldictionary[key])}");
  }
  */

  return PreservedAnalyses::all();
}

}