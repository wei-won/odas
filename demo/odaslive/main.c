
#include <odas/odas.h>

#include "main_api_single_thread.h"

odasStruct* odas_struct;

int main(int argc, char * argv[]) {

    odas_struct = odas_init();
    int ch = 4;
    int hop_size = 1000;
    int a = RAND_MAX;
    double vec[ch][hop_size];
    double *audio_data;
    audio_data = vec;
    for (int i = 0; i < ch; i++) {
        for (int j = 0; j < hop_size; j++) {
            vec[i][j] = 1;
        }
    }
    if (!odas_proc(odas_struct, audio_data) == 0) {
        printf("Error Processing Audio Data!\n");
    }
    else {
        printf("x: %f, y: %f, z: %f\n",
               odas_struct->objs->mod_sst_object->out->tracks->array[0 * 3 + 0],
               odas_struct->objs->mod_sst_object->out->tracks->array[0 * 3 + 1],
               odas_struct->objs->mod_sst_object->out->tracks->array[0 * 3 + 2]);
    }
    odas_close(odas_struct);

    return 0;
}
