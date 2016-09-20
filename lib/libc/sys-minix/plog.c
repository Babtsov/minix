/* plog lib calls implementation */

#include <lib.h> // _syscall & message
#include <unistd.h>

#define plog_cmd    m2_i1 
#define plog_int    m2_i2
#define plog_ctime  m2_l1
#define plog_ttime  m2_l2

enum {STOP_PLOG = 0, START_PLOG = 1, RESET_PLOG = 2, GET_PLOG_SIZE = 3, GET_PLOG_BYINDX = 4, GET_PLOG_BYPID = 5};

void stop_plog(void) {
    message m;
    m.plog_cmd = STOP_PLOG;
    _syscall(PM_PROC_NR, PLOG, &m);
}

void start_plog(void) {
    message m;
    m.plog_cmd = START_PLOG;
    _syscall(PM_PROC_NR, PLOG, &m);
}

void reset_plog(void) {
    message m;
    m.plog_cmd = RESET_PLOG;
    _syscall(PM_PROC_NR, PLOG, &m);
}

int get_plog_size(void) {
    message m;
    m.plog_cmd = GET_PLOG_SIZE;
    _syscall(PM_PROC_NR, PLOG, &m);
    return m.plog_int;
}

int get_plog_byPID(int pid, long * c_time, long * t_time){
    message m;
    m.plog_cmd = GET_PLOG_BYPID;
    m.plog_int = pid;
    _syscall(PM_PROC_NR, PLOG, &m);
    *c_time = m.plog_ctime;
    *t_time = m.plog_ttime;
    return 8;
}

int get_plog_byindex(int index, long * c_time, long * t_time){
    message m;
    m.plog_cmd = GET_PLOG_BYINDX;
    m.plog_int = index;
    int valid = _syscall(PM_PROC_NR, PLOG, &m);
    *c_time = m.plog_ctime;
    *t_time = m.plog_ttime;
   return valid;
}
