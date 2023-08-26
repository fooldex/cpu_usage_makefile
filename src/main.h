#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define INTERVAL 1  




typedef struct {
    unsigned long long user, prevuser;
    unsigned long long nice, prevnice;
    unsigned long long system, prevsystem;
    unsigned long long idle, previdle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal;
    double CPU_Usage;
} CPUStats;



//void sigterm(int signum);

#endif