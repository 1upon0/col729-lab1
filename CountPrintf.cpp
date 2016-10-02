#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

#include <iostream>

using namespace llvm;
using namespace std;
namespace {

struct CntPrintf : public FunctionPass{
    static char ID;
    CntPrintf() : FunctionPass(ID) {}
    bool runOnFunction(Function &F) override {
    	  int count = 0;
		    for(Function::iterator it_f = F.begin(); it_f != F.end() ; ++it_f){
		      BasicBlock& b = *it_f;
		      for(BasicBlock::iterator it_b = b.begin(); it_b != b.end(); ++it_b){
				    CallInst *si = dyn_cast<CallInst>(&*it_b);
		        if(si != NULL){
		        	Function *called_f = si->getCalledFunction();
		        	if(called_f != NULL){
		        		if(called_f->getName().str().compare("printf")==0)count++;
		        	}
		        }
		      }
		    }
				errs().write_escaped(F.getName())<<":\nPrintf(): "<<count<<" calls\n";
        return false;
    }
};
}
char CntPrintf::ID = 0;
static RegisterPass<CntPrintf> X("cntPrintf", "Counts printf() calls for each fn", false, false);
