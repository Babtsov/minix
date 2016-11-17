#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    set_plog_ptr();
    struct plog_t * plog = get_plog_ptr();
    plog->logger_index = 1;
    printf("try: plog ptr: %p", plog);
    for(;;) {
        char c = getchar();
        printf("kernel index: %d\n",plog->kernel_index);
    }
    return 0;
}
