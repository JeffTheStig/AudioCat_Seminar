#include "wav_header.h"
#include <string.h>

wav_header create_header(uint32_t wav_size, uint32_t sample_rate, uint32_t bytes_per_sample, uint16_t bit_depth, uint32_t fmt_chunk_size, uint16_t audio_fmt, uint16_t num_channels, uint32_t data_bytes) {
    wav_header head;
//    strncpy(head.riff_header, "RIFF", 4);
//    endian_swap(&(head.wav_size), wav_size);
//    strncpy(head.wave_header, "WAVE", 4);
//
//    strncpy(head.fmt_header, "fmt ", 4);
//    endian_swap(&(head.fmt_chunk_size), fmt_chunk_size);
//    endian_swap(&(head.audio_format), audio_fmt);
//    endian_swap(&(head.num_channels), num_channels);
//    endian_swap(&(head.sample_rate), sample_rate);
//    endian_swap(&(head.byte_rate), (sample_rate * num_channels * bytes_per_sample));
//    endian_swap(&(head.sample_alignment), (num_channels * bytes_per_sample));
//    endian_swap(&(head.bit_depth), bit_depth);
//
//    strncpy(head.data_header, "data", 4);
////    endian_swap(&(head.data_bytes), data_bytes);
//    head.data_bytes = data_bytes;

//    strncpy(head.riff_header, "RIFF", 4);
//	head.wav_size =  endian_swap_32_ret(wav_size);
//	strncpy(head.wave_header, "WAVE", 4);
//
//	strncpy(head.fmt_header, "fmt ", 4);
//	head.fmt_chunk_size = endian_swap_32_ret(fmt_chunk_size);
//	head.audio_format =  endian_swap_16_ret(audio_fmt);
//	head.num_channels =  endian_swap_16_ret(num_channels);
//	head.sample_rate = endian_swap_32_ret(sample_rate);
//	head.byte_rate = endian_swap_32_ret((sample_rate * num_channels * bytes_per_sample));
//	head.sample_alignment = endian_swap_16_ret((num_channels * bytes_per_sample));
//	head.bit_depth =  endian_swap_16_ret(bit_depth);
//
//	strncpy(head.data_header, "data", 4);
////    endian_swap(&(head.data_bytes), data_bytes);
//	head.data_bytes = endian_swap_32_ret(data_bytes);

	strncpy(head.riff_header, "RIFF", 4);
    head.wav_size =  wav_size;
    strncpy(head.wave_header, "WAVE", 4);

    strncpy(head.fmt_header, "fmt ", 4);
    head.fmt_chunk_size = fmt_chunk_size;
    head.audio_format =  audio_fmt;
    head.num_channels =  num_channels;
    head.sample_rate = sample_rate;
    head.byte_rate = (sample_rate * num_channels * bytes_per_sample);
    head.sample_alignment = (num_channels * bytes_per_sample);
    head.bit_depth =  bit_depth;

	strncpy(head.data_header, "data", 4);
//    endian_swap(&(head.data_bytes), data_bytes);
	head.data_bytes = data_bytes;

    return head;
}

wav_header create_PCM_SC_header(uint32_t wav_size, uint32_t sample_rate, uint32_t bytes_per_sample, uint16_t bit_depth, uint32_t data_bytes) {
    return create_header(wav_size, sample_rate, bytes_per_sample, bit_depth, 16, 1, 1, data_bytes);
}

wav_header create_PCM_SC_header_correct(uint32_t num_samples) {
    uint32_t sample_rate = 27027;
    uint32_t bytes_per_sample = 2;
    uint16_t bit_depth = 14;
    uint32_t data_bytes = 1 * num_samples * bytes_per_sample; // Number of bytes in data. Number of samples * num_channels * sample byte size
    uint32_t wav_size = data_bytes + 36; // Amount of data bytes + 36 header bytes.

    return create_PCM_SC_header(wav_size, sample_rate, bytes_per_sample, bit_depth, data_bytes);
}

void endian_swap_32(uint32_t* dst, uint32_t src) {
	*dst = ((src<<24) & 0xff000000) |
			  ((src<<8) & 0x00ff0000) |
			  ((src>>8) & 0x0000ff00) |
			((src>>24) & 0x000000ff);
//	(*dst) = ((src&0x000000ff) << 24) |
//			((src&0x0000ff00) << 8) |
//			((src&0x00ff0000) >> 8) |
//			((src&0xff000000) >> 24);
}

void endian_swap_16(uint16_t* dst, uint16_t src) {
	(*dst) = ((src>>8)&0x00ff) |
		((src<<8)&0xff00);
//	(*dst) = ((src&0x00ff)<<8) |
//		((src&0xff00)>>8);
}

uint32_t endian_swap_32_ret(uint32_t src) {
	return ((src<<24) & 0xff000000) |
			  ((src<<8) & 0x00ff0000) |
			  ((src>>8) & 0x0000ff00) |
			((src>>24) & 0x000000ff);
//	(*dst) = ((src&0x000000ff) << 24) |
//			((src&0x0000ff00) << 8) |
//			((src&0x00ff0000) >> 8) |
//			((src&0xff000000) >> 24);
}

uint16_t endian_swap_16_ret(uint16_t src) {
	return ((src>>8)&0x00ff) |
		((src<<8)&0xff00);
//	(*dst) = ((src&0x00ff)<<8) |
//		((src&0xff00)>>8);
}

unsigned char* to_byte_array(wav_header header) {
	unsigned char* out[44];
	strncpy(out[0], header.riff_header, 4);
	memcpy( out[4], &header.wav_size, 4 );
	strncpy(out[8], header.wave_header, 4);
	strncpy(out[8], header.fmt_header, 4);
	memcpy( out[16], &header.fmt_chunk_size, 4 );
	memcpy( out[20], &header.audio_format, 2 );
	memcpy( out[22], &header.num_channels, 2 );
	memcpy( out[24], &header.sample_rate, 4 );
	memcpy( out[28], &header.byte_rate, 4 );
	memcpy( out[32], &header.sample_alignment, 2 );
	memcpy( out[34], &header.bit_depth, 2 );
	strncpy(out[36], header.data_header, 4);
	memcpy( out[40], &header.data_bytes, 4 );

	return out;
}
