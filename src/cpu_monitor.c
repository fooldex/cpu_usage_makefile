#include "cpu_monitor.h"
#include <pthread.h>

pthread_mutex_t cpu_stats_mutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cpu_stats_updated = PTHREAD_COND_INITIALIZER; 
