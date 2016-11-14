#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include "pm.h"
#include "mproc.h"

#define plog_cmd    m2_i1 
#define plog_pid    m2_i2

enum {STOP_PLOG = 0, START_PLOG = 1};


int do_plog(void) {
    int command = m_in.plog_cmd;
    int pid = m_in.plog_pid;
    switch (command) {
        case STOP_PLOG:
            printf("PM: STOP_PLOG. pid: %d\n", pid);
            sys_plog(pid,0,false);
            return 0;

        case START_PLOG:
            printf("PM: START_PLOG. pid: %d\n", pid);
            sys_plog(pid,0,true);
            return 0;

    } 
    return -1;
}
