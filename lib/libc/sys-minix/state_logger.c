#include <lib.h>
#include <unistd.h>
#include <stdio.h>

int plog_state_start(int PID) {
    printf("plog state start\n");
    message m;
    return _syscall(PM_PROC_NR, STATE_LOGGER, &m);
}

int plog_state_stop(int PID) {
    printf("plog state stop\n");
    message m;
    return _syscall(PM_PROC_NR, STATE_LOGGER, &m);
}
