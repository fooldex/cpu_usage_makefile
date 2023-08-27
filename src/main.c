#include "main.h"
#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "cpu_monitor.h"
#include "num_cpu_cores.h"
#include "watchdog.h"
#include "logger.h"

int main() {
    
    
    NUM_CPU_CORES = number_of_cores();

    CPUStats* cpu_stats = (CPUStats*)malloc(sizeof(CPUStats) * (NUM_CPU_CORES+1));
    if (cpu_stats == NULL) {
        fprintf(stderr, "Error allocating memory for cpu_stats.\n");
        return 1;
    }

    pthread_t reader_thread, analyzer_thread, printer_thread, watchdog_thread, logger_thread;

    if (pthread_create(&reader_thread, NULL, Reader, cpu_stats) != 0) {
        fprintf(stderr, "Error creating reader thread.\n");
        return 1;
    }

    if (pthread_create(&analyzer_thread, NULL, Analyzer, cpu_stats) != 0) {
        fprintf(stderr, "Error creating analyzer thread.\n");
        return 1;
    }

    if (pthread_create(&printer_thread, NULL, Printer, cpu_stats) != 0) {
        fprintf(stderr, "Error creating printer thread.\n");
        
        return 1;
    }
        if (pthread_create(&watchdog_thread, NULL, Watchdog, NULL) != 0) {
        fprintf(stderr, "Error creating watchdog thread.\n");
       
        return 1;
    }

        if (pthread_create(&logger_thread, NULL, Logger_thread, NULL) != 0) {
        fprintf(stderr, "Error creating logger thread.\n");
       
        return 1;
    }


    pthread_join(reader_thread, NULL);
    pthread_join(analyzer_thread, NULL);
    pthread_join(printer_thread, NULL);
    pthread_join(watchdog_thread, NULL);
    pthread_join(logger_thread, NULL);

    free(cpu_stats);
    return 0;
}