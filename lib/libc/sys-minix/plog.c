#include <lib.h>    // _syscall & message
#include <unistd.h> // plog function prototypes


#define plog_cmd    m2_i1
#define plog_pid    m2_i2
#define plog_addr   m1_p1   

struct plog_t plog;

enum {STOP_PLOG = 0, START_PLOG = 1, PASS_PLOG_PTR = 2};

struct plog_t * get_plog_ptr() {
    return &plog;
}
int set_plog_ptr() {
    message m;
    m.plog_cmd = PASS_PLOG_PTR;
    m.plog_pid = 0;
    m.plog_addr = &plog;
    return _syscall(PM_PROC_NR, PLOG, &m);
}

int plog_state_start(int PID) {
    message m;
    m.plog_cmd = START_PLOG;
    m.plog_pid = PID;
    m.plog_addr = NULL;
    return _syscall(PM_PROC_NR, PLOG, &m);
}

int plog_state_stop(int PID) {
    message m;
    m.plog_cmd = STOP_PLOG;
    m.plog_pid = PID;
    m.plog_addr = NULL;
    return _syscall(PM_PROC_NR, PLOG, &m);
}
