#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include "pm.h"
#include "mproc.h"

#define plog_cmd    m2_i1 
#define plog_pid    m2_i2
#define plog_addr   m1_p1

enum {STOP_PLOG = 0, START_PLOG = 1, PASS_PLOG_PTR = 2};

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
    void * req_addr = m_in.plog_addr;
    int proc_index;
    switch (command) {

        case START_PLOG:
            printf("PM: START_PLOG. pid: %d\n", req_pid);
            proc_index = find_proc_slot(req_pid);
            if (proc_index == -1 ) return 1;
            sys_plog(proc_index, proc_index, true, NULL);
            return 0;

        case STOP_PLOG:
            printf("PM: STOP_PLOG. pid: %d\n", req_pid);
            proc_index = find_proc_slot(req_pid);
            if (proc_index == -1 ) return 1;
            sys_plog(proc_index, proc_index, false, NULL);
            return 0;

        case PASS_PLOG_PTR:
            printf("PM: PASS_PLOG_PTR. address: %p\n", req_addr);
            sys_plog(0, 0, false, req_addr);
            return 0;

    } 
    return -1;
}
