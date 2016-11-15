// one of those allows us to use printf?
#include "kernel/system.h"
#include <minix/endpoint.h>

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <minix/type.h>


int do_plog(struct proc *caller_ptr, message *m_ptr) {
    int pid = m_ptr->m1_i1;
    int proc_index = m_ptr->m1_i2;
    bool enabled = m_ptr->m1_i3;
    struct proc * entry = proc_addr(proc_index);
    entry->plog_pid = (enabled) ? pid : INT_MIN;
    printf("kernel do_plog: name: %s pid: %d enabled %d\n", entry->p_name, pid, enabled);
    print_plog();
    return(OK);
}
