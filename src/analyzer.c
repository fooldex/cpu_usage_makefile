#include "analyzer.h"
#include "logger.h"
#include "cpu_monitor.h"
#include "num_cpu_cores.h"
#include <assert.h>

static volatile int analyzer_alive = 0;

void* Analyzer(void* arg) {

    analyzer_alive = 1;

    CPUStats* cpu_stats = (CPUStats*)arg;
    CPUStats* prev_cpu_stats = (CPUStats*)malloc(sizeof(CPUStats) * (NUM_CPU_CORES+1));
    if (!prev_cpu_stats) {
        fprintf(stderr, "Error allocating memory for prev_cpu_stats.\n");
        exit(EXIT_FAILURE);
    }
    

    
   /* for (int core_id = 0; core_id <= NUM_CPU_CORES; core_id++) {
        prev_cpu_stats[core_id] = cpu_stats[core_id];
    }*/
    
    while (1) {
        
        
        pthread_mutex_lock(&cpu_stats_mutex);
        pthread_cond_wait(&cpu_stats_updated, &cpu_stats_mutex);
        
        


        
        for (int core_id = 1; core_id <= NUM_CPU_CORES; core_id++) {
      

            unsigned long long PrevIdle = prev_cpu_stats[core_id].idle - prev_cpu_stats[core_id].iowait;

            unsigned long long Idle = cpu_stats[core_id].idle - cpu_stats[core_id].iowait;

            unsigned long long PrevNonIdle = prev_cpu_stats[core_id].user + prev_cpu_stats[core_id].nice +
                                                prev_cpu_stats[core_id].system + prev_cpu_stats[core_id].irq +
                                                prev_cpu_stats[core_id].softirq + prev_cpu_stats[core_id].steal;

            unsigned long long NonIdle = cpu_stats[core_id].user + cpu_stats[core_id].nice +
                                                cpu_stats[core_id].system + cpu_stats[core_id].irq +
                                                cpu_stats[core_id].softirq + cpu_stats[core_id].steal;     

            unsigned long long PrevTotal = PrevIdle + PrevNonIdle;

            unsigned long long Total = Idle + NonIdle;

            unsigned long long totald = Total - PrevTotal;

            unsigned long long idled = Idle - PrevIdle;


            
            cpu_stats[core_id].CPU_Usage = ((double)(totald - idled) / totald) * 100.0;
            

            assert(cpu_stats[core_id].CPU_Usage >= 0 && cpu_stats[core_id].CPU_Usage <= 100);

            //printf("idle %llu \n", cpu_stats[core_id].idle);

            //printf("idle %llu \n", prev_cpu_stats[core_id].idle);


            prev_cpu_stats[core_id] = cpu_stats[core_id];
            
        }
        Logger_Log("CPU usage for cores is calculated for an iteration:");
        pthread_mutex_unlock(&cpu_stats_mutex);
        pthread_cond_signal(&calculation_finished);
        
    }

    free(prev_cpu_stats);
    return NULL;
}

int is_analyzer_alive(){
    return analyzer_alive;
}