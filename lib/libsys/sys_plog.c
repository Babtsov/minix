#include "syslib.h"
#include "stdbool.h"

int sys_plog(pid_t proc_pid, int proc_index, bool enabled, void * plog_ptr) {
    message m;
    m.m1_i1 = proc_pid;
    m.m1_i2 = proc_index;
    m.m1_i3 = enabled;
    m.m1_p1 = plog_ptr;
    return(_kernel_call(SYS_PLOG, &m));
}
