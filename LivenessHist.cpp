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
        set<Value*> &_gen = gen[bb], &_kill = kill[bb];

        for(BasicBlock::iterator it_blk = bb->begin(); it_blk != bb->end(); it_blk++)
        {
            Instruction *inst = &*it_blk;
            for(User::op_iterator it_op = inst->op_begin(); it_op != inst->op_end(); it_op++)
            {
                Value *val = it_op->get();
                if(isa<Instruction>(val) || isa<Argument>(val)){
                    if(_kill.find((Instruction*)val) == _kill.end()){
                        _gen.insert((Instruction*)val);
                    }
                }
            }
            _kill.insert(inst);
        }
    }

    bool update_live(BasicBlock *blk){        
        if(live_out.find(blk) == live_out.end())
            live_out[blk] = set<Value*>();

        auto &out = live_out[blk];
        
        set<Value*> in = out;
        calc_genkill(blk);
        cerr<<kill[blk].size()<<": "<<in.size()<<" ";
        for(auto pval: kill[blk]){
            in.erase(pval);
        }
        cerr<<in.size()<<endl;
        for(auto pval: gen[blk]){
            in.insert(pval);
        }
        live_in[blk] = in;
        
        bool changed = false;

        for(succ_iterator succ_it = succ_begin(blk); succ_it != succ_end(blk); succ_it++){
            BasicBlock *succ = *succ_it;

            if(live_in.find(succ) == live_in.end()){
                live_in[succ] = set<Value*>();
                cerr<<";";
            }
                
            set<Value*> &in = live_in[succ];
            cerr<<"insz: "<<in.size()<<endl;
            for(auto pval: in){
                auto res = out.insert(pval);
                if(res.second)
                    changed = true;
            }
        }
        return changed;
    }

    bool doFinalization(Module &M) override {
      map<int, int> hist;
      for(map<BasicBlock*, set<Value*> >::iterator it = live_out.begin(); it!=live_out.end(); it++){
        int sz = it->second.size();
        if(hist.find(sz)==hist.end())hist[sz]=0;
        hist[sz]++;
      }
      for(map<int, int>::iterator it = hist.begin(); it != hist.end(); it++){
        cerr<<"[ "<<it->first<<": "<<it->second<<"] ";
      }
      cerr<<endl;
      return false;
    }

    bool runOnFunction(Function &func) override {
        cerr<<"Func: "<<func.getName().str()<<endl;
        while(1){
            bool changed = false;
            for(Function::iterator blk_it = func.begin(); blk_it != func.end(); blk_it++){
                changed = changed || update_live(&(*blk_it));
            }
            cerr<<".";
            if(!changed)
                break;
        }
        cerr<<"Function: "<<func.getName().str()<<endl;
        for(Function::iterator blk_it = func.begin(); blk_it != func.end(); blk_it++){
            cerr<<"blk: "<<blk_it->getName().str()<<" -> (g,k,i,o): ";
            cerr<<gen[&(*blk_it)].size()<<" ";
            cerr<<kill[&(*blk_it)].size()<<" ";
            cerr<<live_in[&(*blk_it)].size()<<" ";
            cerr<<live_out[&(*blk_it)].size()<<endl;
            for(set<Value*>::iterator it = live_in[&(*blk_it)].begin(); it != live_in[&(*blk_it)].end(); it++){
                if(isa<Instruction>(*it)){
                    cerr<< dyn_cast<Instruction>(*it)->getOpcodeName() << " ";

                    dyn_cast<Instruction>(*it)->getDebugLoc().print(errs());
                }
                // else 
                cerr<<"n:"<<(*it)->getName().str()<<" "; 
            }
            cerr<<endl;

            for(set<Value*>::iterator it = live_out[&(*blk_it)].begin(); it != live_out[&(*blk_it)].end(); it++){
                if(isa<Instruction>(*it)){
                    cerr<< dyn_cast<Instruction>(*it)->getOpcodeName() << " ";

                    dyn_cast<Instruction>(*it)->getDebugLoc().print(errs());
                }
                // else 
                cerr<<"n:"<<(*it)->getName().str()<<" "; 
            }
            cerr<<endl;
        }
        cerr<<endl;
    
        return false;
    }
};

}
char LivenessHist::ID = 0;
static RegisterPass<LivenessHist> X("livenessHist", "Displays liveness histogram for program", false, false);
