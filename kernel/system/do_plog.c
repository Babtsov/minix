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
    if (pid == INT_MIN && proc_index == INT_MIN) { // serve request to print plog_pid
        printf("PLOG TABLE\n");
        for (int i = 0; i < PLOG_BUFFER_SIZE; i++) {
            struct plog_entry * entry = &(plog.buffer[i]);
            char * from_state = fmt_proc_state(entry->from);
            char * to_state = fmt_proc_state(entry->to);
            printf("PID%d\t%ld\t%s\t%s\n",entry->proc_pid, entry->time_stamp, from_state, to_state);
        }  
        return(OK);
    }
    struct proc * entry = proc_addr(proc_index);
    entry->plog_pid = (enabled) ? pid : INT_MIN;
    printf("kernel do_plog: name: %s pid: %d enabled %d\n", entry->p_name, pid, enabled);
    return(OK);
}
