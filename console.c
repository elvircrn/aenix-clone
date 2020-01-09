#include "include/console.h"
#include "include/rangeutil.h"
#include "include/serial.h"
#include "include/slib.h"

// 80 x 25, console dimensions

char *fb = (char *) 0x000B8000;
int cursor_pos = 0;

void fb_move_cursor(unsigned short pos) {
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, HI16(pos));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, LO16(pos));
}
void fb_print_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
  unsigned int ind = (i << 1u);
  fb[ind] = c;
  fb[ind + 1] = (LO8(fg) << 4u) | LO8(bg);
}

void new_line() {
  cursor_pos += CONSOLE_WIDTH;
  cursor_pos -= (cursor_pos % CONSOLE_WIDTH);
  if (cursor_pos >= CONSOLE_PIXELS) {
    cursor_pos -= CONSOLE_WIDTH;
    move_rows_up();
    clear_row(CONSOLE_HEIGHT - 1);
  }
  fb_move_cursor(cursor_pos);
}

/*
 * Increment cursor, while also handling screen scroll.
 */
void increment_cursor() {
  if (cursor_pos >= CONSOLE_PIXELS - 1) {
    while (cursor_pos >= CONSOLE_PIXELS) {
      cursor_pos -= CONSOLE_WIDTH - 1;
    }
  } else {
    cursor_pos++;
  }
  fb_move_cursor(cursor_pos);
}

unsigned char is_cursor_in_last_position() {
  return is_cursor_at_last_position(cursor_pos);
}

unsigned char is_cursor_at_last_position(unsigned int pos) {
  return pos == CONSOLE_PIXELS - 1;
}

void clear_row(int row) {
  for (int i = 0; i < CONSOLE_WIDTH; i++) {
    console_print_char(CONSOLE_WIDTH * row + i, ' ');
  }
}

void console_print_char_at_cursor(const char c) {
  console_print_char(cursor_pos, c);
}

void print_char_with_scroll(unsigned pos, const char c) {
  if (is_cursor_at_last_position(pos)) {
    for (int i = CONSOLE_WIDTH; i < CONSOLE_PIXELS; i++) {
      console_print_char(i - CONSOLE_WIDTH, fb[2 * i]);
    }
    move_rows_up();
    clear_row(CONSOLE_HEIGHT - 1);
  } else {
    console_print_char(pos, c);
  }
}

void console_print_char(unsigned int pos, char c) {
  fb_print_cell(pos, c, 0, 0x7u);
}

void console_print_char_at_cursor_with_scroll(const char c) {
  print_char_with_scroll(cursor_pos, c);
}

int console_print_str(const char *buff) {
  for (; buff && *buff; buff++) {
    if (*buff == '\n') {
      new_line();
    } else {
      console_print_char_at_cursor_with_scroll(*buff);
      increment_cursor();
    }
  }
  char buffs[20];
  __itoa(cursor_pos, buffs);
  serial_println(SERIAL_COM1_BASE, buffs);
  return 0;
}

void console_print_number(int number) {
  char buff[20];
  __memset(buff, 0, sizeof buff);
  __itoa(number, buff);
  console_print_str(buff);
}

void move_rows_up() {
  for (int i = 0; i < CONSOLE_WIDTH * (CONSOLE_HEIGHT - 1); i++) {
    fb[2 * i] = fb[2 * (i + CONSOLE_WIDTH)];
    fb[2 * i + 1] = fb[2 * (i + CONSOLE_WIDTH) + 1];
  }
}
