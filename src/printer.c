#include "printer.h"
#include "cpu_monitor.h"

void* Printer(void* arg) {
    CPUStats* cpu_stats = (CPUStats*)arg;
  
   

    while (1) {
        sleep(INTERVAL); 
        pthread_mutex_lock(&cpu_stats_mutex);
    
        for (int core_id = 1; core_id <= NUM_CPU_CORES; core_id++) {
            printf("CPU Usage for core #%d: %.2f%%\n", core_id, cpu_stats[core_id].CPU_Usage);
                
        }
    
        pthread_mutex_unlock(&cpu_stats_mutex);
       
    }


    return NULL;
}