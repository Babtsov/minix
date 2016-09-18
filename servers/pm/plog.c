#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include "pm.h"
#include "mproc.h"

#define PLOG_MAX_TABLE_SIZE     1024
#define plog_cmd                m2_i1 
#define plog_int                m2_i2
#define plog_ctime              m2_l1
#define plog_ttime              m2_l2
enum {STOP_PLOG = 0, START_PLOG = 1, RESET_PLOG = 2, GET_PLOG_SIZE = 3, GET_PLOG_BYINDX = 4, GET_PLOG_BYPID = 5};

struct plog_table {
    bool enabled;
    int table_size;
    int current_indx;
    struct plog_pair {pid_t pid; long c_time; long t_time;} content[PLOG_MAX_TABLE_SIZE];
} plog_table;

int do_plog(void) {
    int command = m_in.plog_cmd;
    switch (command) {
        case STOP_PLOG:
            printf("plog was called with STOP_PLOG\n");
            plog_table.enabled = false;
            break;

        case START_PLOG:
            printf("plog was called with START_PLOG\n");
            plog_table.enabled = true;
            break;

        case RESET_PLOG:
            printf("plog was called with RESET_PLOG\n");
            plog_table.current_indx = 0;
            plog_table.table_size = 0;
            break;

        case GET_PLOG_SIZE:
            printf("plog was called with GET_PLOG_SIZE\n");
            mp->mp_reply.plog_int = PLOG_MAX_TABLE_SIZE;
            break;

        case GET_PLOG_BYINDX:
            printf("plog was called with GET_PLOG_BYINDX\n");
            int index = m_in.plog_int;
            /* Verify that the requested index is actually within the allowed 
             * range and that it actually stores valid data (and not garbage)
             */
            if (index < 0 || index > PLOG_MAX_TABLE_SIZE - 1 
                || (plog_table.table_size < PLOG_MAX_TABLE_SIZE && index >= plog_table.current_indx) ) {
               return -3;
            } 
            struct plog_pair * pair = &plog_table.content[index];
            mp->mp_reply.plog_ctime = pair->c_time;
            mp->mp_reply.plog_ttime = pair->t_time;
            break;

        case GET_PLOG_BYPID:
            printf("plog was called with GET_PLOG_BYPID\n");
            int pid = m_in.plog_int;
            for (int i = 0; i < plog_table.table_size; i++) {
                struct plog_pair * pair = &plog_table.content[i];
                if (pair->pid == pid) {
                    mp->mp_reply.plog_ctime = pair->c_time;
                    mp->mp_reply.plog_ttime = pair->t_time;
                    return 0;
                } 
            }
            break;
    } 
    return 0;
}

