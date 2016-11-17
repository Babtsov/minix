#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include "pm.h"
#include "mproc.h"

#define plog_cmd    m2_i1 
#define plog_pid    m2_i2

enum {STOP_PLOG = 0, START_PLOG = 1, PRINT_PLOG = 2};

static int find_proc_slot(int req_pid) {
    int proc_index = -1;
    for (int i = 0; i < NR_PROCS - 1; i++) {
        if (mproc[i].mp_pid == req_pid) {
            proc_index = i;
            break;
        }
    }
    if (proc_index != -1) 
        printf("PM: proc name: %s\n",mproc[proc_index].mp_name);
    else
        printf("PM proc name not found\n");
    return proc_index;
}

int do_plog(void) {
    int command = m_in.plog_cmd;
    int req_pid = m_in.plog_pid;
    int proc_index;
    switch (command) {
        case START_PLOG:
            printf("PM: START_PLOG. pid: %d\n", req_pid);
            proc_index = find_proc_slot(req_pid);
            if (proc_index == -1 ) return 1;
            sys_plog(req_pid, proc_index, true);
            return 0;

        case STOP_PLOG:
            printf("PM: STOP_PLOG. pid: %d\n", req_pid);
            proc_index = find_proc_slot(req_pid);
            if (proc_index == -1 ) return 1;
            sys_plog(req_pid, proc_index, false);
            return 0;

        case PRINT_PLOG:
            sys_plog(INT_MIN, INT_MIN, false);
            return 0;
    } 
    return -1;
}
