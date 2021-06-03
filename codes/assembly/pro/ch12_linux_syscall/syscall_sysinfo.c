// gcc -o syscall_sysinfo syscall_sysinfo.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

int main(int argc, char **argv)
{
    printf("sizeof(long)=%ld\n", sizeof(long));
    printf("sizeof(unsigned long)=%ld\n", sizeof(unsigned long));
    printf("sizeof(unsigned short)=%ld\n", sizeof(unsigned short));
    printf("sizeof(unsigned int)=%ld\n", sizeof(int));
    printf("sizeof(struct sysinfo)=%ld\n", sizeof(struct sysinfo));
    printf("\n");

    struct sysinfo si;
    int res = sysinfo(&si);
    if (res == -1)
    {
        printf("Call sysinfo failed\n");
        exit(1);
    }

    printf("uptime: %ld\n", si.uptime);
    printf("loads: %ld %ld %ld\n", si.loads[0], si.loads[1], si.loads[2]);
    printf("totalram: %ld\n", si.totalram);
    printf("freeram: %ld\n", si.freeram);
    printf("sharedram: %ld\n", si.sharedram);
    printf("bufferram: %ld\n", si.bufferram);
    printf("totalswap: %ld\n", si.totalswap);
    printf("freeswap: %ld\n", si.freeswap);
    printf("procs: %d\n", si.procs);
    printf("totalhigh: %ld\n", si.totalhigh);
    printf("freehigh: %ld\n", si.freehigh);
    printf("mem_unit: %d\n", si.mem_unit);
    
    return 0;
}

