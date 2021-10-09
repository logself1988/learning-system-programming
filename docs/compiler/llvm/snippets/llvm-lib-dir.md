
#### Environment

```
$ uname -a
Linux DESKTOP-V3GKSFN 4.19.128-microsoft-standard #1 SMP Tue Jun 23 12:58:10 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
$ clang --version
clang version 10.0.0-4ubuntu1
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin
$ pwd
/usr/lib/llvm-10/lib
```


#### clang

```
├── clang
│   ├── 10
│   │   └── lib
│   │       └── clang_linux
│   └── 10.0.0
│       ├── README.txt
│       ├── include
│       │   ├── __clang_cuda_builtin_vars.h
│       │   ├── __clang_cuda_cmath.h
│       │   ├── __clang_cuda_complex_builtins.h
│       │   ├── __clang_cuda_device_functions.h
│       │   ├── __clang_cuda_intrinsics.h
│       │   ├── __clang_cuda_libdevice_declares.h
│       │   ├── __clang_cuda_math_forward_declares.h
│       │   ├── __clang_cuda_runtime_wrapper.h
│       │   ├── __stddef_max_align_t.h
│       │   ├── __wmmintrin_aes.h
│       │   ├── __wmmintrin_pclmul.h
│       │   ├── adxintrin.h
│       │   ├── altivec.h
│       │   ├── ammintrin.h
│       │   ├── arm64intr.h
│       │   ├── arm_acle.h
│       │   ├── arm_cmse.h
│       │   ├── arm_fp16.h
│       │   ├── arm_mve.h
│       │   ├── arm_neon.h
│       │   ├── armintr.h
│       │   ├── avx2intrin.h
│       │   ├── avx512bf16intrin.h
│       │   ├── avx512bitalgintrin.h
│       │   ├── avx512bwintrin.h
│       │   ├── avx512cdintrin.h
│       │   ├── avx512dqintrin.h
│       │   ├── avx512erintrin.h
│       │   ├── avx512fintrin.h
│       │   ├── avx512ifmaintrin.h
│       │   ├── avx512ifmavlintrin.h
│       │   ├── avx512pfintrin.h
│       │   ├── avx512vbmi2intrin.h
│       │   ├── avx512vbmiintrin.h
│       │   ├── avx512vbmivlintrin.h
│       │   ├── avx512vlbf16intrin.h
│       │   ├── avx512vlbitalgintrin.h
│       │   ├── avx512vlbwintrin.h
│       │   ├── avx512vlcdintrin.h
│       │   ├── avx512vldqintrin.h
│       │   ├── avx512vlintrin.h
│       │   ├── avx512vlvbmi2intrin.h
│       │   ├── avx512vlvnniintrin.h
│       │   ├── avx512vlvp2intersectintrin.h
│       │   ├── avx512vnniintrin.h
│       │   ├── avx512vp2intersectintrin.h
│       │   ├── avx512vpopcntdqintrin.h
│       │   ├── avx512vpopcntdqvlintrin.h
│       │   ├── avxintrin.h
│       │   ├── bmi2intrin.h
│       │   ├── bmiintrin.h
│       │   ├── cetintrin.h
│       │   ├── cldemoteintrin.h
│       │   ├── clflushoptintrin.h
│       │   ├── clwbintrin.h
│       │   ├── clzerointrin.h
│       │   ├── cpuid.h
│       │   ├── cuda_wrappers
│       │   │   ├── algorithm
│       │   │   ├── complex
│       │   │   └── new
│       │   ├── emmintrin.h
│       │   ├── enqcmdintrin.h
│       │   ├── f16cintrin.h
│       │   ├── float.h
│       │   ├── fma4intrin.h
│       │   ├── fmaintrin.h
│       │   ├── fuzzer
│       │   │   └── FuzzedDataProvider.h
│       │   ├── fxsrintrin.h
│       │   ├── gfniintrin.h
│       │   ├── htmintrin.h
│       │   ├── htmxlintrin.h
│       │   ├── ia32intrin.h
│       │   ├── immintrin.h
│       │   ├── intrin.h
│       │   ├── inttypes.h
│       │   ├── invpcidintrin.h
│       │   ├── iso646.h
│       │   ├── limits.h
│       │   ├── lwpintrin.h
│       │   ├── lzcntintrin.h
│       │   ├── mm3dnow.h
│       │   ├── mm_malloc.h
│       │   ├── mmintrin.h
│       │   ├── module.modulemap
│       │   ├── movdirintrin.h
│       │   ├── msa.h
│       │   ├── mwaitxintrin.h
│       │   ├── nmmintrin.h
│       │   ├── omp-tools.h
│       │   ├── omp.h
│       │   ├── ompt.h
│       │   ├── opencl-c-base.h
│       │   ├── opencl-c.h
│       │   ├── openmp_wrappers
│       │   │   ├── __clang_openmp_math.h
│       │   │   ├── __clang_openmp_math_declares.h
│       │   │   ├── cmath
│       │   │   └── math.h
│       │   ├── pconfigintrin.h
│       │   ├── pkuintrin.h
│       │   ├── pmmintrin.h
│       │   ├── popcntintrin.h
│       │   ├── ppc_wrappers
│       │   │   ├── emmintrin.h
│       │   │   ├── mm_malloc.h
│       │   │   ├── mmintrin.h
│       │   │   ├── pmmintrin.h
│       │   │   ├── smmintrin.h
│       │   │   ├── tmmintrin.h
│       │   │   └── xmmintrin.h
│       │   ├── prfchwintrin.h
│       │   ├── profile
│       │   │   └── InstrProfData.inc
│       │   ├── ptwriteintrin.h
│       │   ├── rdseedintrin.h
│       │   ├── rtmintrin.h
│       │   ├── s390intrin.h
│       │   ├── sanitizer
│       │   │   ├── allocator_interface.h
│       │   │   ├── asan_interface.h
│       │   │   ├── common_interface_defs.h
│       │   │   ├── coverage_interface.h
│       │   │   ├── dfsan_interface.h
│       │   │   ├── hwasan_interface.h
│       │   │   ├── linux_syscall_hooks.h
│       │   │   ├── lsan_interface.h
│       │   │   ├── msan_interface.h
│       │   │   ├── netbsd_syscall_hooks.h
│       │   │   ├── scudo_interface.h
│       │   │   ├── tsan_interface.h
│       │   │   ├── tsan_interface_atomic.h
│       │   │   └── ubsan_interface.h
│       │   ├── sgxintrin.h
│       │   ├── shaintrin.h
│       │   ├── smmintrin.h
│       │   ├── stdalign.h
│       │   ├── stdarg.h
│       │   ├── stdatomic.h
│       │   ├── stdbool.h
│       │   ├── stddef.h
│       │   ├── stdint.h
│       │   ├── stdnoreturn.h
│       │   ├── tbmintrin.h
│       │   ├── tgmath.h
│       │   ├── tmmintrin.h
│       │   ├── unwind.h
│       │   ├── vadefs.h
│       │   ├── vaesintrin.h
│       │   ├── varargs.h
│       │   ├── vecintrin.h
│       │   ├── vpclmulqdqintrin.h
│       │   ├── waitpkgintrin.h
│       │   ├── wbnoinvdintrin.h
│       │   ├── wmmintrin.h
│       │   ├── x86intrin.h
│       │   ├── xmmintrin.h
│       │   ├── xopintrin.h
│       │   ├── xray
│       │   │   ├── xray_interface.h
│       │   │   ├── xray_log_interface.h
│       │   │   └── xray_records.h
│       │   ├── xsavecintrin.h
│       │   ├── xsaveintrin.h
│       │   ├── xsaveoptintrin.h
│       │   ├── xsavesintrin.h
│       │   └── xtestintrin.h
│       ├── lib
│       │   └── linux
│       │       ├── clang_rt.crtbegin-i386.o
│       │       ├── clang_rt.crtbegin-x86_64.o
│       │       ├── clang_rt.crtend-i386.o
│       │       ├── clang_rt.crtend-x86_64.o
│       │       ├── libclang_rt.asan-i386.a
│       │       ├── libclang_rt.asan-i386.so
│       │       ├── libclang_rt.asan-preinit-i386.a
│       │       ├── libclang_rt.asan-preinit-x86_64.a
│       │       ├── libclang_rt.asan-x86_64.a
│       │       ├── libclang_rt.asan-x86_64.a.syms
│       │       ├── libclang_rt.asan-x86_64.so
│       │       ├── libclang_rt.asan_cxx-i386.a
│       │       ├── libclang_rt.asan_cxx-x86_64.a
│       │       ├── libclang_rt.asan_cxx-x86_64.a.syms
│       │       ├── libclang_rt.builtins-i386.a
│       │       ├── libclang_rt.builtins-x86_64.a
│       │       ├── libclang_rt.cfi-i386.a
│       │       ├── libclang_rt.cfi-x86_64.a
│       │       ├── libclang_rt.cfi_diag-i386.a
│       │       ├── libclang_rt.cfi_diag-x86_64.a
│       │       ├── libclang_rt.dd-x86_64.a
│       │       ├── libclang_rt.dfsan-x86_64.a
│       │       ├── libclang_rt.dfsan-x86_64.a.syms
│       │       ├── libclang_rt.dyndd-x86_64.so
│       │       ├── libclang_rt.fuzzer-i386.a
│       │       ├── libclang_rt.fuzzer-x86_64.a
│       │       ├── libclang_rt.fuzzer_no_main-i386.a
│       │       ├── libclang_rt.fuzzer_no_main-x86_64.a
│       │       ├── libclang_rt.gwp_asan-i386.a
│       │       ├── libclang_rt.gwp_asan-x86_64.a
│       │       ├── libclang_rt.hwasan-x86_64.a
│       │       ├── libclang_rt.hwasan-x86_64.a.syms
│       │       ├── libclang_rt.hwasan-x86_64.so
│       │       ├── libclang_rt.hwasan_cxx-x86_64.a
│       │       ├── libclang_rt.hwasan_cxx-x86_64.a.syms
│       │       ├── libclang_rt.lsan-i386.a
│       │       ├── libclang_rt.lsan-x86_64.a
│       │       ├── libclang_rt.msan-x86_64.a
│       │       ├── libclang_rt.msan-x86_64.a.syms
│       │       ├── libclang_rt.msan_cxx-x86_64.a
│       │       ├── libclang_rt.msan_cxx-x86_64.a.syms
│       │       ├── libclang_rt.profile-i386.a
│       │       ├── libclang_rt.profile-x86_64.a
│       │       ├── libclang_rt.safestack-i386.a
│       │       ├── libclang_rt.safestack-x86_64.a
│       │       ├── libclang_rt.scudo-i386.a
│       │       ├── libclang_rt.scudo-i386.so
│       │       ├── libclang_rt.scudo-x86_64.a
│       │       ├── libclang_rt.scudo-x86_64.so
│       │       ├── libclang_rt.scudo_cxx-i386.a
│       │       ├── libclang_rt.scudo_cxx-x86_64.a
│       │       ├── libclang_rt.scudo_cxx_minimal-i386.a
│       │       ├── libclang_rt.scudo_cxx_minimal-x86_64.a
│       │       ├── libclang_rt.scudo_minimal-i386.a
│       │       ├── libclang_rt.scudo_minimal-i386.so
│       │       ├── libclang_rt.scudo_minimal-x86_64.a
│       │       ├── libclang_rt.scudo_minimal-x86_64.so
│       │       ├── libclang_rt.scudo_standalone-i386.a
│       │       ├── libclang_rt.scudo_standalone-x86_64.a
│       │       ├── libclang_rt.scudo_standalone_cxx-i386.a
│       │       ├── libclang_rt.scudo_standalone_cxx-x86_64.a
│       │       ├── libclang_rt.stats-i386.a
│       │       ├── libclang_rt.stats-x86_64.a
│       │       ├── libclang_rt.stats_client-i386.a
│       │       ├── libclang_rt.stats_client-x86_64.a
│       │       ├── libclang_rt.tsan-x86_64.a
│       │       ├── libclang_rt.tsan-x86_64.a.syms
│       │       ├── libclang_rt.tsan_cxx-x86_64.a
│       │       ├── libclang_rt.tsan_cxx-x86_64.a.syms
│       │       ├── libclang_rt.ubsan_minimal-i386.a
│       │       ├── libclang_rt.ubsan_minimal-i386.so
│       │       ├── libclang_rt.ubsan_minimal-x86_64.a
│       │       ├── libclang_rt.ubsan_minimal-x86_64.a.syms
│       │       ├── libclang_rt.ubsan_minimal-x86_64.so
│       │       ├── libclang_rt.ubsan_standalone-i386.a
│       │       ├── libclang_rt.ubsan_standalone-i386.so
│       │       ├── libclang_rt.ubsan_standalone-x86_64.a
│       │       ├── libclang_rt.ubsan_standalone-x86_64.a.syms
│       │       ├── libclang_rt.ubsan_standalone-x86_64.so
│       │       ├── libclang_rt.ubsan_standalone_cxx-i386.a
│       │       ├── libclang_rt.ubsan_standalone_cxx-x86_64.a
│       │       ├── libclang_rt.ubsan_standalone_cxx-x86_64.a.syms
│       │       ├── libclang_rt.xray-basic-x86_64.a
│       │       ├── libclang_rt.xray-fdr-x86_64.a
│       │       ├── libclang_rt.xray-profiling-x86_64.a
│       │       └── libclang_rt.xray-x86_64.a
│       └── share
│           ├── README.txt
│           ├── asan_blacklist.txt
│           ├── cfi_blacklist.txt
│           ├── dfsan_abilist.txt
│           ├── hwasan_blacklist.txt
│           └── msan_blacklist.txt
```

#### cmake

```
├── cmake
│   ├── clang
│   │   ├── ClangConfig.cmake
│   │   ├── ClangTargets-relwithdebinfo.cmake
│   │   └── ClangTargets.cmake
│   ├── llvm
│   │   ├── AddLLVM.cmake
│   │   ├── AddLLVMDefinitions.cmake
│   │   ├── AddOCaml.cmake
│   │   ├── AddSphinxTarget.cmake
│   │   ├── CheckAtomic.cmake
│   │   ├── CheckCompilerVersion.cmake
│   │   ├── CheckLinkerFlag.cmake
│   │   ├── ChooseMSVCCRT.cmake
│   │   ├── CrossCompile.cmake
│   │   ├── DetermineGCCCompatible.cmake
│   │   ├── FindLibpfm.cmake
│   │   ├── FindOCaml.cmake
│   │   ├── FindSphinx.cmake
│   │   ├── FindZ3.cmake
│   │   ├── GenerateVersionFromVCS.cmake
│   │   ├── HandleLLVMOptions.cmake
│   │   ├── HandleLLVMStdlib.cmake
│   │   ├── LLVM-Config.cmake
│   │   ├── LLVMConfig.cmake
│   │   ├── LLVMConfigVersion.cmake
│   │   ├── LLVMDistributionSupport.cmake
│   │   ├── LLVMExports-relwithdebinfo.cmake
│   │   ├── LLVMExports.cmake
│   │   ├── LLVMExternalProjectUtils.cmake
│   │   ├── LLVMInstallSymlink.cmake
│   │   ├── LLVMProcessSources.cmake
│   │   ├── TableGen.cmake
│   │   ├── UseLibtool.cmake
│   │   └── VersionFromVCS.cmake
│   └── polly
│       ├── PollyConfig.cmake
│       └── PollyExports-all.cmake
```

#### libLLVM

```
├── libLLVM-10.0.0.so -> ../../x86_64-linux-gnu/libLLVM-10.so.1
├── libLLVM-10.0.0.so.1 -> ../../x86_64-linux-gnu/libLLVM-10.so.1
├── libLLVM-10.so -> ../../x86_64-linux-gnu/libLLVM-10.so.1
├── libLLVM-10.so.1 -> ../../x86_64-linux-gnu/libLLVM-10.so.1
├── libLLVM.so -> libLLVM-10.so
├── libLLVMAArch64AsmParser.a
├── libLLVMAArch64CodeGen.a
├── libLLVMAArch64Desc.a
├── libLLVMAArch64Disassembler.a
├── libLLVMAArch64Info.a
├── libLLVMAArch64Utils.a
├── libLLVMAMDGPUAsmParser.a
├── libLLVMAMDGPUCodeGen.a
├── libLLVMAMDGPUDesc.a
├── libLLVMAMDGPUDisassembler.a
├── libLLVMAMDGPUInfo.a
├── libLLVMAMDGPUUtils.a
├── libLLVMARMAsmParser.a
├── libLLVMARMCodeGen.a
├── libLLVMARMDesc.a
├── libLLVMARMDisassembler.a
├── libLLVMARMInfo.a
├── libLLVMARMUtils.a
├── libLLVMAVRAsmParser.a
├── libLLVMAVRCodeGen.a
├── libLLVMAVRDesc.a
├── libLLVMAVRDisassembler.a
├── libLLVMAVRInfo.a
├── libLLVMAggressiveInstCombine.a
├── libLLVMAnalysis.a
├── libLLVMAsmParser.a                          // 解析汇编文本, 实现汇编器
├── libLLVMAsmPrinter.a                         // 打印汇编语言, 实现生成汇编文件的后端
├── libLLVMBPFAsmParser.a
├── libLLVMBPFCodeGen.a
├── libLLVMBPFDesc.a
├── libLLVMBPFDisassembler.a
├── libLLVMBPFInfo.a
├── libLLVMBinaryFormat.a
├── libLLVMBitReader.a
├── libLLVMBitWriter.a
├── libLLVMBitstreamReader.a
├── libLLVMCFGuard.a
├── libLLVMCodeGen.a                            // 代码生成算法
├── libLLVMCore.a
├── libLLVMCoroutines.a
├── libLLVMCoverage.a
├── libLLVMDWARFLinker.a
├── libLLVMDebugInfoCodeView.a
├── libLLVMDebugInfoDWARF.a
├── libLLVMDebugInfoGSYM.a
├── libLLVMDebugInfoMSF.a
├── libLLVMDebugInfoPDB.a
├── libLLVMDemangle.a
├── libLLVMDlltoolDriver.a
├── libLLVMExecutionEngine.a
├── libLLVMFrontendOpenMP.a
├── libLLVMFuzzMutate.a
├── libLLVMGlobalISel.a
├── libLLVMHexagonAsmParser.a
├── libLLVMHexagonCodeGen.a
├── libLLVMHexagonDesc.a
├── libLLVMHexagonDisassembler.a
├── libLLVMHexagonInfo.a
├── libLLVMIRReader.a
├── libLLVMInstCombine.a
├── libLLVMInstrumentation.a
├── libLLVMInterpreter.a
├── libLLVMJITLink.a
├── libLLVMLTO.a
├── libLLVMLanaiAsmParser.a
├── libLLVMLanaiCodeGen.a
├── libLLVMLanaiDesc.a
├── libLLVMLanaiDisassembler.a
├── libLLVMLanaiInfo.a
├── libLLVMLibDriver.a
├── libLLVMLineEditor.a
├── libLLVMLinker.a
├── libLLVMMC.a                                 // MCInst类, LLVM最底层的程序表示
├── libLLVMMCA.a
├── libLLVMMCDisassembler.a                     // 实现反汇编器, 读取对象代码, 解码为MCInst对象
├── libLLVMMCJIT.a                              // JIT代码生成器
├── libLLVMMCParser.a                           // MCAsmParser类的接口, 用于实现解析汇编文本和部分汇编器的工作
├── libLLVMMIRParser.a
├── libLLVMMSP430AsmParser.a
├── libLLVMMSP430CodeGen.a
├── libLLVMMSP430Desc.a
├── libLLVMMSP430Disassembler.a
├── libLLVMMSP430Info.a
├── libLLVMMipsAsmParser.a
├── libLLVMMipsCodeGen.a
├── libLLVMMipsDesc.a
├── libLLVMMipsDisassembler.a
├── libLLVMMipsInfo.a
├── libLLVMNVPTXCodeGen.a
├── libLLVMNVPTXDesc.a
├── libLLVMNVPTXInfo.a
├── libLLVMObjCARCOpts.a
├── libLLVMObject.a
├── libLLVMObjectYAML.a
├── libLLVMOption.a
├── libLLVMOrcError.a
├── libLLVMOrcJIT.a
├── libLLVMPasses.a
├── libLLVMPerfJITEvents.a
├── libLLVMPowerPCAsmParser.a
├── libLLVMPowerPCCodeGen.a
├── libLLVMPowerPCDesc.a
├── libLLVMPowerPCDisassembler.a
├── libLLVMPowerPCInfo.a
├── libLLVMProfileData.a
├── libLLVMRISCVAsmParser.a
├── libLLVMRISCVCodeGen.a
├── libLLVMRISCVDesc.a
├── libLLVMRISCVDisassembler.a
├── libLLVMRISCVInfo.a
├── libLLVMRISCVUtils.a
├── libLLVMRemarks.a
├── libLLVMRuntimeDyld.a
├── libLLVMScalarOpts.a
├── libLLVMSelectionDAG.a                       // 包含SelectionDAG等类
├── libLLVMSparcAsmParser.a
├── libLLVMSparcCodeGen.a
├── libLLVMSparcDesc.a
├── libLLVMSparcDisassembler.a
├── libLLVMSparcInfo.a
├── libLLVMSupport.a
├── libLLVMSymbolize.a
├── libLLVMSystemZAsmParser.a
├── libLLVMSystemZCodeGen.a
├── libLLVMSystemZDesc.a
├── libLLVMSystemZDisassembler.a
├── libLLVMSystemZInfo.a
├── libLLVMTableGen.a
├── libLLVMTarget.a                             // 提供接口支持目标独立的算法使用目标特定的功能
├── libLLVMTextAPI.a
├── libLLVMTransformUtils.a
├── libLLVMVectorize.a
├── libLLVMWebAssemblyAsmParser.a
├── libLLVMWebAssemblyCodeGen.a
├── libLLVMWebAssemblyDesc.a
├── libLLVMWebAssemblyDisassembler.a
├── libLLVMWebAssemblyInfo.a
├── libLLVMWindowsManifest.a
├── libLLVMX86AsmParser.a                       // <Target>AsmParser.a
├── libLLVMX86CodeGen.a                         // <Target>CodeGen.a
├── libLLVMX86Desc.a                            // <Target>Desc.a
├── libLLVMX86Disassembler.a                    // <Target>Disassembler.a
├── libLLVMX86Info.a                            // <Target>Info.a
├── libLLVMX86Utils.a                           //
├── libLLVMXCoreCodeGen.a
├── libLLVMXCoreDesc.a
├── libLLVMXCoreDisassembler.a
├── libLLVMXCoreInfo.a
├── libLLVMXRay.a
├── libLLVMipo.a
```

#### libclang

```
├── libclang-10.0.0.so -> libclang-10.so
├── libclang-10.so -> ../../x86_64-linux-gnu/libclang-10.so.1
├── libclang-10.so.1 -> ../../x86_64-linux-gnu/libclang-10.so.1
├── libclang-cpp.so.10
├── libclang.so -> ../../x86_64-linux-gnu/libclang-10.so.1
├── libclang.so.1 -> libclang-10.so.1
├── libclangARCMigrate.a
├── libclangAST.a
├── libclangASTMatchers.a
├── libclangAnalysis.a
├── libclangApplyReplacements.a
├── libclangBasic.a
├── libclangChangeNamespace.a
├── libclangCodeGen.a
├── libclangCrossTU.a
├── libclangDaemon.a
├── libclangDaemonTweaks.a
├── libclangDependencyScanning.a
├── libclangDirectoryWatcher.a
├── libclangDoc.a
├── libclangDriver.a
├── libclangDynamicASTMatchers.a
├── libclangEdit.a
├── libclangFormat.a
├── libclangFrontend.a
├── libclangFrontendTool.a
├── libclangHandleCXX.a
├── libclangHandleLLVM.a
├── libclangIncludeFixer.a
├── libclangIncludeFixerPlugin.a
├── libclangIndex.a
├── libclangLex.a
├── libclangMove.a
├── libclangParse.a
├── libclangQuery.a
├── libclangReorderFields.a
├── libclangRewrite.a
├── libclangRewriteFrontend.a
├── libclangSema.a
├── libclangSerialization.a
├── libclangStaticAnalyzerCheckers.a
├── libclangStaticAnalyzerCore.a
├── libclangStaticAnalyzerFrontend.a
├── libclangTidy.a
├── libclangTidyAbseilModule.a
├── libclangTidyAndroidModule.a
├── libclangTidyBoostModule.a
├── libclangTidyBugproneModule.a
├── libclangTidyCERTModule.a
├── libclangTidyCppCoreGuidelinesModule.a
├── libclangTidyDarwinModule.a
├── libclangTidyFuchsiaModule.a
├── libclangTidyGoogleModule.a
├── libclangTidyHICPPModule.a
├── libclangTidyLLVMModule.a
├── libclangTidyLinuxKernelModule.a
├── libclangTidyMPIModule.a
├── libclangTidyMiscModule.a
├── libclangTidyModernizeModule.a
├── libclangTidyObjCModule.a
├── libclangTidyOpenMPModule.a
├── libclangTidyPerformanceModule.a
├── libclangTidyPlugin.a
├── libclangTidyPortabilityModule.a
├── libclangTidyReadabilityModule.a
├── libclangTidyUtils.a
├── libclangTidyZirconModule.a
├── libclangTooling.a
├── libclangToolingASTDiff.a
├── libclangToolingCore.a
├── libclangToolingInclusions.a
├── libclangToolingRefactoring.a
├── libclangToolingSyntax.a
├── libclangTransformer.a
```

#### Others

```
├── LLVMPolly.so
├── LLVMgold.so
├── libLTO.so -> libLTO.so.10
├── libLTO.so.10
├── libPolly.a
├── libPollyISL.a
├── libPollyPPCG.a
├── libRemarks.so -> libRemarks.so.10
├── libRemarks.so.10
├── libarcher.so
├── libarcher_static.a
├── libfindAllSymbols.a
├── libgomp.so -> libomp.so.5
├── libiomp5.so -> libomp.so.5
├── libomp-10.so.5
├── libomp.so -> libomp.so.5
├── libomp.so.5
└── libomptarget.so
```
