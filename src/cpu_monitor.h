#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include <pthread.h>

extern pthread_mutex_t cpu_stats_mutex;
extern pthread_cond_t cpu_stats_updated;
extern pthread_cond_t print_finished; 
extern pthread_cond_t calculation_finished; 

#endif
