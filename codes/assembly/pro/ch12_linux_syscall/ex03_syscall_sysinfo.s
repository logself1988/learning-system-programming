# An example of system call sysinfo()

# $ man 2 sysinfo
# struct sysinfo {
#    long uptime;             /* Seconds since boot */
#    unsigned long loads[3];  /* 1, 5, and 15 minute load averages */
#    unsigned long totalram;  /* Total usable main memory size */
#    unsigned long freeram;   /* Available memory size */
#    unsigned long sharedram; /* Amount of shared memory */
#    unsigned long bufferram; /* Memory used by buffers */
#    unsigned long totalswap; /* Total swap space size */
#    unsigned long freeswap;  /* Swap space still available */
#    unsigned short procs;    /* Number of current processes */
#    unsigned long totalhigh; /* Total high memory size */
#    unsigned long freehigh;  /* Available high memory size */
#    unsigned int mem_unit;   /* Memory unit size in bytes */
#    char _f[20-2*sizeof(long)-sizeof(int)];
#                             /* Padding to 64 bytes */
# };


.section .data
result:
uptime: .long 0
load1: .long 0
load5: .long 0
load15: .long 0
totalram: .long 0
freeram: .long 0
sharedram: .long 0
bufferram: .long 0
totalswap: .long 0
freeswap: .long 0
procs: .byte 0x00, 0x00
totalhigh: .long 0
freehigh: .long 0
mem_unit: .int 0

.section .text
.globl _start
_start:
    movl $result, %ebx
    movl $116, %eax
    int $0x80

    movl $0, %ebx
    movl $1, %eax
    int $0x80
