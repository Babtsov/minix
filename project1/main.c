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
#define plog_int    m2_i2
#define plog_ctime  m2_l1
#define plog_ttime  m2_l2

// put impl in /usr/src/lib/libc/sys-minix/

#include <lib.h> // _syscall & message

void stop_plog() {
    message m;
    m.plog_cmd = STOP_PLOG;
    _syscall(PM_PROC_NR, PLOG, &m);
} 

void start_plog() {
    message m;
    m.plog_cmd = START_PLOG;
    _syscall(PM_PROC_NR, PLOG, &m);
}

void reset_plog() {
    message m;
    m.plog_cmd = RESET_PLOG;
    _syscall(PM_PROC_NR, PLOG, &m);
}

int get_plog_size() {
    message m;
    m.plog_cmd = GET_PLOG_SIZE;
    _syscall(PM_PROC_NR, PLOG, &m);
    return m.plog_int;
}

int get_plog_byPID(int pid, long * c_time, long * t_time){
    message m;
    m.plog_cmd = GET_PLOG_BYPID;
    m.plog_int = pid;
    _syscall(PM_PROC_NR, PLOG, &m);
    *c_time = m.plog_ctime;
    *t_time = m.plog_ttime;
    return 8;
}

int get_plog_byindex(int index, long * c_time, long * t_time){
    message m;
    m.plog_cmd = GET_PLOG_BYINDX;
    m.plog_int = index;
    _syscall(PM_PROC_NR, PLOG, &m);
    *c_time = m.plog_ctime;
    *t_time = m.plog_ttime;
    return 8;
}

#include <stdio.h> // printf

void test_plog_pid(int pid) {
    printf("testing get_plog_byPID with pid = %d\n", pid);
    long c_time = -1, t_time = -1;
    get_plog_byPID(pid,&c_time,&t_time);
    printf("c_time = %ld\nt_time = %ld\n\n", c_time, t_time);
}

void test_plog_index(int index) {
    printf("testing get_plog_byindex with index = %d\n", index);
    long c_time = -1, t_time = -1;
    get_plog_byindex(index,&c_time,&t_time);
    printf("c_time = %ld\nt_time = %ld\n\n", c_time, t_time);
}

int main(int argc, char * argv[]){
  //  start_plog();
  //  test_plog_pid(23);
    test_plog_index(3);
    printf("Plog size is: %d\n", get_plog_size());
   // reset_plog();
   // stop_plog();
    return 0;
}
