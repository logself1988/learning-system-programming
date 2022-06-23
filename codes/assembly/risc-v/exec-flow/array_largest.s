	.file	"array_largest.c"
	.option nopic
	.attribute arch, "rv32i2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	get_largest_number
	.type	get_largest_number, @function
get_largest_number:
	lui	a5,%hi(.LANCHOR0)
	lw	a0,%lo(.LANCHOR0)(a5)
	addi	a5,a5,%lo(.LANCHOR0)
	addi	a3,a5,36
.L3:
	lw	a4,4(a5)
	addi	a5,a5,4
	bge	a0,a4,.L2
	mv	a0,a4
.L2:
	bne	a5,a3,.L3
	ret
	.size	get_largest_number, .-get_largest_number
	.globl	numbers
	.bss
	.align	2
	.set	.LANCHOR0,. + 0
	.type	numbers, @object
	.size	numbers, 40
numbers:
	.zero	40
	.ident	"GCC: (GNU) 10.1.0"
