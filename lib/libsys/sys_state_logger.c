#include <syslib.h>

int sys_state_logger(int processId, int processIndex) {
    message m;
    return _kernel_call(SYS_STATE_LOGGER, &m);
}
