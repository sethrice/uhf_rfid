#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "uhf_buffer.h"

#define FRAME_END 0x7E

typedef struct{
    char* hw_version;
    char* sw_version;
    char* manufacturer;
}M100ModuleInfo;

typedef enum{
    CHINA_900 = 1,  // Freq_CH-920.125M
    US,             // Freq_CH-902.25M
    EU,             // Freq_CH-865.1M
    CHINA_800,      // Freq_CH-840.125M
    KOREA = 6       // Freq_CH-917.1M
} WorkingArea;

typedef enum{
    CHINA_900 = 1,  // CH_Index(CN,900MHz) = (Freq_CH-920.125M)/0.25M
    US,             // CH_Index(US) = (Freq_CH-902.25M)/0.5M
    EU,             // CH_Index(EU) = (Freq_CH-865.1M)/0.2M
    CHINA_800,      // CH_Index(CN,800MHz) = (Freq_CH-840.125M)/0.25M
    KOREA = 6       // CH_Index(Korea) = (Freq_CH-917.1M)/0.2M
} WorkingChannel;

typedef struct{
    M100ModuleInfo* info;
    uint16_t baudrate;
    WorkingArea area;
    WorkingChannel channel;
    uint16_t transmitting_power;
    bool freq_hopping;
    Buffer* buf;
} M100Module;

M100ModuleInfo* m100_module_info_alloc();
void m100_module_info_free(M100ModuleInfo* module_info);

M100Module* m100_module_alloc();
void m100_module_free(M100Module* module);
uint16_t crc16_genibus(const uint8_t* data, size_t length);
uint8_t checksum(const uint8_t* data, size_t length);

// Function prototypes
char* m100_get_hardware_version(M100Module* module);
char* m100_get_software_version(M100Module* module);
char* m100_get_manufacturers(M100Module* module);
void m100_set_baudrate(M100Module* module, uint16_t baudrate);
bool m100_set_working_area(M100Module* module, WorkingArea area);
bool m100_set_working_channel(M100Module* module, WorkingChannel channel);
bool m100_set_transmitting_power(M100Module* module, uint16_t power);
bool m100_set_freq_hopping(M100Module* module, bool hopping);