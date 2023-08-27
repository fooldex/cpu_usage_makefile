#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "main.h"

void* Watchdog(void* arg);
int is_reader_alive();
int is_analyzer_alive();
int is_printer_alive();

#endif