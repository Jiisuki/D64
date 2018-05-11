/*
 * d64sect.h
 *
 *  Created on: 26 Apr 2018
 *      Author: Jiisuki
 */

#pragma once

#include <stdint.h>

#define D64_FIELD_SIZE_DIR_TRACK ( 18)
#define D64_FIELD_SIZE_BAM_TRACK ( 18)
#define D64_FIELD_SIZE_SECTOR    (256)
#define D64_FIELD_SIZE_DIR_ENTRY ( 32)
#define D64_FIELD_SIZE_NAME      ( 16)
#define D64_FIELD_SIZE_BLOCK     (254)

uint8_t D64_getSectorLength(const uint8_t track);
uint32_t D64_getSectorOffset(const uint8_t track);

typedef struct{
    uint8_t DiskDOS;
    uint8_t DiskName[17]; // for now, last byte is always \0, could be deleted?
    uint8_t DiskID[2];
    uint8_t DOSType[2];
} s64Data;

typedef struct {
    uint8_t  nextDirTrack;
    uint8_t  nextDirSect;
    uint8_t  fType[4];
    uint8_t  fName[17];
    uint8_t  fTrack;
    uint8_t  fSect;
    uint8_t  fBlocksL;
    uint8_t  fBlocksH;
    uint16_t fBlocks;
} dirEntry;

typedef enum
{
    C64_Load_Result_LoadingReady,
    C64_Load_Result_DirectoryReady,
    C64_Load_Result_FileNotFound,
} C64_Load_Result_t;

void D64_initBAM(void); // needed for write operations etc. (?)
void D64_printDirectory(void); // for output of program list to C64
C64_Load_Result_t D64_uploadToC64(const uint8_t* const inName); // issue from C64 to load prog
void D64_readProgramBinary(const uint8_t fTrack, const uint8_t fSect); // read full program binary and transmit
