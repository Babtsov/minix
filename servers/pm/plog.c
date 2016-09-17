#include <stdio.h>

#include "pm.h"
#include "param.h"

#define plog_cmd    m2_i1 
#define plog_num    m2_i2
#define plog_ctime  m2_l1
#define plog_ttime  m2_l2
enum {STOP_PLOG = 0, START_PLOG = 1, RESET_PLOG = 2, GET_PLOG_SIZE = 3, GET_PLOG_BYINDX = 4, GET_PLOG_BYPID = 5};

int do_plog(void) {
    int command = m_in.plog_cmd;
    switch(command) {
        case STOP_PLOG:
            printf("plog was called with STOP_PLOG\n");
            break;

        case GET_PLOG_BYINDX:
            printf("plog was called with GET_PLOG_BY_INDX\n");
            break;
    }    
    return -9;
}

