#include "kernel/system.h"
#include <minix/endpoint.h>

int do_state_logger(struct proc *caller_ptr, message *m_ptr) {
    prinf("kernel message!\n");
}
