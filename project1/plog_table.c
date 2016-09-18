#include <stdio.h>
#include "plog.h"

int main() {
    printf("valid?\t|index\t|start\t\t|end\n");
    long c_time = -1, t_time = -1;
    for (int i = 0, n = get_plog_size(); i < n; i++) {
        int status = get_plog_byindex(i, &c_time, &t_time);
        char * padding = (c_time != 0)? "\t" : "\t\t";
        printf("%d\t|%d\t|%ld%s|%ld\n", status, i, c_time, padding, t_time);
    }    
    return 0;
}
