#include "include/serial.h"
#include "include/io.h"
#include "include/slib.h"

void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
  outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT(com), HI16(divisor));
  outb(SERIAL_DATA_PORT(com), LO16(divisor));
}

void serial_configure_modem(unsigned short com) {
  outb(SERIAL_MODEM_COMMAND_PORT(com), 0x3u);
}

void serial_configure_line(unsigned short com) {
  outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_fifo_buffer(unsigned short com) {
  outb(SERIAL_FIFO_COMMAND_PORT(com), 0xc7);
}

unsigned char serial_is_transmit_fifo_empty(unsigned int com) {
  return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20u;
}

void serial_configure(unsigned int com) {
  serial_configure_baud_rate(com, 1);
  serial_configure_modem(com);
  serial_configure_line(com);
  serial_configure_fifo_buffer(com);
}

void wait_empty_buffer(unsigned int com) {
  while (!serial_is_transmit_fifo_empty(com)) {
  }
}

void serial_println(unsigned int com, char *content) {
  serial_print(com, content);
  serial_print(com, "\n");
}

void serial_print(unsigned int com, char *content) {
  unsigned int res = __strlen(content);
  for (unsigned int i = 0; i < res; i++) {
    outb(com, content[i]);
    wait_empty_buffer(com);
  }
}

void serial_print_number(unsigned int com, int number) {
  char buff[20];
  __memset(buff, 0, sizeof buff);
  __itoa(number, buff);
  serial_print(com, buff);
}

void serial_print_numberln(unsigned int com, int number) {
  char buff[20];
  __memset(buff, 0, sizeof buff);
  __itoa(number, buff);
  serial_println(com, buff);
}

