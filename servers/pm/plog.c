#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include "pm.h"
#include "mproc.h"

#define plog_cmd    m2_i1 
#define plog_pid    m2_i2

enum {STOP_PLOG = 0, START_PLOG = 1};

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
void test(void) {
    int F = open("/tmp/qaz.txt",O_APPEND);
    char buff[10];
    int bytes = sprintf(buff,"%d",123);
    dprintf(F,"judge %d",bytes);
}
int do_plog(void) {
    int command = m_in.plog_cmd;
    int pid = m_in.plog_pid;
    int proc_index = -1;
    for (int i = 0; i < NR_PROCS - 1; i++) {
        if (mproc[i].mp_pid == pid) {
            proc_index = i;
            break;
        }
    }
    if (proc_index != -1) printf("PM: proc name: %s\n",mproc[proc_index].mp_name);
    switch (command) {
        case STOP_PLOG:
            printf("PM: STOP_PLOG. pid: %d\n", pid);
            test();
            sys_plog(pid, proc_index, false);
            return 0;

        case START_PLOG:
            printf("PM: START_PLOG. pid: %d\n", pid);
            sys_plog(pid, proc_index, true);
            return 0;

    } 
    return -1;
}
