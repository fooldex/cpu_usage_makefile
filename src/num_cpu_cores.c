#include "num_cpu_cores.h"
#include <assert.h>
#include <unistd.h>

int NUM_CPU_CORES = 0;

int number_of_cores() {
    int num_cpu_cores = sysconf(_SC_NPROCESSORS_ONLN);
    assert(num_cpu_cores > 0  && "Failed to determine the number of CPU cores.\n");
    return num_cpu_cores;
}