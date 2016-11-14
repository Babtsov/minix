// one of those allows us to use printf?
#include "kernel/system.h"
#include <minix/endpoint.h>

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <minix/type.h>

int do_plog(struct proc *caller_ptr, message *m_ptr) {
    int pid = m_ptr->m1_i1;
    int proc_index = m_ptr->m1_i2;
    bool enabled = m_ptr->m1_i3;
    printf("kernel: pid: %d index: %d. enabled %d\n",pid, proc_index, enabled);
    printf("kernel: bye\n");     
    return(OK);
}
