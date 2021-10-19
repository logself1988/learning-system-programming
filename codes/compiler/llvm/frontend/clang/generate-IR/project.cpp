// $ make
// $ ./project ../../data/test.c
// 
// int main() {
//     char *msg = "Hello, world!\n";
//     write(1, msg, 14);
//     return 0;
// }

// *** AST Context Stats:
//   72 types total.
//     2 ConstantArray types, 56 each (112 bytes)
//     58 Builtin types, 24 each (1392 bytes)
//     4 Complex types, 40 each (160 bytes)
//     1 FunctionNoProto types, 40 each (40 bytes)
//     5 Pointer types, 40 each (200 bytes)
//     2 Record types, 32 each (64 bytes)
// Total bytes = 1968
// 0/0 implicit default constructors created
// 0/0 implicit copy constructors created
// 0/0 implicit copy assignment operators created
// 0/0 implicit destructors created

// Number of memory regions: 2
// Bytes used: 4698
// Bytes allocated: 8192
// Bytes wasted: 3494 (includes alignment, etc)

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Host.h"

#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"

#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"

#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"

#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/PreprocessorOptions.h"

#include "clang/Parse/Parser.h"
#include "clang/Parse/ParseAST.h"

#include <iostream>

using namespace llvm;
using namespace clang;

static cl::opt<std::string> FileName(cl::Positional, cl::desc("Input file"), cl::Required);

int main(int argc, char **argv) 
{
    
    cl::ParseCommandLineOptions(argc, argv, "My simple driver\n");
    CompilerInstance CI;
    DiagnosticOptions diagnosticOptions;
    CI.createDiagnostics();

    //std::shared_ptr<TargetOptions> PTO(new TargetOptions());
    std::shared_ptr<clang::TargetOptions> PTO(new clang::TargetOptions());
    PTO->Triple = sys::getDefaultTargetTriple();
    TargetInfo *PTI = TargetInfo::CreateTargetInfo(CI.getDiagnostics(), PTO);
    CI.setTarget(PTI);

    CI.createFileManager();
    CI.createSourceManager(CI.getFileManager());
    CI.createPreprocessor(TU_Complete);
    CI.getPreprocessorOpts().UsePredefines = false;
    //ASTConsumer *astConsumer = CreateASTPrinter(NULL, "");
    //CI.setASTConsumer(astConsumer);
    CI.setASTConsumer(CreateASTPrinter(NULL, ""));

    CI.createASTContext();
    CI.createSema(TU_Complete, NULL);
    const FileEntry *pFile = CI.getFileManager().getFile(FileName).get();
    if (!pFile) 
    {
        std::cerr << "File not found: " << FileName << std::endl;
        return 1;
    }
    CI.getSourceManager().setMainFileID(CI.getSourceManager().createFileID(pFile, SourceLocation(), SrcMgr::C_User));
    
    CI.getDiagnosticClient().BeginSourceFile(CI.getLangOpts(), 0);
    ParseAST(CI.getSema());
    CI.getASTContext().PrintStats();
    CI.getDiagnosticClient().EndSourceFile();
  
    return 0;
}