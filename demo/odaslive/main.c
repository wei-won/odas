
#include <odas/odas.h>
#include <math.h>

#include "main_api_single_thread.h"

#define PI 3.14159265

odasStruct* odas_struct;

int get_data(char * buffer,
             unsigned int buffer_size,
             FILE * fp) {
    unsigned int nBytesTotal;
    int rtnValue;

    nBytesTotal = fread(buffer, sizeof(char), buffer_size, fp);
    if (nBytesTotal == buffer_size) {
        rtnValue = 0;
    }
    else {
        rtnValue = -1;
    }

    return rtnValue;
}

void file_parse(char * buffer,
                unsigned int n_ch,
                unsigned int hop_size,
                unsigned int n_bytes,
                double ** signal_array) {
    unsigned int iSample;
    unsigned int iChannel;
    char bytes[4];
    double sample;

    memset(bytes, 0x00, 4 * sizeof(char));
    for (iSample = 0; iSample < hop_size; iSample++) {
        for (iChannel = 0; iChannel < n_ch; iChannel++) {
            memcpy(&(bytes[4-n_bytes]),
                   &(buffer[(iSample * n_ch + iChannel) * n_bytes]),
                   sizeof(char) * n_bytes);
            sample = pcm_signedXXbits2normalized(bytes, n_bytes);
            signal_array[iChannel][iSample] = sample;
        }
    }
}

int source_proc(char * buffer,
                unsigned int n_ch,
                unsigned int hop_size,
                unsigned int format_bits,
                double ** signal_array,
                FILE * fp) {
    int rtnValue;
    unsigned int n_bytes;
    unsigned int buffer_size;

    n_bytes = format_bits/8;
    buffer_size = hop_size * n_ch * n_bytes;
    file_parse(buffer, n_ch, hop_size, n_bytes, signal_array);
    rtnValue = get_data(buffer, buffer_size, fp);
    return rtnValue;
}

int main(int argc, char * argv[]) {
    unsigned int n_ch = 6;
    unsigned int hop_size = 128;
    unsigned int format_bits = 16;
    char * file_path;
    char * buffer;
    double **audio_array;
    double degree;
    unsigned long long counter = 0;

    // NOTE: before testing this .wav file, please set the "fs" in the
    //       configuration file (respeaker_4_mic_array.cfg) as 44100.
    file_path = "/home/wei/wei_code/ssl/records/respeaker_2_16bit.wav";
    odas_struct = odas_init();
    buffer = (char *) malloc(sizeof(char) * hop_size * n_ch * 4);
    memset(buffer, 0x00, sizeof(char) * hop_size * n_ch * 4);
    audio_array = (double **) malloc(sizeof(double *) * n_ch);
    for (int iChannel = 0; iChannel < n_ch; iChannel++) {
        audio_array[iChannel] = (double *) malloc(sizeof(double) * hop_size);
        memset(audio_array[iChannel], 0x00, hop_size * sizeof(double));
    }
    FILE *fp = fopen(file_path, "rb");
    if (fp == NULL) {
        printf("Cannot open file %s\n",file_path);
        exit(EXIT_FAILURE);
    }

    while((source_proc(buffer, n_ch, hop_size, format_bits, audio_array, fp) == 0) &&
            (odas_proc(odas_struct, audio_array) == 0)) {
        int max_track = 0;
        if (counter == odas_struct->objs->mod_sst_object->out->timeStamp) {
            float max_activity = 0.0;
            for (int i_track = 0; i_track < n_ch; ++i_track) {
                if (max_activity < odas_struct->objs->mod_sst_object->out->tracks->activity[i_track]) {
                    max_activity = odas_struct->objs->mod_sst_object->out->tracks->activity[i_track];
                    max_track = i_track;
                }
            }
            degree = atan2((double) odas_struct->objs->mod_sst_object->out->tracks->array[max_track * 3 + 1],
                           (double) odas_struct->objs->mod_sst_object->out->tracks->array[max_track * 3 + 0]);
            printf("Time Stamp: %llu\nID: %llu, x: %f, y: %f, z: %f, activity: %f, degree: %f\n",
                   odas_struct->objs->mod_sst_object->out->timeStamp,
                   odas_struct->objs->mod_sst_object->out->tracks->ids[max_track],
                   odas_struct->objs->mod_sst_object->out->tracks->array[max_track * 3 + 0],
                   odas_struct->objs->mod_sst_object->out->tracks->array[max_track * 3 + 1],
                   odas_struct->objs->mod_sst_object->out->tracks->array[max_track * 3 + 2],
                   odas_struct->objs->mod_sst_object->out->tracks->activity[max_track],
                   degree * 180/PI);
            counter++;
        }
    }
    odas_close(odas_struct);

    return 0;
}
