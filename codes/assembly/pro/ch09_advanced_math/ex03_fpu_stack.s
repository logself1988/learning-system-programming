# An example of working with the FPU stack

.section .data
value1:
    .int 40
value2:
    .float 92.4405
value3:
    .double 221.440321

.section .bss
    .lcomm int1, 4
    .lcomm control, 2
    .lcomm status, 2
    .lcomm result, 4

.section .text
.globl _start
_start:
    finit               /* initialize FPU */
    fstcw control       /* store FPU control register to memory */
    fstsw status        /* store FPU status register to memory */

    filds value1        /* load 4B integer to FPU stack */
    fists int1          /* store FPU stack top value to memory */
    flds value2         /* load 4B single precision float to FPU stack */
    fldl value3         /* load 8B double precision float to FPU stack */

    fst %st(4)          /* load ST0 to ST4 */
    fxch %st(1)         /* exchange ST0 with ST1 */
    fstps result        /* (cyclic) pop and store FPU stack top to memory */

    movl $1, %eax
    movl $0, %ebx
    int $0x80
