#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

#define ECHO_SUCCESS "Test passed!\n"
#define ECHO_OOPS "Something might have went wrong\n"

const int plog_buffer_size = 1024;

/* prototypes for helper functions */
pid_t fork_sleeping_child(int time);
void table_dump(int start, int end);

/* plog test cases */
void test_get_plog_size(void) {
    puts("Testing get_plog_size functionality...\n");
    
    //act
    int plog_size = get_plog_size();

    //assert
    if (plog_size == plog_buffer_size) {
        puts(ECHO_SUCCESS);
    } else {
        puts(ECHO_OOPS);
        printf("Returned plog size %d (expected %d)\n", plog_size, plog_buffer_size);
    }
}

void test_get_plog_by_valid_index(void) {
    puts("Checking get_plog_byindex with valid indices...\n");
    // arrange
    long current_time = time(NULL);
    
    // act
    int sleep_times[] = {1 ,2 , 0, 3, 5};
    const int N = sizeof(sleep_times)/sizeof(sleep_times[0]);

    pid_t children[N];
    for (int i = 0; i < N; i++) {
        children[i] = fork_sleeping_child(sleep_times[i]);
    }

    for (int i = 0; i < N; i++) {
        while ( -1 == waitpid(children[i], NULL, 0) ); // wait until all children exited. 
        long c_time, t_time;
        int status = get_plog_byindex(i, &c_time, &t_time);
        
        // assert
        if (c_time == current_time && t_time >= current_time + sleep_times[i]  && status == 0) {
            printf("Index tested: %d (slept for %d seconds) " ECHO_SUCCESS , i, sleep_times[i]);
        } else {
            printf(ECHO_OOPS);
            printf("Current time:  %ld\nc_time: %ld\nt_time: %ld\n", current_time, c_time, t_time);
            printf("status returned by the function: %d\n", status);
        }    
    }
}

void test_get_plog_by_invalid_index_or_pid(void) {
    puts("Testing for invalid indices and invalid pids");
    long c_time = 345, t_time = 356;
    fork_sleeping_child(1);
    wait(NULL);
    int status_for_neg = get_plog_byindex(-1, &c_time, &t_time);
    int status_for_too_large = get_plog_byindex(plog_buffer_size, &c_time, &t_time);
    int status_pid_not_found = get_plog_byPID(1, &c_time, &t_time);

    // assert
    if (status_for_too_large == 3 && status_for_neg == 3 && status_pid_not_found == 2
            && c_time == 345 && t_time == 356) {
        printf(ECHO_SUCCESS);
    } else {
        printf(ECHO_OOPS);
        printf("Status for negatvie index: %d\n"
               "Status for too big of an index: %d\n"
               "Status for invalid pid: %d\n"
               "c_time=%ld (expected 345), t_time=%ld (expected 356)\n",
               status_for_neg, status_for_too_large, status_pid_not_found, c_time, t_time);
    }
}

void test_get_plog_by_valid_pid(void) {
    puts("Checking get_plog_byPID...\n");
    // arrange
    long current_time = time(NULL);
    
    // act
    int sleep_times[] = {1 ,4 ,1, 2, 5};
    const int N = sizeof(sleep_times)/sizeof(sleep_times[0]);

    pid_t children[N];
    for (int i = 0; i < N; i++) {
        children[i] = fork_sleeping_child(sleep_times[i]);
    }

    for (int i = 0; i < N; i++) {
        while ( -1 == waitpid(children[i], NULL, 0) ); // wait until all children exited. 
        long c_time, t_time;
        int status = get_plog_byPID(children[i], &c_time, &t_time);
        
        // assert
        if (c_time == current_time && t_time >= current_time + sleep_times[i]  && status == 0) {
            printf("Case %d/%d (slept for %d seconds) " ECHO_SUCCESS ,i + 1, N, sleep_times[i]);
        } else {
            printf(ECHO_OOPS);
            printf("Current time:  %ld\nc_time: %ld\nt_time: %ld\n", current_time, c_time, t_time);
            printf("status returned by the function: %d\n", status);
        }    
    }
}
void test_plog_buffer_cycling(void) {
    puts("Testing the ability of the plog_buffer to cycle...\n");
    // arrange
    pid_t children[plog_buffer_size];
    long current_time = time(NULL);
    printf("Current time before forking 1024 children: %ld\n", current_time);
    for (int i = 0; i < plog_buffer_size; i++) {
        pid_t child = fork_sleeping_child(0);
        wait(NULL);
    }
    puts("done forking!\n");
    sleep(2);
    pid_t child_1025 = fork_sleeping_child(1);
    wait(NULL);
    long c_time, t_time;
    int status = get_plog_byPID(child_1025, &c_time, &t_time);
    if (status == 0) {
        puts(ECHO_SUCCESS);
    } else {
        puts(ECHO_OOPS);
        printf("The 1025th child couldn't be found in the plog table (status: %d)\n", status);
    }
}

int main(int argc, char ** argv) {
    void (*tests[])(void) = {
        test_get_plog_size,
        test_get_plog_by_valid_index,
        test_get_plog_by_invalid_index_or_pid,
        test_get_plog_by_valid_pid,
        test_plog_buffer_cycling
    };
    const int number_of_tests = sizeof(tests)/sizeof(tests[0]);
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
    return 0;
}

void table_dump(int start, int end) {
    printf("@@@@@@@@@@@  PLOG BUFFER DUMP  @@@@@@@@@@\n");
    printf("index\t|creation time\t|termination time\n");
    long c_time = -1, t_time = -1;
    for (int i = start; i < end; i++) {
        get_plog_byindex(i, &c_time, &t_time);
        char * padding = (c_time != 0)? "\t" : "\t\t";
        printf("%d\t|%ld%s|%ld\n", i , c_time, padding, t_time);
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
