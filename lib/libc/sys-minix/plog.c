#include <lib.h>    // _syscall & message
#include <unistd.h> // plog function prototypes


#define plog_cmd    m2_i1
#define plog_pid    m2_i2
#define plog_addr   m1_p1   

enum proc_state {PROC_READY = 0, PROC_RUNNING = 1}; 
#define PLOG_BUFFER_SIZE 1024
struct plog_t {
    int kernel_index;
    int logger_index;
    struct plog_entry {
        int proc_pid; 
        long time_stamp; 
        enum proc_state from; 
        enum proc_state to; 
    } buffer[PLOG_BUFFER_SIZE];
} plog;

enum {STOP_PLOG = 0, START_PLOG = 1};

struct plog_t * get_plog() {
    return &plog;
}

int plog_state_start(int PID) {
    message m;
    m.plog_cmd = START_PLOG;
    m.plog_pid = PID;
    m.plog_addr = &plog;
    return _syscall(PM_PROC_NR, PLOG, &m);
}

int plog_state_stop(int PID) {
    message m;
    m.plog_cmd = STOP_PLOG;
    m.plog_pid = PID;
    m.plog_addr = &plog;
    return _syscall(PM_PROC_NR, PLOG, &m);
}
