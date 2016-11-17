#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    for(;;) {
        plog_print_transitions();
    }
    return 0;
}
