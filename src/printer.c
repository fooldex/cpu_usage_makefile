#include "printer.h"
#include "cpu_monitor.h"
#include "num_cpu_cores.h"


static volatile int printer_alive = 0;
void* Printer(void* arg) {

    printer_alive = 1;
    CPUStats* cpu_stats = (CPUStats*)arg;
    int first_iteration = 1;

  
   

    while (1) {
        sleep(INTERVAL); 
        pthread_mutex_lock(&cpu_stats_mutex);
    
        for (int core_id = 1; core_id <= NUM_CPU_CORES; core_id++) {

            if(!first_iteration){
            printf("CPU Usage for core #%d: %.2f%%\n", core_id, cpu_stats[core_id].CPU_Usage);
            
            }
                
        }
    
        pthread_mutex_unlock(&cpu_stats_mutex);

        printf("\n");

        first_iteration = 0;
       
    }


    return NULL;
}

int is_printer_alive(){
    return printer_alive;
}