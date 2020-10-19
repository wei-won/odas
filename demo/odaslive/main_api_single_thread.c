
#include "main_api_single_thread.h"


odasStruct * odas_init(){
    odasStruct * odas_struct;
    objects * objs;
    char * file_config;
    configs * cfgs; // Configurations
    profiler * prf; // Profiler

    odas_struct = (odasStruct *) malloc(sizeof(odasStruct));
    file_config = "../../config/odaslive/respeaker_4_mic_array.cfg";

    if (file_config == NULL) {
        printf("Missing configuration file.\n");
        exit(EXIT_FAILURE);
    }

    prf = profiler_construct();
    cfgs = configs_construct(file_config);
    objs = objects_construct(cfgs);
    threads_single_open(objs);

    odas_struct->objs = objs;
    odas_struct->prf = prf;
    odas_struct->cfgs = cfgs;
    odas_struct->file_config = file_config;

    return odas_struct;
}

int odas_close(odasStruct * odas_struct){
    threads_single_close(odas_struct->objs);
    // Free memory
    objects_destroy(odas_struct->objs);
    configs_destroy(odas_struct->cfgs);
    free((void *) odas_struct->file_config);
    profiler_destroy(odas_struct->prf);

    return 0;
}

int odas_proc(odasStruct * odas_struct, double *audio_data){
    threads_single_process(odas_struct->objs, odas_struct->prf, audio_data);

    return 0;
}


