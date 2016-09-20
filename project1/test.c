#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

#define ECHO_SUCCESS "Test passed!\n"
#define ECHO_OOPS "Something might have went wrong\n"


pid_t fork_sleeping_child(int time) {
    pid_t child_pid = fork();
    if (child_pid == 0) { 
        sleep(time);
        exit(0);
    }
    return child_pid;
}

void test_get_plog_by_valid_existing_index() {
    // arrange
    reset_plog();
    start_plog();
    long current_time = time(NULL);
    
    // act
    fork_sleeping_child(3);
    wait(NULL);
    long c_time, t_time;
    int status = get_plog_byindex(0, &c_time, &t_time);
    
    // assert
    if (c_time == current_time && t_time == current_time + 3 && status == 0) {
        printf(ECHO_SUCCESS);
    } else {
        printf(ECHO_OOPS);
        printf("Current time:  %ld\nc_time: %ld\nt_time: %ld\n", current_time, c_time, t_time);
        printf("status returned by the function: %d\n", status);
    }    
    stop_plog();
}

void test_get_plog_by_invalid_index() {
    long c_time = 345, t_time = 356;
    int status_for_neg = get_plog_byindex(-1, &c_time, &t_time);
    int status_for_too_large = get_plog_byindex(19230, &c_time, &t_time);

    // assert
    if (status_for_too_large == -3 && status_for_neg == -3 
            && c_time == 345 && t_time == 356) {
        printf(ECHO_SUCCESS);
    } else {
        printf(ECHO_OOPS);
        printf("Status for negatvie index: %d\n"
               "Status for too big of an index: %d\n"
               "c_time=%ld (expected 345), t_time=%ld (expected 356)\n",
               status_for_neg, status_for_too_large, c_time, t_time);
    }
}

int main(int argc, char ** argv) {
    test_get_plog_by_valid_existing_index();
    test_get_plog_by_invalid_index();
    return 0;
}
