#include "main.h"
#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "cpu_monitor.h"

int main() {
    long num_cores = NUM_CPU_CORES;

    if (num_cores <= 0) {
        printf("Failed to determine the number of CPU cores.\n");
        return 1;
    }

    CPUStats* cpu_stats = (CPUStats*)malloc(sizeof(CPUStats) * (num_cores+1));
    if (cpu_stats == NULL) {
        fprintf(stderr, "Error allocating memory for cpu_stats.\n");
        return 1;
    }

    pthread_t reader_thread, analyzer_thread, printer_thread;

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
        free(cpu_stats);
        return 1;
    }

    pthread_join(reader_thread, NULL);
    pthread_join(analyzer_thread, NULL);
    pthread_join(printer_thread, NULL);

    free(cpu_stats);
    return 0;
}