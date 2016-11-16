#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[]) {
    
    if (fork() > 0) exit(0); // terminate parent
    umask(0);
    if(setsid() < 0) exit(1);
    chdir("/");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    plog;
    FILE * fp = fopen ("/tmp/proc-states", "w+");
    for(;;) {
        sleep(1);
        fprintf(fp, "Judge me\n");
        fflush(fp);
    }
    return (0);
}
