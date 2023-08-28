#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <pthread.h>

#define MAX_LOG_SIZE 1000

typedef struct {
    pthread_t thread_id;
    char log_messages[MAX_LOG_SIZE][256];
    int num_messages;
    
} Logger;
extern Logger logger;


extern pthread_mutex_t log_mutex;

void Logger_Log(const char* message);
void* Logger_thread(void* arg);

#endif

