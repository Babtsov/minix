#include <stdio.h> // printf
#include <stdlib.h>
#include <unistd.h>

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
    reset_plog();
  // stop_plog();
    return 0;
}
