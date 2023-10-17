#include <stdint.h>

typedef struct wav_header {
    // RIFF Header
    char riff_header[4]; // Contains "RIFF"
    uint32_t wav_size; // Size of the wav portion of the file, which follows the first 8 bytes. File size - 8
    char wave_header[4]; // Contains "WAVE"
    
    // Format Header
    char fmt_header[4]; // Contains "fmt " (includes trailing space)
    uint32_t fmt_chunk_size; // Should be 16 for PCM
    uint16_t audio_format; // Should be 1 for PCM. 3 for IEEE Float
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate; // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
    uint16_t sample_alignment; // num_channels * Bytes Per Sample
    uint16_t bit_depth; // Number of bits per sample
    
    // Data
    char data_header[4]; // Contains "data"
    uint32_t data_bytes; // Number of bytes in data. Number of samples * num_channels * sample byte size
    // uint8_t bytes[]; // Remainder of wave file is bytes
} wav_header;

wav_header create_header(uint32_t wav_size, uint32_t sample_rate, uint32_t bytes_per_sample, uint16_t bit_depth, uint32_t fmt_chunk_size, uint16_t audio_fmt, uint16_t num_channels, uint32_t data_bytes);

wav_header create_PCM_SC_header(uint32_t wav_size, uint32_t sample_rate, uint32_t bytes_per_sample, uint16_t bit_depth, uint32_t data_bytes);

wav_header create_PCM_SC_header_correct(uint32_t num_samples);

void endian_swap_32(uint32_t* dst, uint32_t src);

void endian_swap_16(uint16_t* dst, uint16_t src);

uint32_t endian_swap_32_ret(uint32_t src);

uint16_t endian_swap_16_ret(uint16_t src);

unsigned char* to_byte_array(wav_header header);

#define endian_swap(dst, src)                         \
_Generic((src),                                              \
    uint32_t : endian_swap_32,          \
    uint16_t : endian_swap_16)

