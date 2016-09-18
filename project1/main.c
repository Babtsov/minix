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

/************************************************************************************************/
#include <stdio.h> // printf
#include <stdlib.h>
#include "plog.h"

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
  // printf("Plog size is: %d\n", get_plog_size());
	test_plog_index(123);
  // reset_plog();
  // stop_plog();
    return 0;
}
