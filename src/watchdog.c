#include "watchdog.h"
# define TIMER 2

void* Watchdog(void* arg){
    (void)arg;
    while(1){
        sleep (TIMER);
        if(!is_reader_alive() || !is_analyzer_alive() || !is_printer_alive()){
            fprintf(stderr, "Watchdog: One of threads is not responding!\n");
            exit(EXIT_FAILURE);
        }


    }
    return NULL;
}