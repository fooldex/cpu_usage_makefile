#include "reader.h"
#include <string.h>
#include "cpu_monitor.h"
#include <assert.h>
#include "num_cpu_cores.h"

//Reader thread


void* Reader(void* arg) {
    CPUStats* cpu_stats = (CPUStats*)arg;

    while (1) {
        FILE* file = fopen("/proc/stat", "r");

        assert(file != NULL && "Error opening /proc/stat file.\n");

        char buffer[256];
        int cpu_id = 0;

        while (fgets(buffer, sizeof(buffer), file) && cpu_id <= NUM_CPU_CORES) {
            if (strncmp(buffer, "cpu", 3) == 0) {   //if there is "cpu" in the line
                sscanf(buffer + 5, "%llu %llu %llu %llu %llu %llu %llu %llu",
                       &cpu_stats[cpu_id].user, &cpu_stats[cpu_id].nice,
                       &cpu_stats[cpu_id].system, &cpu_stats[cpu_id].idle,
                       &cpu_stats[cpu_id].iowait, &cpu_stats[cpu_id].irq,
                       &cpu_stats[cpu_id].softirq, &cpu_stats[cpu_id].steal);  //+5 to eliminate "cpu_..."
                cpu_id++;
            }
            
        }
        

        fclose(file);

        pthread_cond_signal(&cpu_stats_updated);

        sleep(INTERVAL); 
    }

    return NULL;
}