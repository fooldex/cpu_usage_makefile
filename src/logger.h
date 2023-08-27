#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>


void Logger_Log(const char* message);
void* Logger_thread(void* arg);

#endif
