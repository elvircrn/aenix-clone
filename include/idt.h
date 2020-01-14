#ifndef OS_INCLUDE_IDT_H
#define OS_INCLUDE_IDT_H

#include "ntypes.h"

struct idt_entry {
  unsigned int offset_low: 16;
  unsigned int segment_selector: 16;
  unsigned int reserved: 5;
  unsigned char zero: 8;
  unsigned char dpl: 2;
  unsigned char p: 1;
  unsigned int offset_high: 16;
} __attribute__((packed));

struct idt_entry idt_entries[256];

#endif //OS_INCLUDE_IDT_H
