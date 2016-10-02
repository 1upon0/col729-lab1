#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CFG.h"
#include <iostream>
#include <set>
#include <map>
using namespace llvm;
using namespace std;
namespace {

struct LivenessHist : public FunctionPass{
    static char ID;
    LivenessHist() :FunctionPass(ID) {}
    map<BasicBlock*, set<Value*> > live_in, live_out, gen, kill;
    void get_genkill(BasicBlock *blk, set<Value*> &gen, set<Value*> &kill){
    }
    bool update_live(BasicBlock *blk){
        map<BasicBlock*, set<Value*> >::iterator out_it = live_out.find(blk);
        
        if(out_it == live_out.end())
            live_out[blk] = set<Value*>();
        set<Value*> &out = live_out[blk];
        bool changed = false;

        for(BasicBlock::iterator succ_it = succ_begin(blk); succ_it != succ_end(blk); succ_it++){
            BasicBlock *succ = succ_it;
            map<BasicBlock*, set<Value*> >::iterator in = live_in.find(succ);
            if(in == live_in.end())
                live_in.insert(make_pair(succ, set<Value*>()));

            for(set<Value*>::iterator 
        }
    }
    bool runOnFunction(Function &f) override {
        cerr<<"Func: "<<f.getName().str()<<endl;
        for(Function::iterator blk_it = f.begin(); blk_it != f.end(); blk_it++){
        
            for(BasicBlock::iterator inst_it = blk_it->begin(); inst_it != blk_it->end();
              inst_it++){
                cerr<<"-------\nInst: "<<inst_it->getName().str()<<endl;
                User::op_iterator op;
                //CallInst *call_inst = dyn_cast<CallInst>(&(*inst_it));
            
                for(op = inst_it->op_begin(); op != inst_it->op_end(); op++)
                {
                    Value *val = *op;
                    if(isa<Instruction>(val))
                        cerr<<" def:";
                    else if(isa<Argument>(val))
                        cerr<<" arg:";
                    else cerr<<" otr:";
                    cerr<<(*op)->getName().str()<<endl;
                }
            }
        }
        return false;
    }
};
}
char LivenessHist::ID = 0;
static RegisterPass<LivenessHist> X("livenessHist", "Displays liveness histogram for program", false, false);
