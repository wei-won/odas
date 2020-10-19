
#include "main_api_single_thread.h"


// Flag
//char stopProcess;

// CHANGES: declare Result struct
//        struct Results{
//            int * trnValue;
//            objects * objs;
//        };


// Signal handler
//void sighandler(int signum) {
//    stopProcess = 1;
//}

odasStruct * odas_init(){
    odasStruct odas_struct;
    objects * objs;
    char * file_config;
    configs * cfgs; // Configurations
    profiler * prf; // Profiler

    odas_struct = (odasStruct *) malloc(sizeof(odasStruct));

    file_config = (char *) NULL;
    file_config = (char *) malloc(sizeof(char) * (strlen(optarg)+1));
    strcpy(file_config, optarg);

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

int odas_proc(odasStruct * odas_struct, double (*audio_data)[int size]){

    threads_single_process(odas_struct->objs, odas_struct->prf, audio_data);
    return 0;
}


