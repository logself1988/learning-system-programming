// $ clang++ -O3 -Wall -std=c++11 toy.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o toy

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h" // for llvm:outs()
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include <string>
#include <vector>

static llvm::LLVMContext context;

typedef llvm::SmallVector<llvm::BasicBlock *, 16> BBList;
typedef llvm::SmallVector<llvm::Value *, 16> ValList;

llvm::Function * createFunc(
    llvm::Module *module, 
    llvm::IRBuilder<> &builder, 
    std::string name,
    std::vector<std::string> funcArgs)
{
    std::vector<llvm::Type *> funcArgTypes(funcArgs.size(), llvm::Type::getInt32Ty(context));
    llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getInt32Ty(), funcArgTypes, false);
    llvm::Function *func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, name, module);
    return func;
}

void setFunctionArgs(
    llvm::Function *func, 
    std::vector<std::string> funcArgs) 
{
    unsigned idx = 0;
    llvm::Function::arg_iterator ai, ae;
    for(ai = func->arg_begin(), ae = func->arg_end(); ai != ae; ++ai, ++idx)
    {
        ai->setName(funcArgs[idx]);
    }
}

llvm::BasicBlock * createBasicBlock(
    llvm::Function *func, 
    std::string name)
{
    return llvm::BasicBlock::Create(context, name, func);
}

llvm::GlobalVariable * createGlobalVar(
    llvm::Module *module, 
    llvm::IRBuilder<> &builder, 
    std::string name)
{
    module->getOrInsertGlobal(name, builder.getInt32Ty());
    llvm::GlobalVariable *gVar = module->getNamedGlobal(name);
    gVar->setLinkage(llvm::GlobalVariable::CommonLinkage);
    gVar->setAlignment(4);
    return gVar;
}

llvm::Value * createArith(
    llvm::IRBuilder<> &builder, 
    llvm::Value *L,
    llvm::Value *R) 
{
    return builder.CreateMul(L, R, "multmp");
}

llvm::Value * createIfElse(
    llvm::IRBuilder<> &builder,
    BBList list,
    ValList valList)
{
    using namespace llvm;

    Value *condition = valList[0];
    Value *arg1 = valList[1];
    BasicBlock *thenBB = list[0];
    BasicBlock *elseBB = list[1];
    BasicBlock *mergeBB = list[2];
    builder.CreateCondBr(condition, thenBB, elseBB);

    builder.SetInsertPoint(thenBB);
    Value *thenVal = builder.CreateAdd(arg1, builder.getInt32(1), "thenaddtmp");
    builder.CreateBr(mergeBB);

    builder.SetInsertPoint(elseBB);
    Value *elseVal = builder.CreateAdd(arg1, builder.getInt32(2), "elseaddtmp");
    builder.CreateBr(mergeBB);

    unsigned phiBBSize = list.size() - 1;
    builder.SetInsertPoint(mergeBB);
    PHINode *phi = builder.CreatePHI(Type::getInt32Ty(context), phiBBSize, "iftmp");
    phi->addIncoming(thenVal, thenBB);
    phi->addIncoming(elseVal, elseBB);

    return phi;
}

llvm::Value * createLoop(
    llvm::IRBuilder<> &builder,
    BBList list,
    ValList valList,
    llvm::Value *startVal,
    llvm::Value *endVal)
{
    using namespace llvm;

    BasicBlock *preheaderBB = builder.GetInsertBlock();
    Value *val = valList[0];
    BasicBlock * loopBB = list[0];
    builder.CreateBr(loopBB);

    builder.SetInsertPoint(loopBB);
    PHINode *indVar = builder.CreatePHI(Type::getInt32Ty(context), 2, "i");
    indVar->addIncoming(startVal, preheaderBB);
    Value *add = builder.CreateAdd(val, builder.getInt32(5), "addtmp");
    Value *stepVal = builder.getInt32(1);
    Value *nextVal = builder.CreateAdd(indVar, stepVal, "nextval");
    Value *endCond = builder.CreateICmpULT(indVar, endVal, "endcond");
    endCond = builder.CreateICmpNE(endCond, builder.getInt1(0), "loopcond");

    BasicBlock *loopEndBB = builder.GetInsertBlock();
    BasicBlock *afterBB = list[1];
    builder.CreateCondBr(endCond, loopBB, afterBB);
    
    builder.SetInsertPoint(afterBB);
    indVar->addIncoming(nextVal, loopEndBB);
    return add;
}

int main(int argc, char *argv[])
{
    static llvm::IRBuilder<> builder(context);
    
    // 模块
    llvm::Module *module = new llvm::Module("my compiler", context);
    
    // 全局变量
    llvm::GlobalVariable *xVar = createGlobalVar(module, builder, "x");

    // 函数参数
    static std::vector<std::string> fooFuncArgs;
    fooFuncArgs.push_back("a");
    fooFuncArgs.push_back("b");
    llvm::Function *fooFunc = createFunc(module, builder, "foo", fooFuncArgs);
    setFunctionArgs(fooFunc, fooFuncArgs);
    // 基本块
    llvm::BasicBlock *entryBlock = createBasicBlock(fooFunc, "entry");
    builder.SetInsertPoint(entryBlock);
    
    // 语句
    llvm::Value *arg1 = fooFunc->arg_begin();
    llvm::Value *constant = builder.getInt32(16);
    llvm::Value *val = createArith(builder, arg1, constant); 
    // 返回值
    // builder.CreateRet(val);

    // if-else
    // llvm::Value *val2 = builder.getInt32(100);
    // llvm::Value *compare = builder.CreateICmpULT(val, val2, "cmptmp"); // i1
    // // https://stackoverflow.com/questions/35856196/llvm-test-example-issue-with-type-comparison
    // // llvm::Value *condition = builder.CreateICmpNE(compare, builder.getInt32(0), "ifcond");
    // llvm::Value *condition = builder.CreateICmpNE(compare, builder.getInt1(0), "ifcond");
    // ValList valList;
    // valList.push_back(condition);
    // valList.push_back(arg1);
    // llvm::BasicBlock *thenBB = createBasicBlock(fooFunc, "then");
    // llvm::BasicBlock *elseBB = createBasicBlock(fooFunc, "else");
    // llvm::BasicBlock *mergeBB = createBasicBlock(fooFunc, "ifcond");
    // BBList list;
    // list.push_back(thenBB);
    // list.push_back(elseBB);
    // list.push_back(mergeBB);

    // llvm::Value *v = createIfElse(builder, list, valList);
    // // 返回值
    // builder.CreateRet(v);

    // 循环语句
    llvm::Function::arg_iterator ai = fooFunc-> arg_begin();
    llvm::Value *loopArg1 = ai++;
    llvm::Value *loopArg2 = ai;
    llvm::Value *loopConstant = builder.getInt32(16);
    llvm::Value *loopVal = createArith(builder, loopArg1, loopConstant);
    ValList loopValList;
    loopValList.push_back(loopArg1);
    BBList loopList;
    llvm::BasicBlock *loopBB = createBasicBlock(fooFunc, "loop");
    llvm::BasicBlock *afterBB = createBasicBlock(fooFunc, "afterloop");
    loopList.push_back(loopBB);
    loopList.push_back(afterBB);
    llvm::Value *startVal = builder.getInt32(1);
    llvm::Value *Res = createLoop(builder, loopList, loopValList, startVal, loopArg2);
    // 返回值
    builder.CreateRet(Res);

    // 校验函数
    llvm::verifyFunction(*fooFunc);

    // module->dump(); // ERROR
    module->print(llvm::outs(), nullptr);
 
    return 0;
}