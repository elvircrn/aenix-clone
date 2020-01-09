#ifndef OS_INCLUDE_CONSOLE_H
#define OS_INCLUDE_CONSOLE_H

#include "io.h"
#include "bitutil.h"

#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 25
#define CONSOLE_PIXELS CONSOLE_WIDTH * CONSOLE_HEIGHT

#define FB_GREEN     2
#define FB_DARK_GREY 8

#define FB_COMMAND_PORT 0x3d4
#define FB_DATA_PORT 0x3d5
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

extern int cursor_pos;
extern char *fb;

void fb_move_cursor(unsigned short pos);
void fb_print_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
int console_print_str(const char *buff);
void console_print_char_at_cursor(char c);
void console_print_char(unsigned int pos, char c);
void console_print_number(int number);
unsigned char is_cursor_in_last_position();
unsigned char is_cursor_at_last_position(unsigned int pos);
void clear_row(int row);
void new_line();
void move_rows_up();

#endif //OS_INCLUDE_CONSOLE_H
