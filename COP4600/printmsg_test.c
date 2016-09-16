#include <lib.h> 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {  
    int i = (argc == 2)? atoi(argv[1]) : -1;
    message m; 
    m.m1_i1 = i;
    _syscall(PM_PROC_NR, PRINTMSG, &m);
    printf("the function returned %d\n", m.m1_i1);
}
