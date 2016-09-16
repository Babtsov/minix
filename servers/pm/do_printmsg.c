#include <stdio.h>
#include "pm.h" // provides the m_in
#include "mproc.h"

int do_printmsg() {
    int i = m_in.m1_i1;
    printf("System call do_printmsg called with the value %d\n", i);
    mp->mp_reply.m1_i1 = i + 1;
    return 0;
}
