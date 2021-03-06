#include "pthread_impl.h"

int pthread_getschedparam(pthread_t t, int* restrict policy, struct sched_param* restrict param) {
    int r;
    mxr_mutex_lock(&t->killlock);
    if (t->dead) {
        r = ESRCH;
    } else {
        r = -__syscall(SYS_sched_getparam, t->tid, param);
        if (!r) {
            *policy = __syscall(SYS_sched_getscheduler, t->tid);
        }
    }
    mxr_mutex_unlock(&t->killlock);
    return r;
}
