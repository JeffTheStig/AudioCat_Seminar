#include "wav_header.h"
#include <string.h>

wav_header create_header(uint32_t wav_size, uint32_t sample_rate, uint32_t bytes_per_sample, uint16_t bit_depth, uint32_t fmt_chunk_size, uint16_t audio_fmt, uint16_t num_channels, uint32_t data_bytes) {
    wav_header head;
    strncpy(head.riff_header, "RIFF", 4);
    endian_swap(&(head.size), wav_size);
    strncpy(head.wave_header, "WAVE", 4);

    strncpy(head.fmt_header, "fmt ", 4);
    endian_swap(&(head.fmt_chunk_size), fmt_chunk_size);
    endian_swap(&(head.audio_format), audio_fmt);
    endian_swap(&(head.num_channels), num_channels);
    endian_swap(&(head.sample_rate), sample_rate);
    endian_swap(&(head.byte_rate), (sample_rate * num_channels * bytes_per_sample));
    endian_swap(&(head.sample_alignment), (num_channels * bytes_per_sample));
    endian_swap(&(head.bit_depth), bit_depth);

    strncpy(head.data_header, "data", 4);
    endian_swap(&(head.data_bytes), data_bytes);

    return head;
}

wav_header create_PCM_SC_header(uint32_t wav_size, uint32_t sample_rate, uint32_t bytes_per_sample, uint16_t bit_depth, uint32_t data_bytes) {
    return create_header(wav_size, sample_rate, bytes_per_sample, bit_depth, 16, 1, 1, data_bytes);
}

wav_header create_PCM_SC_header_correct(uint32_t num_samples) {
    uint32_t sample_rate = 16000;
    uint32_t bytes_per_sample = 4;
    uint16_t bit_depth = 32;
    uint32_t data_bytes = 1 * num_samples * bytes_per_sample; // Number of bytes in data. Number of samples * num_channels * sample byte size
    uint32_t wav_size = data_bytes + 36; // Amount of data bytes + 36 header bytes.

    return create_PCM_SC_header(wav_size, sample_rate, bytes_per_sample, bit_depth, data_bytes);
}

void endian_swap_32(uint32_t* dst, uint32_t src) {
	(*dst) = ((src>>24)&0x000000ff) |
    		((src>>8)&0x0000ff00) |
			((src<<8)&0x00ff0000) |
			((src<<24)&0xff000000);
}

void endian_swap_16(uint16_t* dst, uint16_t src) {
	(*dst) = ((src>>8)&0x00ff) |
		((src<<8)&0xff00);
}
