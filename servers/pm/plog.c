#include <stdio.h>

#include "pm.h"
#include "mproc.h"

#define PLOG_TABLE_SIZE     1024
#define plog_cmd            m2_i1 
#define plog_int            m2_i2
#define plog_ctime          m2_l1
#define plog_ttime          m2_l2
enum {STOP_PLOG = 0, START_PLOG = 1, RESET_PLOG = 2, GET_PLOG_SIZE = 3, GET_PLOG_BYINDX = 4, GET_PLOG_BYPID = 5};

struct plog_table {
    int current_indx;
    struct plog_pair { long c_time; long t_time;} content[PLOG_TABLE_SIZE];
} plog_table;

int do_plog(void) {
    int command = m_in.plog_cmd;
    switch(command) {

        case STOP_PLOG:
            printf("plog was called with STOP_PLOG\n");
            break;

        case START_PLOG:
            printf("plog was called with START_PLOG\n");
            break;

        case RESET_PLOG:
            printf("plog was called with RESET_PLOG\n");
            break;

        case GET_PLOG_SIZE:
            printf("plog was called with GET_PLOG_SIZE\n");
            mp->mp_reply.plog_int = PLOG_TABLE_SIZE;
            break;

        case GET_PLOG_BYINDX:
            printf("plog was called with GET_PLOG_BYINDX\n");
            int index = m_in.plog_int;
            struct plog_pair * pair = &plog_table.content[index];
            mp->mp_reply.plog_ctime = pair->c_time;
            mp->mp_reply.plog_ttime = pair->t_time;
            break;

        case GET_PLOG_BYPID:
            printf("plog was called with GET_PLOG_BYPID\n");
            int pid = m_in.plog_int;
            break;

    }    
    return 0;
}

