
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
//#include "llvm/Bitcode/BitcodeWriter.h"
//#include "llvm/Support/ToolOutputFile.h"
#include "llvm/Support/raw_ostream.h" // for llvm:outs()


static llvm::LLVMContext context;
using namespace llvm;

Module * makeLLVMModule()
{
    Module *module = new Module("sum.ll", context);
    module->setDataLayout("e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128");
    module->setTargetTriple("x86_64-pc-linux-gnu");

    SmallVector<Type*, 2> functionTypeArgs;
    functionTypeArgs.push_back(IntegerType::get(module->getContext(), 32));
    functionTypeArgs.push_back(IntegerType::get(module->getContext(), 32));
    FunctionType *functionType = FunctionType::get(
        /*Result=*/ IntegerType::get(module->getContext(), 32),
        /*Params=*/ functionTypeArgs,
        /*isVarArg=*/ false);
    Function *functionSum = Function::Create(
        /*Type=*/ functionType,
        /*Linkage=*/ GlobalValue::ExternalLinkage,
        /*Name=*/ "sum",
        module);
    functionSum->setCallingConv(CallingConv::C);

    Function::arg_iterator args = functionSum->arg_begin();
    Value *int32_a = args++;
    int32_a->setName("a");
    Value *int32_b = args++;
    int32_b->setName("b");

    BasicBlock *labelEntry = BasicBlock::Create(module->getContext(), "entry", functionSum, 0);

    // AllocaInst *ptrA = new AllocaInst(IntegerType::get(module->getContext(), 32), "a.addr", labelEntry);
    AllocaInst *ptrA = new AllocaInst(IntegerType::get(module->getContext(), 32), 0, "a.addr", labelEntry);
    ptrA->setAlignment(MaybeAlign(4));
    // AllocaInst *ptrB = new AllocaInst(IntegerType::get(module->getContext(), 32), "b.addr", labelEntry);
    AllocaInst *ptrB = new AllocaInst(IntegerType::get(module->getContext(), 32), 0, "b.addr", labelEntry);
    ptrB->setAlignment(MaybeAlign(4));

    StoreInst *st0 = new StoreInst(int32_a, ptrA, false, labelEntry);
    st0->setAlignment(MaybeAlign(4));
    StoreInst *st1 = new StoreInst(int32_b, ptrB, false, labelEntry);
    st1->setAlignment(MaybeAlign(4));

    LoadInst *ld0 = new LoadInst(ptrA, "", false, labelEntry);
    ld0->setAlignment(MaybeAlign(4));
    LoadInst *ld1 = new LoadInst(ptrB, "", false, labelEntry);
    ld1->setAlignment(MaybeAlign(4));

    BinaryOperator *addRes = BinaryOperator::Create(Instruction::Add, ld0, ld1, "add", labelEntry);
    ReturnInst::Create(module->getContext(), addRes, labelEntry);

    return module;
}

int main()
{
    Module *module = makeLLVMModule();
    verifyModule(*module);
    std::string errorInfo;
    // OwningPtr<tool_output_file> out(new tool_output_file("./sum-gen.bc", errorInfo, sys:fs::F_Node));
    // if (!errorInfo.empty())
    // {
        // errs() << errorInfo << '\n';
        // return -1;
    // }
    // WriteBitcodeToFile(module, out->os());
    // out->keep();

    module->print(llvm::outs(), nullptr);
    return 0;
}