Codes of Low-Level Programming(LLP): C, Assembly, and Program Execution on Intel® 64 Architecture.


Tools:

- NASM
- GCC
- GDB
- GNU Make
- VSCode Extention: The Netwide Assembler (NASM)

snippets:

```
{
	"NASM main": {
		"prefix": "nasm",
		"body": [
			"%include \"../lib/syscall.inc\"",
			"",
			"section .data",
			"message: db 'hello, world!', 10",
			"",
			"section .text",
			"; syscall arguments: rax, rdi, rsi, rdx, r10, r8, r9",
			"; syscall returns: rax; destroys: rcx, r11",
			"; function arguments: rax, rdi, rsi, rdx, rcx, r8, r9",
			"; function returns: rax, rdx",
			"global _start",
			"_start:",
			"  $1",
			"",
			"  mov rax, NR_EXIT",
			"  xor rdi, rdi",
			"  syscall",
			""
		],
		"description": "NASM main routine."
	}
}
```

Contents:

Part I: Assembly Language and Computer Architecture
ch01: Basic Computer Architecture
ch02: Assembly Language
ch03: Legacy
ch04: Virtual Memory
ch05: Compilation Pipeline
ch06: Interrupts and System Calls
ch07: Models of Computation

Part II: The C Programming Language
ch08: Basics
ch09: Type System
ch10: Code Structure
ch11: Memory
ch12: Syntax, Semantics, and Pragmatics
ch13: Good Code Practices

Part III: Between C and Assembly
ch14: Translation Details
ch15: Shared Objects and Code Models
ch16: Performance
ch17: Multithreading

Part IV: Appendices
ch18: Appendix A. Using gdb
ch19: Appendix B. Using Make
ch20: Appendix C. System Calls
ch21: Appendix D. Performance Tests Information
ch22: Bibliography


Portablility:

- system call number and style: Linux, MacOS(with all parameters each)