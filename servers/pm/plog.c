#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include "pm.h"
#include "mproc.h"

#define plog_cmd                m2_i1 
#define plog_int                m2_i2
#define plog_ctime              m2_l1
#define plog_ttime              m2_l2
enum {STOP_PLOG = 0, START_PLOG = 1, RESET_PLOG = 2, GET_PLOG_SIZE = 3, GET_PLOG_BYINDX = 4, GET_PLOG_BYPID = 5};

struct plog_cell * get_plog(pid_t process_id) {
    if (process_id < 0 || process_id > NR_PROCS) 
        return NULL; 
    for (int i = 0; i < plog_table.table_size; i++) {
        struct plog_cell * cell = &plog_table.content[i];
        if (cell->process_id == process_id)
            return cell;
    }
    return NULL;
}

int do_plog(void) {
    int command = m_in.plog_cmd;
    switch (command) {
        case STOP_PLOG:
            printf("plog was called with STOP_PLOG\n");
            plog_table.enabled = false;
            return 0;

        case START_PLOG:
            printf("plog was called with START_PLOG\n");
            plog_table.enabled = true;
            return 0;

        case RESET_PLOG:
            printf("plog was called with RESET_PLOG\n");
            int old_state = plog_table.enabled;
            memset(&plog_table, 0, sizeof(plog_table));
            plog_table.enabled = old_state;
            return 0;

        case GET_PLOG_SIZE:
            printf("plog was called with GET_PLOG_SIZE\n");
            mp->mp_reply.plog_int = PLOG_MAX_TABLE_SIZE;
            return 0;

        case GET_PLOG_BYINDX:
            printf("plog was called with GET_PLOG_BYINDX\n");
            int index = m_in.plog_int;
            if (index < 0 || index > PLOG_MAX_TABLE_SIZE - 1) 
               return -3;
            mp->mp_reply.plog_ctime = plog_table.content[index].c_time;
            mp->mp_reply.plog_ttime = plog_table.content[index].t_time;
            if (plog_table.table_size < PLOG_MAX_TABLE_SIZE && index >= plog_table.current_indx)
                return -2; 
            return 0;

        case GET_PLOG_BYPID:
            printf("plog was called with GET_PLOG_BYPID\n");
            struct plog_cell * cell = get_plog(m_in.plog_int);
            if (!cell)
                return -1;
            mp->mp_reply.plog_ctime = cell->c_time;
            mp->mp_reply.plog_ttime = cell->t_time;
            return 0;
    } 
    return -1;
}
