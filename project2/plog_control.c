#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 3)
        return 1;
    int enabled = atoi(argv[1]);
    int pid = atoi(argv[2]);
    
    if (enabled)
        plog_state_start(pid)
    else
        plog_state_stop(pid);
    return 0;
}
