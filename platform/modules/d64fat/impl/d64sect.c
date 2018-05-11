/*
 * d64sect.c
 *
 *  Created on: 26 Apr 2018
 *      Author: Jiisuki
 */

#include "d64Iface.h"
#include <stdint.h>

#define D64_NUM_TRACKS (40)

/* number of sectors for each track */
static const uint8_t d64sectors[D64_NUM_TRACKS] = {
    21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 19, 19, 19,
    19, 19, 19, 19, 18, 18, 18, 18, 18, 18, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17
};

/* byte offset for first sector in each track */
static const uint32_t d64offsets[D64_NUM_TRACKS] = {
         0,   5376,  10752,  16128,  21504,  26880,  32256,  37632,  43008,  48384,
     53760,  59136,  64512,  69888,  75264,  80640,  86016,  91392,  96256, 101120,
    105984, 110848, 115712, 120576, 125440, 130048, 134656, 139264, 143872, 148480,
    153088, 157440, 161792, 166144, 170496, 174848, 179200, 183552, 187904, 192256
};

uint8_t D64_getSectorLength(const uint8_t track)
{
    if (track < D64_NUM_TRACKS)
    {
        return (d64sectors[track]);
    }

    return (0);
}

uint32_t D64_getSectorOffset(const uint8_t track)
{
    if (track < D64_NUM_TRACKS)
    {
        return (d64offsets[track]);
    }

    return (0);
}
