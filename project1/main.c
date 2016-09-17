#include <stdio.h> // printf



//func prototypes to be included in /usr/src/include/unistd.h

/*
 * Turns recording off; it is not an error if recording is already off.
 */
void stop_plog(); 

/* 
 * Turns recording on; it is not an error if recording is already on.
 */
void start_plog(); 

/* 
 * Causes all entries to be cleared.
 */
void reset_plog(); 

/*
 * Returns the size of the circular buffer
 */
int get_plog_size(); 

/*
 * Takes the PID whose entry values are desired as the first argument, with pointers to 
 * store the time in seconds since 12:00am Jan 1, 1970  for creation time and termination 
 * time. If the PID is not present in any entry, then the library call shall return an error value of
 * 2 to indicate PID not found.
 */
int get_plog_byPID(int pid, long * c_time, long * t_time);

/* 
 * Takes an index for the entry to read as the first argument, with pointers to store the time in
 * seconds since 12:00am Jan 1, 1970 for creation time and termination time.  If the index is 
 * negative or too large then it shall return an error value of 3 to indicate index out of range.
 */
int get_plog_byindex(int index, long * c_time, long * t_time);

enum {STOP_PLOG = 0, START_PLOG = 1, RESET_PLOG = 2, GET_PLOG_SIZE = 3, GET_PLOG_BYINDX = 4, GET_PLOG_BYPID = 5};

#define plog_cmd    m2_i1 
#define plog_num    m2_i2
#define plog_ctime  m2_l1
#define plog_ttime  m2_l2

// put impl in /usr/src/lib/libc/sys-minix/

#include <lib.h> // _syscall & message

int get_plog_byindex(int index, long * c_time, long * t_time){
    message m;
    m.plog_cmd = GET_PLOG_BYINDX;
    m.plog_num = index;
    _syscall(PM_PROC_NR, PLOG, &m);
    *c_time = m.plog_ctime;
    *t_time = m.plog_ttime;
    return 8;
}

int main(int argc, char * argv[]){
    printf("hello world");
    return 0;
}
