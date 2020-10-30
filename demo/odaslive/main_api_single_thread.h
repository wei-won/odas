
#ifndef ODAS_MAIN_API_SINGLE_THREAD_H
#define ODAS_MAIN_API_SINGLE_THREAD_H

#include "parameters.h"
#include "configs.h"
#include "objects.h"
#include "threads.h"
#include "profiler.h"

#include <time.h>
#include <odas/odas.h>
#include <signal.h>

typedef struct odasStruct {
    objects * objs;
    configs * cfgs;
    profiler * prf;
    char* file_config;
} odasStruct;

odasStruct * odas_init();

void odas_close(odasStruct * odas_struct);

int odas_proc(odasStruct * odas_struct, double **audio_data);

#endif //ODAS_MAIN_API_SINGLE_THREAD_H

