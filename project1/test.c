#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

#define ECHO_SUCCESS "Test passed!\n"
#define ECHO_OOPS "Something might have went wrong\n"

/* prototypes for helper functions */
pid_t fork_sleeping_child(int time);
void execute_tests(void);
void table_dump(int start, int end);

/* plog test cases */
void test_get_plog_by_valid_existing_index(void) {
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
}

void test_get_plog_by_invalid_index(void) {
    long c_time = 345, t_time = 356;
    int status_for_neg = get_plog_byindex(-1, &c_time, &t_time);
    int status_for_too_large = get_plog_byindex(19230, &c_time, &t_time);

    // assert
    if (status_for_too_large == 3 && status_for_neg == 3 
          /*  && c_time == 345 && t_time == 356*/) {
        printf(ECHO_SUCCESS);
    } else {
        printf(ECHO_OOPS);
        printf("Status for negatvie index: %d\n"
               "Status for too big of an index: %d\n"
               "c_time=%ld (expected 345), t_time=%ld (expected 356)\n",
               status_for_neg, status_for_too_large, c_time, t_time);
    }
}

void test_get_plog_by_valid_pid(void) {
    // arrange
    long current_time = time(NULL);
    
    // act
    pid_t children[] = {fork_sleeping_child(1), fork_sleeping_child(1), fork_sleeping_child(1) };
    wait(NULL); 
    
    for (int i = 0, n_children = sizeof(children)/sizeof(children[0]); i < n_children; i++) {
        long c_time, t_time;
        int status = get_plog_byPID(children[i], &c_time, &t_time);
        
        // assert
        if (c_time == current_time && t_time == current_time + 1 /* && status == 0*/ ) {
            printf("(%d/%d) "ECHO_SUCCESS,i + 1, n_children);
        } else {
            printf(ECHO_OOPS);
            printf("Current time:  %ld\nc_time: %ld\nt_time: %ld\n", current_time, c_time, t_time);
            printf("status returned by the function: %d\n", status);
        }    
    }
}

int main(int argc, char ** argv) {
    execute_tests();
    return 0;
}

void execute_tests(void) {
    void (*tests[])(void) = {
        test_get_plog_by_valid_existing_index,
        test_get_plog_by_invalid_index,
        test_get_plog_by_valid_pid
    };
    int number_of_tests = sizeof(tests)/sizeof(tests[0]);
    printf("~~~~~~ Number of tests: %d ~~~~~~~~~~~~~~~~~~~~~~~\n", number_of_tests);
    for (int i = 0; i < number_of_tests; i++) {
        printf("\t\tTEST %d\n",i + 1);
        reset_plog();
        start_plog();
        (*tests[i])(); // run the test case
        stop_plog();
        table_dump(0,5);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }
}

void table_dump(int start, int end) {
    printf("%%%%%%%%%% PLOG TABLE DUMP %%%%%%%%%%%%\n");
    printf("valid?\t|index\t|creation time\t|termination time\n");
    long c_time = -1, t_time = -1;
    for (int i = start; i < end; i++) {
        int status = get_plog_byindex(i, &c_time, &t_time);
        char * padding = (c_time != 0)? "\t" : "\t\t";
        printf("%d\t|%d\t|%ld%s|%ld\n", status, i, c_time, padding, t_time);
    }
}

pid_t fork_sleeping_child(int time) {
    pid_t child_pid = fork();
    if (child_pid == 0) { 
        sleep(time);
        exit(0);
    }
    return child_pid;
}
