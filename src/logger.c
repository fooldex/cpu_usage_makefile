#include "logger.h"
#include "cpu_monitor.h"
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

Logger logger;
pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER; 

void* Logger_thread(void* arg) {
    (void) arg;
    while (1) {
        pthread_mutex_lock(&log_mutex);
        if (logger.num_messages > 0) {
            FILE* log_file = fopen("log.txt", "a");
            if (log_file) {
                for (int i = 0; i < logger.num_messages; ++i) {
                    fprintf(log_file, "%s\n", logger.log_messages[i]);
                }
                fclose(log_file);
            }
            logger.num_messages = 0;
        }
        pthread_mutex_unlock(&log_mutex);

        sleep(1); 
    }

    return NULL;
}



void Logger_Log(const char* message) {
    pthread_mutex_lock(&log_mutex);
    if (logger.num_messages < MAX_LOG_SIZE) {
        strcpy(logger.log_messages[logger.num_messages], message);
        logger.num_messages++;
    }
    pthread_mutex_unlock(&log_mutex);
}
