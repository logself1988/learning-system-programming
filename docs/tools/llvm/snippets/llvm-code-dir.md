```
// $ pwd
// /mnt/d/workspace/llvm-project/llvm
// $ tree -d -L 3 > /mnt/d/workspace/llvm-code-dir.txt
```

#### benchmarks

```
├── benchmarks
```

#### bindings

```
├── bindings
│   ├── go
│   │   └── llvm
│   ├── ocaml
│   │   ├── all_backends
│   │   ├── analysis
│   │   ├── backends
│   │   ├── bitreader
│   │   ├── bitwriter
│   │   ├── debuginfo
│   │   ├── executionengine
│   │   ├── irreader
│   │   ├── linker
│   │   ├── llvm
│   │   ├── target
│   │   └── transforms
│   └── python
│       └── llvm
```

#### cmake

```
├── cmake
│   ├── modules
│   └── platforms
```

#### docs

```
├── docs
│   ├── AMDGPU
│   ├── CommandGuide
│   ├── DependenceGraphs
│   ├── Frontend
│   ├── GlobalISel
│   ├── HistoricalNotes
│   ├── PDB
│   ├── Proposals
│   ├── TableGen
│   ├── _ocamldoc
│   ├── _static
│   ├── _templates
│   ├── _themes
│   │   └── llvm-theme
│   └── tutorial
│       └── MyFirstLanguageFrontend
```

#### examples

```
├── examples
│   ├── BrainF
│   ├── Bye
│   ├── ExceptionDemo
│   ├── Fibonacci
│   ├── HowToUseJIT
│   ├── HowToUseLLJIT
│   ├── IRTransforms
│   ├── Kaleidoscope
│   │   ├── BuildingAJIT
│   │   ├── Chapter2
│   │   ├── Chapter3
│   │   ├── Chapter4
│   │   ├── Chapter5
│   │   ├── Chapter6
│   │   ├── Chapter7
│   │   ├── Chapter8
│   │   ├── Chapter9
│   │   ├── MCJIT
│   │   └── include
│   ├── ModuleMaker
│   ├── OrcV2Examples
│   │   ├── LLJITDumpObjects
│   │   ├── LLJITWithCustomObjectLinkingLayer
│   │   ├── LLJITWithGDBRegistrationListener
│   │   ├── LLJITWithInitializers
│   │   ├── LLJITWithLazyReexports
│   │   ├── LLJITWithObjectCache
│   │   ├── LLJITWithObjectLinkingLayerPlugin
│   │   ├── LLJITWithOptimizingIRTransform
│   │   ├── LLJITWithRemoteDebugging
│   │   ├── LLJITWithTargetProcessControl
│   │   ├── LLJITWithThinLTOSummaries
│   │   ├── OrcV2CBindingsAddObjectFile
│   │   ├── OrcV2CBindingsBasicUsage
│   │   ├── OrcV2CBindingsDumpObjects
│   │   ├── OrcV2CBindingsIRTransforms
│   │   ├── OrcV2CBindingsLazy
│   │   ├── OrcV2CBindingsReflectProcessSymbols
│   │   ├── OrcV2CBindingsRemovableCode
│   │   └── OrcV2CBindingsVeryLazy
│   ├── ParallelJIT
│   └── SpeculativeJIT
```

#### include

```
├── include
│   ├── llvm
│   │   ├── ADT
│   │   ├── Analysis
│   │   ├── AsmParser
│   │   ├── BinaryFormat
│   │   ├── Bitcode
│   │   ├── Bitstream
│   │   ├── CodeGen
│   │   ├── Config
│   │   ├── DWARFLinker
│   │   ├── DWP
│   │   ├── DebugInfo
│   │   ├── Demangle
│   │   ├── ExecutionEngine
│   │   ├── FileCheck
│   │   ├── Frontend
│   │   ├── FuzzMutate
│   │   ├── IR
│   │   ├── IRReader
│   │   ├── InterfaceStub
│   │   ├── LTO
│   │   ├── LineEditor
│   │   ├── Linker
│   │   ├── MC
│   │   ├── MCA
│   │   ├── Object
│   │   ├── ObjectYAML
│   │   ├── Option
│   │   ├── Passes
│   │   ├── ProfileData
│   │   ├── Remarks
│   │   ├── Support
│   │   ├── TableGen
│   │   ├── Target
│   │   ├── Testing
│   │   ├── TextAPI
│   │   ├── ToolDrivers
│   │   ├── Transforms
│   │   ├── WindowsManifest
│   │   ├── WindowsResource
│   │   └── XRay
│   └── llvm-c
│       └── Transforms
```

#### lib

```
├── lib                                         // 库
│   ├── Analysis
│   │   └── models
│   ├── AsmParser
│   ├── BinaryFormat
│   ├── Bitcode
│   │   ├── Reader
│   │   └── Writer
│   ├── Bitstream
│   │   └── Reader
│   ├── CodeGen                                 // 通用的代码生成算法
│   │   ├── AsmPrinter
│   │   ├── GlobalISel
│   │   ├── LiveDebugValues
│   │   ├── MIRParser
│   │   └── SelectionDAG
│   ├── DWARFLinker
│   ├── DWP
│   ├── DebugInfo
│   │   ├── CodeView
│   │   ├── DWARF
│   │   ├── GSYM
│   │   ├── MSF
│   │   ├── PDB
│   │   └── Symbolize
│   ├── Demangle
│   ├── ExecutionEngine
│   │   ├── IntelJITEvents
│   │   ├── Interpreter
│   │   ├── JITLink
│   │   ├── MCJIT
│   │   ├── OProfileJIT
│   │   ├── Orc
│   │   ├── PerfJITEvents
│   │   └── RuntimeDyld
│   ├── Extensions
│   ├── FileCheck
│   ├── Frontend
│   │   ├── OpenACC
│   │   └── OpenMP
│   ├── FuzzMutate
│   ├── Fuzzer
│   ├── IR
│   ├── IRReader
│   ├── InterfaceStub
│   ├── LTO
│   ├── LineEditor
│   ├── Linker
│   ├── MC                                      // 支持汇编器和反汇编器的底层功能实现
│   │   ├── MCDisassembler
│   │   └── MCParser
│   ├── MCA
│   │   ├── HardwareUnits
│   │   └── Stages
│   ├── Object
│   ├── ObjectYAML
│   ├── Option
│   ├── Passes
│   ├── ProfileData
│   │   └── Coverage
│   ├── Remarks
│   ├── Support
│   │   ├── Unix
│   │   └── Windows
│   ├── TableGen                                // TableGen工具的实现
│   ├── Target                                  // 特定目标的实现
│   │   ├── AArch64
│   │   ├── AMDGPU
│   │   ├── ARC
│   │   ├── ARM
│   │   ├── AVR
│   │   ├── BPF
│   │   ├── CSKY
│   │   ├── Hexagon
│   │   ├── Lanai
│   │   ├── M68k
│   │   ├── MSP430
│   │   ├── Mips
│   │   ├── NVPTX
│   │   ├── PowerPC
│   │   ├── RISCV
│   │   ├── Sparc
│   │   ├── SystemZ
│   │   ├── VE
│   │   ├── WebAssembly
│   │   ├── X86
│   │   └── XCore
│   ├── Testing
│   │   └── Support
│   ├── TextAPI
│   ├── ToolDrivers
│   │   ├── llvm-dlltool
│   │   └── llvm-lib
│   ├── Transforms
│   │   ├── AggressiveInstCombine
│   │   ├── CFGuard
│   │   ├── Coroutines
│   │   ├── Hello
│   │   ├── IPO
│   │   ├── InstCombine
│   │   ├── Instrumentation
│   │   ├── ObjCARC
│   │   ├── Scalar
│   │   ├── Utils
│   │   └── Vectorize
│   ├── WindowsManifest
│   └── XRay
```

#### projects

```
├── projects
```

#### resources

```
├── resources
```

#### runtimes

```
├── runtimes
```

#### test

```
├── test
│   ├── Analysis
│   │   ├── AliasSet
│   │   ├── AssumptionCache
│   │   ├── BasicAA
│   │   ├── BlockFrequencyInfo
│   │   ├── BranchProbabilityInfo
│   │   ├── CFLAliasAnalysis
│   │   ├── CallGraph
│   │   ├── CostModel
│   │   ├── DDG
│   │   ├── Delinearization
│   │   ├── DemandedBits
│   │   ├── DependenceAnalysis
│   │   ├── DivergenceAnalysis
│   │   ├── DominanceFrontier
│   │   ├── Dominators
│   │   ├── FunctionPropertiesAnalysis
│   │   ├── GlobalsModRef
│   │   ├── IRSimilarityIdentifier
│   │   ├── IVUsers
│   │   ├── LazyCallGraph
│   │   ├── LazyValueAnalysis
│   │   ├── LegacyDivergenceAnalysis
│   │   ├── Lint
│   │   ├── LoopAccessAnalysis
│   │   ├── LoopCacheAnalysis
│   │   ├── LoopInfo
│   │   ├── LoopNestAnalysis
│   │   ├── MemoryDependenceAnalysis
│   │   ├── MemorySSA
│   │   ├── MustExecute
│   │   ├── PhiValues
│   │   ├── PostDominators
│   │   ├── ProfileSummary
│   │   ├── RegionInfo
│   │   ├── ScalarEvolution
│   │   ├── ScopedNoAliasAA
│   │   ├── StackSafetyAnalysis
│   │   ├── TypeBasedAliasAnalysis
│   │   └── ValueTracking
│   ├── Assembler
│   ├── Bindings
│   │   ├── Go
│   │   ├── OCaml
│   │   └── llvm-c
│   ├── Bitcode
│   │   └── Inputs
│   ├── BugPoint
│   ├── CodeGen
│   │   ├── AArch64
│   │   ├── AMDGPU
│   │   ├── ARC
│   │   ├── ARM
│   │   ├── AVR
│   │   ├── BPF
│   │   ├── Generic
│   │   ├── Hexagon
│   │   ├── Inputs
│   │   ├── Lanai
│   │   ├── M68k
│   │   ├── MIR
│   │   ├── MSP430
│   │   ├── Mips
│   │   ├── NVPTX
│   │   ├── PowerPC
│   │   ├── RISCV
│   │   ├── SPARC
│   │   ├── SystemZ
│   │   ├── Thumb
│   │   ├── Thumb2
│   │   ├── VE
│   │   ├── WebAssembly
│   │   ├── WinCFGuard
│   │   ├── WinEH
│   │   ├── X86
│   │   └── XCore
│   ├── DebugInfo
│   │   ├── AArch64
│   │   ├── AMDGPU
│   │   ├── ARM
│   │   ├── BPF
│   │   ├── COFF
│   │   ├── Generic
│   │   ├── Inputs
│   │   ├── Lanai
│   │   ├── MIR
│   │   ├── MSP430
│   │   ├── Mips
│   │   ├── NVPTX
│   │   ├── PDB
│   │   ├── PowerPC
│   │   ├── RISCV
│   │   ├── Sparc
│   │   ├── Symbolize
│   │   ├── SystemZ
│   │   ├── WebAssembly
│   │   ├── X86
│   │   └── XCOFF
│   ├── Demangle
│   ├── Examples
│   │   ├── IRTransforms
│   │   ├── Kaleidoscope
│   │   └── OrcV2Examples
│   ├── ExecutionEngine
│   │   ├── Interpreter
│   │   ├── JITLink
│   │   ├── MCJIT
│   │   ├── OrcLazy
│   │   └── RuntimeDyld
│   ├── Feature
│   │   └── OperandBundles
│   ├── FileCheck
│   │   ├── Inputs
│   │   ├── comment
│   │   ├── dump-input
│   │   └── match-time-error-propagation
│   ├── Instrumentation
│   │   ├── AddressSanitizer
│   │   ├── BoundsChecking
│   │   ├── DataFlowSanitizer
│   │   ├── HWAddressSanitizer
│   │   ├── HeapProfiler
│   │   ├── InstrOrderFile
│   │   ├── InstrProfiling
│   │   ├── MemorySanitizer
│   │   ├── PoisonChecking
│   │   ├── SanitizerCoverage
│   │   └── ThreadSanitizer
│   ├── Integer
│   ├── JitListener
│   ├── LTO
│   │   ├── ARM
│   │   ├── Resolution
│   │   └── X86
│   ├── Linker
│   │   └── Inputs
│   ├── MC
│   │   ├── AArch64
│   │   ├── AMDGPU
│   │   ├── ARM
│   │   ├── AVR
│   │   ├── AsmParser
│   │   ├── BPF
│   │   ├── COFF
│   │   ├── CSKY
│   │   ├── Disassembler
│   │   ├── ELF
│   │   ├── Hexagon
│   │   ├── Lanai
│   │   ├── M68k
│   │   ├── MSP430
│   │   ├── MachO
│   │   ├── Mips
│   │   ├── PowerPC
│   │   ├── RISCV
│   │   ├── Sparc
│   │   ├── SystemZ
│   │   ├── VE
│   │   ├── WebAssembly
│   │   ├── X86
│   │   └── XCOFF
│   ├── MachineVerifier
│   ├── Object
│   │   ├── AArch64
│   │   ├── AMDGPU
│   │   ├── ARM
│   │   ├── BPF
│   │   ├── Inputs
│   │   ├── Lanai
│   │   ├── Mips
│   │   ├── RISCV
│   │   └── X86
│   ├── ObjectYAML
│   │   ├── COFF
│   │   ├── CodeView
│   │   ├── ELF
│   │   ├── MachO
│   │   └── wasm
│   ├── Other
│   │   ├── ChangePrinters
│   │   ├── Inputs
│   │   └── X86
│   ├── SafepointIRVerifier
│   ├── Support
│   ├── SymbolRewriter
│   ├── TableGen
│   │   ├── Common
│   │   ├── FixedLenDecoderEmitter
│   │   └── GICombinerEmitter
│   ├── ThinLTO
│   │   └── X86
│   ├── Transforms
│   │   ├── ADCE
│   │   ├── AddDiscriminators
│   │   ├── AggressiveInstCombine
│   │   ├── AlignmentFromAssumptions
│   │   ├── ArgumentPromotion
│   │   ├── AtomicExpand
│   │   ├── Attributor
│   │   ├── BDCE
│   │   ├── BlockExtractor
│   │   ├── BranchFolding
│   │   ├── CallSiteSplitting
│   │   ├── CalledValuePropagation
│   │   ├── CanonicalizeAliases
│   │   ├── CanonicalizeFreezeInLoops
│   │   ├── CodeExtractor
│   │   ├── CodeGenPrepare
│   │   ├── ConstantHoisting
│   │   ├── ConstantMerge
│   │   ├── ConstraintElimination
│   │   ├── Coroutines
│   │   ├── CorrelatedValuePropagation
│   │   ├── CrossDSOCFI
│   │   ├── DCE
│   │   ├── DFAJumpThreading
│   │   ├── DeadArgElim
│   │   ├── DeadStoreElimination
│   │   ├── DivRemPairs
│   │   ├── EarlyCSE
│   │   ├── EliminateAvailableExternally
│   │   ├── EntryExitInstrumenter
│   │   ├── ExpandMemCmp
│   │   ├── FixIrreducible
│   │   ├── Float2Int
│   │   ├── ForcedFunctionAttrs
│   │   ├── FunctionAttrs
│   │   ├── FunctionImport
│   │   ├── FunctionSpecialization
│   │   ├── GCOVProfiling
│   │   ├── GVN
│   │   ├── GVNHoist
│   │   ├── GVNSink
│   │   ├── GlobalDCE
│   │   ├── GlobalMerge
│   │   ├── GlobalOpt
│   │   ├── GlobalSplit
│   │   ├── GuardWidening
│   │   ├── HardwareLoops
│   │   ├── HelloNew
│   │   ├── HotColdSplit
│   │   ├── IRCE
│   │   ├── IROutliner
│   │   ├── IndVarSimplify
│   │   ├── IndirectBrExpand
│   │   ├── InferAddressSpaces
│   │   ├── InferFunctionAttrs
│   │   ├── Inline
│   │   ├── InstCombine
│   │   ├── InstMerge
│   │   ├── InstNamer
│   │   ├── InstSimplify
│   │   ├── InterleavedAccess
│   │   ├── Internalize
│   │   ├── JumpThreading
│   │   ├── LCSSA
│   │   ├── LICM
│   │   ├── LoadStoreVectorizer
│   │   ├── LoopBoundSplit
│   │   ├── LoopDataPrefetch
│   │   ├── LoopDeletion
│   │   ├── LoopDistribute
│   │   ├── LoopFlatten
│   │   ├── LoopFusion
│   │   ├── LoopIdiom
│   │   ├── LoopInstSimplify
│   │   ├── LoopInterchange
│   │   ├── LoopLoadElim
│   │   ├── LoopPredication
│   │   ├── LoopReroll
│   │   ├── LoopRotate
│   │   ├── LoopSimplify
│   │   ├── LoopSimplifyCFG
│   │   ├── LoopStrengthReduce
│   │   ├── LoopTransformWarning
│   │   ├── LoopUnroll
│   │   ├── LoopUnrollAndJam
│   │   ├── LoopUnswitch
│   │   ├── LoopVectorize
│   │   ├── LoopVersioning
│   │   ├── LoopVersioningLICM
│   │   ├── LowerAtomic
│   │   ├── LowerConstantIntrinsics
│   │   ├── LowerExpectIntrinsic
│   │   ├── LowerGuardIntrinsic
│   │   ├── LowerInvoke
│   │   ├── LowerMatrixIntrinsics
│   │   ├── LowerSwitch
│   │   ├── LowerTypeTests
│   │   ├── LowerWidenableCondition
│   │   ├── MakeGuardsExplicit
│   │   ├── Mem2Reg
│   │   ├── MemCpyOpt
│   │   ├── MergeFunc
│   │   ├── MergeICmps
│   │   ├── MetaRenamer
│   │   ├── NameAnonGlobals
│   │   ├── NaryReassociate
│   │   ├── NewGVN
│   │   ├── ObjCARC
│   │   ├── OpenMP
│   │   ├── PGOProfile
│   │   ├── PartialInlining
│   │   ├── PartiallyInlineLibCalls
│   │   ├── PhaseOrdering
│   │   ├── PlaceSafepoints
│   │   ├── PreISelIntrinsicLowering
│   │   ├── PruneEH
│   │   ├── Reassociate
│   │   ├── Reg2Mem
│   │   ├── RelLookupTableConverter
│   │   ├── RewriteStatepointsForGC
│   │   ├── SCCP
│   │   ├── SLPVectorizer
│   │   ├── SROA
│   │   ├── SafeStack
│   │   ├── SampleProfile
│   │   ├── ScalarizeMaskedMemIntrin
│   │   ├── Scalarizer
│   │   ├── SeparateConstOffsetFromGEP
│   │   ├── SimpleLoopUnswitch
│   │   ├── SimplifyCFG
│   │   ├── Sink
│   │   ├── SpeculativeExecution
│   │   ├── StraightLineStrengthReduce
│   │   ├── StripDeadPrototypes
│   │   ├── StripSymbols
│   │   ├── StructurizeCFG
│   │   ├── SyntheticCountsPropagation
│   │   ├── TailCallElim
│   │   ├── ThinLTOBitcodeWriter
│   │   ├── TypePromotion
│   │   ├── UnifyFunctionExitNodes
│   │   ├── UnifyLoopExits
│   │   ├── Util
│   │   ├── VectorCombine
│   │   └── WholeProgramDevirt
│   ├── Unit
│   ├── Verifier
│   │   ├── AMDGPU
│   │   ├── ARM
│   │   ├── Mips
│   │   └── SystemZ
│   ├── YAMLParser
│   └── tools
│       ├── UpdateTestChecks
│       ├── dsymutil
│       ├── gold
│       ├── llc
│       ├── llvm-ar
│       ├── llvm-as
│       ├── llvm-bcanalyzer
│       ├── llvm-cfi-verify
│       ├── llvm-config
│       ├── llvm-cov
│       ├── llvm-cvtres
│       ├── llvm-cxxdump
│       ├── llvm-cxxfilt
│       ├── llvm-cxxmap
│       ├── llvm-diff
│       ├── llvm-dis
│       ├── llvm-dlltool
│       ├── llvm-dwarfdump
│       ├── llvm-dwp
│       ├── llvm-exegesis
│       ├── llvm-extract
│       ├── llvm-gsymutil
│       ├── llvm-ifs
│       ├── llvm-isel-fuzzer
│       ├── llvm-jitlink
│       ├── llvm-lib
│       ├── llvm-libtool-darwin
│       ├── llvm-link
│       ├── llvm-lipo
│       ├── llvm-lit
│       ├── llvm-locstats
│       ├── llvm-lto
│       ├── llvm-lto2
│       ├── llvm-mc
│       ├── llvm-mca
│       ├── llvm-ml
│       ├── llvm-modextract
│       ├── llvm-mt
│       ├── llvm-nm
│       ├── llvm-objcopy
│       ├── llvm-objdump
│       ├── llvm-opt-fuzzer
│       ├── llvm-opt-report
│       ├── llvm-original-di-preservation
│       ├── llvm-pdbutil
│       ├── llvm-profdata
│       ├── llvm-profgen
│       ├── llvm-ranlib
│       ├── llvm-rc
│       ├── llvm-readobj
│       ├── llvm-reduce
│       ├── llvm-rtdyld
│       ├── llvm-sim
│       ├── llvm-size
│       ├── llvm-split
│       ├── llvm-stress
│       ├── llvm-strings
│       ├── llvm-symbolizer
│       ├── llvm-tapi-diff
│       ├── llvm-undname
│       ├── llvm-xray
│       ├── lto
│       ├── not
│       ├── obj2yaml
│       ├── opt-viewer
│       ├── sancov
│       ├── sanstats
│       ├── split-file
│       └── yaml2obj
```

#### tools

```
├── tools
│   ├── bugpoint
│   ├── bugpoint-passes
│   ├── dsymutil
│   ├── gold
│   ├── llc
│   ├── lli
│   │   └── ChildTarget
│   ├── llvm-ar
│   ├── llvm-as
│   ├── llvm-as-fuzzer
│   ├── llvm-bcanalyzer
│   ├── llvm-c-test
│   ├── llvm-cat
│   ├── llvm-cfi-verify
│   │   └── lib
│   ├── llvm-config
│   ├── llvm-cov
│   ├── llvm-cvtres
│   ├── llvm-cxxdump
│   ├── llvm-cxxfilt
│   ├── llvm-cxxmap
│   ├── llvm-diff
│   │   └── lib
│   ├── llvm-dis
│   ├── llvm-dwarfdump
│   │   └── fuzzer
│   ├── llvm-dwp
│   ├── llvm-exegesis
│   │   └── lib
│   ├── llvm-extract
│   ├── llvm-go
│   ├── llvm-gsymutil
│   ├── llvm-ifs
│   ├── llvm-isel-fuzzer
│   ├── llvm-itanium-demangle-fuzzer
│   ├── llvm-jitlink
│   │   └── llvm-jitlink-executor
│   ├── llvm-jitlistener
│   ├── llvm-libtool-darwin
│   ├── llvm-link
│   ├── llvm-lipo
│   ├── llvm-lto
│   ├── llvm-lto2
│   ├── llvm-mc
│   ├── llvm-mc-assemble-fuzzer
│   ├── llvm-mc-disassemble-fuzzer
│   ├── llvm-mca
│   │   └── Views
│   ├── llvm-microsoft-demangle-fuzzer
│   ├── llvm-ml
│   ├── llvm-modextract
│   ├── llvm-mt
│   ├── llvm-nm
│   ├── llvm-objcopy
│   │   ├── COFF
│   │   ├── ELF
│   │   ├── MachO
│   │   └── wasm
│   ├── llvm-objdump
│   ├── llvm-opt-fuzzer
│   ├── llvm-opt-report
│   ├── llvm-pdbutil
│   ├── llvm-profdata
│   ├── llvm-profgen
│   ├── llvm-rc
│   ├── llvm-readobj
│   ├── llvm-reduce
│   │   └── deltas
│   ├── llvm-rtdyld
│   ├── llvm-rust-demangle-fuzzer
│   ├── llvm-shlib
│   ├── llvm-sim
│   ├── llvm-size
│   ├── llvm-special-case-list-fuzzer
│   ├── llvm-split
│   ├── llvm-stress
│   ├── llvm-strings
│   ├── llvm-symbolizer
│   ├── llvm-tapi-diff
│   ├── llvm-undname
│   ├── llvm-xray
│   ├── llvm-yaml-numeric-parser-fuzzer
│   ├── llvm-yaml-parser-fuzzer
│   ├── lto
│   ├── msbuild
│   │   ├── Platformx64
│   │   └── Platformx86
│   ├── obj2yaml
│   ├── opt
│   ├── opt-viewer
│   ├── remarks-shlib
│   ├── sancov
│   ├── sanstats
│   ├── split-file
│   ├── verify-uselistorder
│   ├── vfabi-demangle-fuzzer
│   ├── xcode-toolchain
│   └── yaml2obj
```

#### unittests

```
├── unittests
│   ├── ADT
│   ├── Analysis
│   │   └── Inputs
│   ├── AsmParser
│   ├── BinaryFormat
│   ├── Bitcode
│   ├── Bitstream
│   ├── CodeGen
│   │   └── GlobalISel
│   ├── DebugInfo
│   │   ├── CodeView
│   │   ├── DWARF
│   │   ├── GSYM
│   │   ├── MSF
│   │   └── PDB
│   ├── Demangle
│   ├── ExecutionEngine
│   │   ├── JITLink
│   │   ├── MCJIT
│   │   └── Orc
│   ├── FileCheck
│   ├── Frontend
│   ├── FuzzMutate
│   ├── IR
│   ├── InterfaceStub
│   ├── LineEditor
│   ├── Linker
│   ├── MC
│   │   ├── AMDGPU
│   │   └── SystemZ
│   ├── MI
│   ├── MIR
│   ├── Object
│   ├── ObjectYAML
│   ├── Option
│   ├── Passes
│   ├── ProfileData
│   ├── Remarks
│   ├── Support
│   │   ├── CommandLineInit
│   │   └── DynamicLibrary
│   ├── TableGen
│   ├── Target
│   │   ├── AArch64
│   │   ├── AMDGPU
│   │   ├── ARM
│   │   ├── PowerPC
│   │   ├── WebAssembly
│   │   └── X86
│   ├── TextAPI
│   ├── Transforms
│   │   ├── IPO
│   │   ├── Scalar
│   │   ├── Utils
│   │   └── Vectorize
│   ├── XRay
│   └── tools
│       ├── llvm-cfi-verify
│       ├── llvm-exegesis
│       └── llvm-profgen
```

#### utils

```
└── utils
    ├── FileCheck
    ├── KillTheDoctor
    ├── LLVMVisualizers
    ├── Misc
    ├── PerfectShuffle
    ├── Reviewing
    ├── TableGen
    │   └── GlobalISel
    ├── Target
    │   └── ARM
    ├── UpdateTestChecks
    ├── benchmark
    │   ├── cmake
    │   ├── docs
    │   ├── include
    │   ├── src
    │   ├── test
    │   └── tools
    ├── bugpoint
    ├── count
    ├── crosstool
    │   └── ARM
    ├── docker
    │   ├── debian8
    │   ├── example
    │   ├── nvidia-cuda
    │   └── scripts
    ├── emacs
    ├── fpcmp
    ├── gdb-scripts
    ├── git
    ├── gn
    │   ├── build
    │   ├── docs
    │   └── secondary
    ├── jedit
    ├── kate
    ├── lint
    ├── lit
    │   ├── examples
    │   ├── lit
    │   ├── tests
    │   └── utils
    ├── llvm-lit
    ├── llvm-locstats
    ├── not
    ├── release
    ├── rsp_bisect_test
    ├── sanitizers
    ├── testgen
    ├── textmate
    │   └── TableGen.tmbundle
    ├── unittest
    │   ├── UnitTestMain
    │   ├── googlemock
    │   └── googletest
    ├── valgrind
    ├── vim
    │   ├── ftdetect
    │   ├── ftplugin
    │   ├── indent
    │   └── syntax
    ├── vscode
    │   └── llvm
    └── yaml-bench
```
