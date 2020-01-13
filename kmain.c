#include "include/serial.h"
#include "include/console.h"
#include "include/segmentation.h"
void demo() {
  for (int i = 0; i < 40; i++) {
    char a[4];
    a[0] = i / 10 + '0';
    a[1] = i % 10 + '0';
    a[2] = '\n';
    a[3] = 0;
    console_print_str(a);
  }
}

void demo1() {
  for (int i = 0; i < 2500; i++) {
    new_line();
    console_print_number(i);
    serial_print_numberln(SERIAL_COM1_BASE, cursor_pos);
  }
}

void demo_segmentation() {
  struct gdt _gdt;
  _gdt.size = 100;
  _gdt.address = 0;
  load_lgdt(&_gdt);
  console_print_number(_gdt.address);
  console_print_str(" ");
  console_print_number(_gdt.size);
}

int main() {
  serial_configure(SERIAL_COM1_BASE);
  demo_segmentation();
  return 0;
}
