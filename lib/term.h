// Terminal functions

#ifndef _TERM_IO_H_
#define _TERM_IO_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include "include/board.h"

// ****************************************************************************
// Data types

// ANSI color & effect code array
#define CL_DEFAULT					0
#define CL_BLACK					30
#define CL_RED 						31
#define CL_GREEN					32
#define CL_YELLOW					33
#define CL_BLUE						34
#define CL_MAGENTA					35
#define CL_CYAN						36
#define CL_WHITE					37

#define CL_NORMAL					0
#define CL_BRIGHT					1
#define CL_UNDERLINE				4
#define CL_BLINK					5
#define CL_REVERSE					7

#define KC_UP						(1<<8)
#define KC_DOWN						(2<<8)
#define KC_LEFT						(3<<8)
#define KC_RIGHT					(4<<8)
#define KC_HOME						(5<<8)
#define KC_END						(6<<8)
#define KC_PAGEUP					(7<<8)
#define KC_PAGEDOWN					(8<<8)
#define KC_ENTER					(9<<8)
#define KC_TAB						(10<<8)
#define KC_BACKSPACE				(11<<8)
#define KC_SUPPR					(12<<8)
#define KC_INSERT					(13<<8)
#define KC_ESC						(14<<8)
#define KC_F1						(15<<8)
#define KC_F2						(16<<8)
#define KC_F3						(17<<8)
#define KC_F4						(18<<8)
#define KC_F5						(19<<8)
#define KC_F6						(20<<8)
#define KC_F7						(21<<8)
#define KC_F8						(22<<8)
#define KC_F9						(23<<8)
#define KC_F10						(24<<8)
#define KC_F11						(25<<8)
#define KC_F12						(26<<8)
#define KC_EOT						(27<<8)
#define KC_UNKNOWN					(28<<8)
/*
enum
{
	KC_UP = 256,
	KC_DOWN,
	KC_LEFT,
	KC_RIGHT,
	KC_HOME,
	KC_END,
	KC_PAGEUP,
	KC_PAGEDOWN,
	KC_ENTER,
	KC_TAB,
	KC_BACKSPACE,
	KC_SUPPR,
	KC_INSERT,
	KC_ESC,
	KC_F1,
	KC_F2,
	KC_F3,
	KC_F4,
	KC_F5,
	KC_F6,
	KC_F7,
	KC_F8,
	KC_F9,
	KC_F10,
	KC_F11,
	KC_F12,
	KC_EOT,
	KC_UNKNOWN
};
*/


// ****************************************************************************
// Exported functions

// Terminal initialization
void term_init(USART_t *u, unsigned int rows, unsigned int cols);

// Terminal output functions
void term_clrscr(void);
void term_clreol(void);
void term_color(unsigned int color, unsigned int effect);


void term_gotoxy(unsigned int x, unsigned int y);
void term_up(unsigned int delta);
void term_down(unsigned int delta);
void term_left(unsigned int delta);
void term_right(unsigned int delta);

unsigned int term_get_rows(void);
unsigned int term_get_cols(void);
unsigned int term_get_cx(void);
unsigned int term_get_cy(void);

int term_getc(void);
void term_putc(char ch );
void term_puts(const char* str);
void term_printf(const char* fmt, ...);

int term_readline(const char *prompt_str, char *buf, int maxlength);

#ifdef __cplusplus
}
#endif
#endif /* #ifndef __TERM_IO_H__ */
