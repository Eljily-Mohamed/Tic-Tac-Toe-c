#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include "include/board.h"


typedef void (*OnUartRx)(char c);


// Definitions for typical UART 'mode' settings
// CR1 bit 12
#define UART_CHAR_8       (0x00)
#define UART_CHAR_9       (0x01)

// CR2 bits 12-13
#define UART_STOP_1       (0x00<<4)
#define UART_STOP_2       (0x02<<4)

// CR1 bits 8-10
#define UART_PAR_NO       (0x0<<8)
#define UART_PAR_EVEN     (0x5<<8)
#define UART_PAR_ODD      (0x7<<8)

#define UART_8N1          (UART_CHAR_8 | UART_PAR_NO   | UART_STOP_1)
#define UART_8N2          (UART_CHAR_8 | UART_PAR_NO   | UART_STOP_2)
#define UART_8E1          (UART_CHAR_9 | UART_PAR_EVEN | UART_STOP_1)
#define UART_8E2          (UART_CHAR_9 | UART_PAR_EVEN | UART_STOP_2)
#define UART_8O1          (UART_CHAR_9 | UART_PAR_ODD  | UART_STOP_1)
#define UART_8O2          (UART_CHAR_9 | UART_PAR_ODD  | UART_STOP_2)

/*
 * uart_init : initialize with baud, line mode parameters,
 *             polling Tx and IRQ Rx
 */
int uart_init(USART_t *u, uint32_t baud, uint32_t mode, OnUartRx cb);

/*
 * uart_getc : get a char from the serial link (polling)
 */
char uart_getc(USART_t *u);

/*
 * uart_getchar : check if a char has been received from the serial link
 * (non-blocking)
 */
int uart_getchar(USART_t *u, char *pChar);

/*
 * uart_putc : send a char over the serial link (polling)
 */
void uart_putc(USART_t *u, char c);

/*
 * uart_puts : send a string over the serial link (polling)
 */
void uart_puts(USART_t *u, const char *s);

/*
 * uart_printf : print formatted text to serial link
 */
void uart_printf(USART_t *u, const char* fmt, ...);

#ifdef __cplusplus
}
#endif
#endif
