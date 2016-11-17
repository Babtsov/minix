#include <lib.h>    // _syscall & message
#include <unistd.h> // plog function prototypes

#define plog_cmd    m2_i1
#define plog_pid    m2_i2

enum {STOP_PLOG = 0, START_PLOG = 1, PRINT_PLOG = 2};

int plog_state_start(int PID) {
    message m;
    m.plog_cmd = START_PLOG;
    m.plog_pid = PID;
    return _syscall(PM_PROC_NR, PLOG, &m);
}

int plog_state_stop(int PID) {
    message m;
    m.plog_cmd = STOP_PLOG;
    m.plog_pid = PID;
    return _syscall(PM_PROC_NR, PLOG, &m);
}
int plog_print_transitions(void) {
    message m;
    m.plog_cmd = PRINT_PLOG;
    return _syscall(PM_PROC_NR, PLOG, &m);
}
