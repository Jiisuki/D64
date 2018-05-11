/*
 * d64reader.c
 *
 *  Created on: 26 Apr 2018
 *      Author: Jiisuki
 */

#include "d64Iface.h"

#include "iecIface.h"
#include "flashIface.h"

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

s64Data DiskInfo;
dirEntry dEntry;

uint32_t diskHeadPosition;

static const char* D64_getFiletype(const uint8_t byte); // convert filetype to easy interpretable string

void D64_initBAM(void)
{
    const uint32_t offset = D64_getSectorOffset(D64_FIELD_SIZE_DIR_TRACK-1);

    DiskInfo.DiskDOS = Flash_readByte(offset+2);
    Flash_readBlock(offset+144, D64_FIELD_SIZE_NAME, DiskInfo.DiskName);
    Flash_readBlock(offset+162,2,DiskInfo.DiskID);
    Flash_readBlock(offset+164,2,DiskInfo.DOSType);
}

void D64_printDirectory(void)
{
    uint32_t offset = D64_getSectorOffset(D64_FIELD_SIZE_DIR_TRACK-1);
    offset += D64_FIELD_SIZE_SECTOR; // directory starts after BAM sector

    char sendString[33] = {'\0'};

    while (1)
    {
        // each sector, excluding BAM
        Flash_seek(offset, Flash_Mode_Read);
        for (uint8_t k = 0; k < 8; k++ )
        {
            // move to sector block

            if (0 == k)
            {
                dEntry.nextDirTrack = Flash_readByte(offset);
                dEntry.nextDirSect = Flash_readByte(offset+1);
            }

            memcpy(dEntry.fType, D64_getFiletype(Flash_readByte(offset+2)), 3*sizeof(uint8_t));

            dEntry.fTrack = Flash_readByte(offset+3);
            dEntry.fSect = Flash_readByte(offset+4);

            Flash_readBlock(offset+5,D64_FIELD_SIZE_NAME,dEntry.fName);

            dEntry.fBlocksL = Flash_readByte(offset+13);
            dEntry.fBlocksH = Flash_readByte(offset+14);
            dEntry.fBlocks = dEntry.fBlocksL + dEntry.fBlocksH*256;

            // PRETTY PRINT
            sprintf(sendString,"%5d  %20s  %3s",dEntry.fBlocks,dEntry.fName,dEntry.fType);
            if (dEntry.fType[0] != '*')
            {
                // SEND TEXT STRING HERE
                //sendIECBlock(sendString,32);
            }
            offset += D64_FIELD_SIZE_DIR_ENTRY;
        }
        if (0 == dEntry.nextDirTrack)
        {
            return;
        }
        else
        {
            offset = D64_getSectorOffset(dEntry.nextDirTrack - 1) + (D64_FIELD_SIZE_SECTOR * dEntry.nextDirSect);
        }
    }
    //sendIECString("No disk loaded!");
}

C64_Load_Result_t D64_uploadToC64(const uint8_t* const inName)
{
    /* this function basically searches the disk for the filename */
    /* a way to optimize this is to actually store start t/s for each filename */
    /* in a separate struct on startup... this function only returns a flag to */
    /* tell the looper if we are good to go or not */

    if ('$' == inName[16])
    {
        return (C64_Load_Result_DirectoryReady);
    }

    // we need to pad the input name with spaces
    char NAME[17] = {'\0'};
    sprintf(NAME,"%-16s",inName);

    for (uint8_t i = 0; i < D64_FIELD_SIZE_NAME; i++)
    {
        if (32 == NAME[i])
        {
            NAME[i] = 0xa0; // c64 padding
        }
    }

    uint32_t offset = D64_getSectorOffset(D64_FIELD_SIZE_DIR_TRACK-1);
    offset += D64_FIELD_SIZE_SECTOR; // directory starts after BAM sector

    while (1)
    {
        for (uint8_t k = 0; k < 8; k++)
        {
            // move to sector block
            Flash_seek(offset, Flash_Mode_Read);

            if (0 == k)
            {
                dEntry.nextDirTrack = Flash_readByte(offset);
                dEntry.nextDirSect = Flash_readByte(offset+1);
            }

            memcpy(dEntry.fType, D64_getFiletype(Flash_readByte(offset+2)), 3*sizeof(uint8_t));
            dEntry.fTrack = Flash_readByte(offset+3);
            dEntry.fSect = Flash_readByte(offset+4);
            Flash_readBlock(offset+5,D64_FIELD_SIZE_NAME,dEntry.fName);

            if (0 == strncmp(NAME,(char*) dEntry.fName, strlen(NAME)))
            {
                // should really use strnIcmp (not found)
                // name match like the line above
                //flashSkipBytes(8);

                dEntry.fBlocksL = Flash_readByte(offset+13);
                dEntry.fBlocksH = Flash_readByte(offset+14);
                dEntry.fBlocks = dEntry.fBlocksL + dEntry.fBlocksH*256;

                /* file found */
                offset = D64_getSectorOffset(dEntry.fTrack - 1) + (D64_FIELD_SIZE_SECTOR * dEntry.fSect);
                diskHeadPosition = offset;

                Flash_seek(offset, Flash_Mode_Read);
                return (C64_Load_Result_LoadingReady);
            }

            offset += D64_FIELD_SIZE_DIR_ENTRY;
        }

        if (0 == dEntry.nextDirTrack)
        {
            break;
        }
        else
        {
            offset = D64_getSectorOffset(dEntry.nextDirTrack - 1) + (D64_FIELD_SIZE_SECTOR * dEntry.nextDirSect);
        }
    }

    return (C64_Load_Result_FileNotFound);
}

void D64_readProgramBinary(const uint8_t fTrack, const uint8_t fSect)
{
    uint32_t offset = D64_getSectorOffset(fTrack-1) + (D64_FIELD_SIZE_SECTOR * fSect);

    uint8_t nextDirTrack = 0;
    uint8_t nextDirSect = 0;

    while (1)
    {
        // move to sector block
        Flash_seek(offset, Flash_Mode_Read);
        nextDirTrack = Flash_readByte(offset);
        nextDirSect = Flash_readByte(offset+1);

        /* is it best to buffer the array, or bit bang after each read? */
        /* we need to calculate the speed of read from flash */

        //eeReadBlock(BLOCK_SIZE,DATABLOCK);

        /* check 'end' conditions, should be implemented in sendIECBlock or here? */

        //sendIECBlock(DATABLOCK,BLOCK_SIZE);

        if (0 == nextDirTrack)
        {
            return;
        }

        offset = D64_getSectorOffset(nextDirTrack - 1) + (D64_FIELD_SIZE_SECTOR * nextDirSect);
    }
}

static const char* D64_getFiletype(const uint8_t byte)
{
    /* this decodes bits to see what type there is */
    /* returning *** means that the space is deleted */
    switch (byte)
    {
        case 0:   return "***";
        case 1:   return "SEQ";
        case 2:   return "PRG";
        case 3:   return "USR";
        case 4:   return "REL";
        case 128: return "DEL";
        case 129: return "SEQ";
        case 130: return "PRG";
        case 131: return "USR";
        case 132: return "REL";
        default: return "---";
    }
}
