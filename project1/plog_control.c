#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 2)
        return 1;

    int enabled = atoi(argv[1]);
    if (enabled)
        start_plog();
    else
        stop_plog();
    return 0;
}
