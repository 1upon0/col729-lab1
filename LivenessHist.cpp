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

struct LivenessHist : public FunctionPass {
    static char ID;
    LivenessHist() :FunctionPass(ID) {}

    map<BasicBlock*, set<Value*> > live_in, live_out, gen, kill;
    
    void calc_genkill(BasicBlock *bb)
    {
        if(gen.find(bb) != gen.end() || kill.find(bb) != kill.end())
            return;
        gen[bb] = set<Value*>();
        kill[bb] = set<Value*>();
        set<Value*>() &_gen = gen[bb], &_kill = kill[bb];

        for(BasicBlock::iterator it_blk = bb->begin(); it_blk != bb->end(); it_blk++)
        {
            Instruction *inst = &*it_blk;
            for(User::op_iterator it_op = inst->op_begin(); it_op != inst->op_end(); it_op++)
            {
                Value *val = it_op->get();
                if(isa<Instruction>(val) || isa<Argument>(val)){
                    if(_kill.find((Instruction*)val) == _kill.end()){
                        _gen->insert((Instruction*)val);
                    }
                }
            }
            _kill.insert(inst);
        }
    }

    bool update_live(BasicBlock *blk){        
        if(live_out.find(blk) == live_out.end())
            live_out[blk] = set<Value*>();

        set<Value*> &out = live_out[blk];
        bool changed = false;

        for(BasicBlock::iterator succ_it = succ_begin(blk); succ_it != succ_end(blk); succ_it++){
            BasicBlock *succ = succ_it;
            map<BasicBlock*, set<Value*> >::iterator in = live_in.find(succ);
            if(in == live_in.end())
                live_in.insert(make_pair(succ, set<Value*>()));

            for(set<Value*>::iterator val_it = in->begin(); val_it != in->end(); val_it++){
                pair<set<Value*>::iterator, bool> res = out.insert(*val_it);
                if(res->second)
                    changed = true;
            }
        }
        set<Value*> in = out;
        for(set<Value*>::iterator val_it = kill->begin(); val_it != kill->end(); val_it++){
            in.erase(*val_it);
        }
        for(set<Value*>::iterator val_it = gen->begin(); val_it != gen->end(); val_it++){
            in.insert(*val_it);
        }
        live_in[blk] = in;
        return changed;
    }
    bool runOnFunction(Function &func) override {
        cerr<<"Func: "<<func.getName().str()<<endl;
        while(1){
            bool changed = false;
            for(Function::iterator blk_it = func.begin(); blk_it != func.end(); blk_it++){
                changed = changed || update_live(blk_it);
            }
            if(!changed)
                break;
        }
        return false;
    }
};

}
char LivenessHist::ID = 0;
static RegisterPass<LivenessHist> X("livenessHist", "Displays liveness histogram for program", false, false);
