#ifndef OS_INCLUDE_SEGMENTATION_H
#define OS_INCLUDE_SEGMENTATION_H

struct gdt {
  unsigned int address;
  unsigned short size;
} __attribute__((packed));


void load_lgdt(struct gdt *gdt);

#endif //OS_INCLUDE_SEGMENTATION_H
