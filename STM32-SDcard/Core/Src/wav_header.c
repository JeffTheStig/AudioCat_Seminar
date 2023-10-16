#include "wav_header.h"
#include <string.h>

wav_header create_header(int wav_size, int sample_rate, int bytes_per_sample, short bit_depth, int fmt_chunk_size, short audio_fmt, short num_channels, int data_bytes) {
    wav_header head;
    strncpy(head.riff_header, "RIFF", 4);
    head.wav_size = wav_size;
    strncpy(head.wave_header, "WAVE", 4);

    strncpy(head.fmt_header, "fmt ", 4);
    head.fmt_chunk_size = fmt_chunk_size;
    head.audio_format = audio_fmt;
    head.num_channels = num_channels;
    head.sample_rate = sample_rate;
    head.byte_rate = sample_rate * num_channels * bytes_per_sample;
    head.sample_alignment = num_channels * bytes_per_sample;
    head.bit_depth = bit_depth;

    strncpy(head.data_header, "data", 4);
    head.data_bytes = data_bytes;

    return head;
}

wav_header create_PCM_SC_header(int wav_size, int sample_rate, int bytes_per_sample, short bit_depth, int data_bytes) {
    return create_header(wav_size, sample_rate, bytes_per_sample, bit_depth, 16, 1, 1, data_bytes);
}

wav_header create_PCM_SC_header_correct(int wav_size, int num_samples) {
    int sample_rate = 6000;
    int bytes_per_sample = 2;
    short bit_depth = 14;
    int data_bytes = 1 * num_samples * bytes_per_sample; // Number of bytes in data. Number of samples * num_channels * sample byte size

    return create_PCM_SC_header(wav_size, sample_rate, bytes_per_sample, bit_depth, data_bytes);
}
