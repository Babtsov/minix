#include <lib.h>
#include <unistd.h>

int plog_state_start(int PID) {
    printf("plog state start\n");
    return _syscall(PM_PROC_NR, STATE_LOGGER, &m);
}

int plog_state_stop(int PID) {
    printf("plog state stop\n");
    return _syscall(PM_PROC_NR, STATE_LOGGER, &m);
}
