// one of those allows us to use printf?
#include "kernel/system.h"
#include <minix/endpoint.h>

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <libexec.h>
#include <a.out.h>
#include <minix/com.h>
#include <machine/vmparam.h>
#include <minix/u64.h>
#include <minix/type.h>

int do_plog(struct proc *caller_ptr, message *m_ptr) {
    printf("Kernel: hello\n");
    return(OK);
}
