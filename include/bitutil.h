#ifndef INCLUDE_BITUTIL_H
#define INCLUDE_BITUTIL_H

#define LO8(x) (unsigned char) ((x) & 0x0fu)
#define HI8(x) ((x >> 4) & 0x0f)
#define LO16(x) ((x) & 0xffu)
#define HI16(x) ((unsigned short)((x) >> 8u) & 0xffu)

#endif
