#ifndef OS__SERIAL_H
#define OS__SERIAL_H

#include "bitutil.h"
#include "io.h"

#define SERIAL_COM1_BASE  0x3f8
#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

#define SERIAL_LINE_ENABLE_DLAB 0x80

enum LogLevel { INFO, DEBUG, WARN, ERROR };

/*
 * TODO: Implement
 */
void serial_printf(enum LogLevel log_level, const char *fmt, ...);

void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

/*
 * Configures the modem (Ready-To-Transmit and Data-Terminal-Ready pins). When
 * configuring the serial port, we want RTS and DTS to be 1, which means that
 * we are ready to send data.
 * Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
 * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
 */
void serial_configure_modem(unsigned short com);

/*
 * Configures the line of the given serial port. The port is set to have a
 * data length of 8 bits, no parity bits, one stop bit and break control
 * disabled.
 * Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
 * Content: | d | b | prty  | s | dl  |
 * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
 * @param com
 */
void serial_configure_line(unsigned short com);

/*
 * Configures the serial port buffer
 * - Enables FIFO
 * - Clear both receiver and transmission FIFO queues
 * - Use 14 bytes as size of queue
 *
 * Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
 * Content: | lvl | bs | r | dma | clt | clr | e |
 */
void serial_configure_fifo_buffer(unsigned short com);

/*
 *  Checks whether the transmit FIFO queue is empty or not given COM
 *  port.
 * @param com The COM port
 */
unsigned char serial_is_transmit_fifo_empty(unsigned int com);

/*
 * prints data to the serial port.
 */
void serial_print(unsigned int com, char *content);

/*
 * prints data to the serial port while along with a newline character.
 */
void serial_println(unsigned int com, char *content);

/*
 * Configures the serial port specified by @com.
 */
void serial_configure(unsigned int com);

/*
 * Prints a number through the serial port.
 */
void serial_print_number(unsigned int com, int number);

/*
 * Prints a number through the serial port, adding a newline.
 */
void serial_print_numberln(unsigned int com, int number);
#endif //OS__SERIAL_H
