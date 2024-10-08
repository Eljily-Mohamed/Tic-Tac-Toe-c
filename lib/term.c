// Terminal function

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "lib/term.h"
#include "lib/uart.h"


// Local variables
static USART_t *uart;
static unsigned term_num_rows, term_num_cols;
static unsigned term_cx, term_cy;
static unsigned fg_color;

/****************************************************************************
 *  util functions
 ***************************************************************************/
#define RING_BUF_SIZE	64

typedef volatile struct RingBuffer {
	char buf[RING_BUF_SIZE];
	int  i_push;		/* pointeur (index) d'écriture */
	int  i_pop;		/* pointeur (index) de lecture */
} RingBuffer;

static RingBuffer rx_buf = {
	.i_push=0,
	.i_pop=0
};

static void uart_cb(char c)
{
    // Si le buffer n'est pas plein
    if ((rx_buf.i_push + 1) % RING_BUF_SIZE != rx_buf.i_pop) {
        // Ecrire le caractère dans le buffer
        rx_buf.buf[rx_buf.i_push] = c;
        // Incrémenter l'index d'écriture
        rx_buf.i_push = (rx_buf.i_push + 1) % RING_BUF_SIZE;
    }
}

// Terminal output function
static void term_out(char c)
{
	uart_putc(uart, c);
}

// Terminal input function
static char term_in(void)
{
	unsigned char c;

    // Attendre que le buffer ne soit plus vide
    while (rx_buf.i_push == rx_buf.i_pop) {}

    // Lire un caractère
    c = rx_buf.buf[rx_buf.i_pop];
    // Incrémenter l'index de lecture
    rx_buf.i_pop = (rx_buf.i_pop + 1) % RING_BUF_SIZE;

	return c;
}

// num2str
//   convert a number 'number' in base 'base' to the string s (the string
//   variable must be large enough)
//   size : (unsigned int) minimal number of digit width for string number
//   sp   : (boolean) complete the width with ' ' or '0'
static void num2str(char *s, unsigned int number, unsigned int base, int size, int sp)
{
	static char  hexChars[] = "0123456789ABCDEF";

	char *p=s;
	int cnt;
	int i;
	char tmp;

	// get digits
	do {
		*s++=hexChars[number % base];
	} while (number /= base);
	*s='\0';

	// reverse string
	cnt=s-p;
	for (i=0;i<cnt/2;i++) {
		tmp=p[i]; p[i] = p[cnt-i-1]; p[cnt-i-1]=tmp;
	}

	// add extra space
	if (cnt<size) {
		for (i=cnt;i>=0;i--) p[i+size-cnt]=p[i];
		if (sp) tmp=' '; else tmp='0';
		for (i=0;i<size-cnt;i++) p[i]=tmp;
	}
}

static unsigned int str2num(char *s, unsigned base)
{
	unsigned int u=0, d;
	char ch=*s++;
	while (ch) {
		if ((ch>='0') && (ch<='9')) d=ch-'0';
		else if ((base==16) && (ch>='A') && (ch<='F')) d=ch-'A'+10;
		else if ((base==16) && (ch>='a') && (ch<='f')) d=ch-'a'+10;
		else break;
		u=d+base*u;
		ch=*s++;
	}
	return u;
}

// Helper function: send the requested string to the terminal
static void term_ansi( const char* fmt, ... )
{
	va_list ap;
	char s[20], *p;
	
	term_out('\x1B');
	term_out('[');
	va_start(ap,fmt);
	while (*fmt!='\0') {
		if (*fmt=='%') {
			switch (*++fmt) {
			case 'u':
				num2str(s, va_arg(ap, unsigned int), 10, 0, 0);
				p=s;
				while (*p) term_out(*p++);
				break;
			}
		} else term_out(*fmt);
		fmt++;
	}
	va_end(ap);
}

/****************************************************************************
 *  terminal functions (public API)
 ***************************************************************************/
// init function
void term_init(USART_t *u, unsigned rows, unsigned cols)
{
	uart=u;
	uart_init(uart, 115200, UART_8N1, uart_cb);
	term_num_rows = rows;
	term_num_cols = cols;
	term_cx = term_cy = 1;
}                

//-----------------------------
//  Screen handling functions 
//-----------------------------

// Clear the screen
void term_clrscr(void)
{
	term_ansi( "2J" );
	term_ansi( "H" );
	term_cx = term_cy = 1;
}

// Clear to end of line
void term_clreol(void)
{
	term_ansi( "K" );
}

// Set the current color on the 
void term_color(unsigned color, unsigned effect)
{
	if (fg_color != color) {
		term_ansi("%u;%um", effect, color);
		fg_color = color;
	}
}

//-----------------------------
//  Cursor handling functions 
//-----------------------------

// Move cursor to (x, y)
void term_gotoxy( unsigned x, unsigned y )
{
	term_ansi( "%u;%uH", y, x );
	term_cx = x;
	term_cy = y;
}

// Move cursor up "delta" lines
void term_up( unsigned delta )
{
	term_ansi( "%uA", delta );  
	term_cy -= delta;
}

// Move cursor down "delta" lines
void term_down( unsigned delta )
{
	term_ansi( "%uB", delta );  
	term_cy += delta;
}

// Move cursor right "delta" chars
void term_right( unsigned delta )
{
	term_ansi( "%uC", delta );  
	term_cx += delta;
}

// Move cursor left "delta" chars
void term_left( unsigned delta )
{
	term_ansi( "%uD", delta );  
	term_cx -= delta;
}

// Return the number of terminal rows
unsigned term_get_rows(void)
{
	return term_num_rows;
}

// Return the number of terminal columns
unsigned term_get_cols(void)
{
	return term_num_cols;
}

// Return the cursor "x" position
unsigned term_get_cx(void)
{
	return term_cx;
}

// Return the cursor "y" position
unsigned term_get_cy(void)
{
	return term_cy;
}

//-----------------------------
//  I/O handling functions (terminal level)
//-----------------------------

// Return a char read from the terminal
int term_getc(void)
{
	int c=term_in();
	if(isprint(c)) return c;
	else if (c == 0x04) return KC_EOT;	// ctrl D
	else if( c == 0x1B ) {		// escape sequence

		/* A COMPLETER */

	} else {
		switch(c) {
		case 0x0D:
		case 0x0A:		// CR/LF sequence, read the second char (LF) if applicable
			return KC_ENTER;
		case 0x09:
			return KC_TAB;
		case 0x7F:
		case 0x08:
			return KC_BACKSPACE;
		default:
			return KC_UNKNOWN;
		}
	}
	return KC_UNKNOWN;
}

// Write a character to the terminal
void term_putc( char ch )
{
	if( ch == '\n' ) {
		if( term_cy < term_num_rows )
			term_cy ++;
		term_cx = 1;
	} else term_cx++;
	term_out( ch );
}

// Write a string to the terminal
void term_puts( const char* str )
{
	while( *str ) {
		term_putc( *str++ );
	}
}
 
void term_printf(const char* fmt, ...)
{
	va_list        ap;
	char          *p;
	char           ch;
	unsigned long  ul;
	unsigned long  size;
	unsigned int   sp;
	char           s[34];
	
	va_start(ap, fmt);
	while (*fmt != '\0') {
		if (*fmt =='%') {
			size=0; sp=1;
			if (*++fmt=='0') {fmt++; sp=0;}	// parse %04d --> sp=0
			ch=*fmt;
			if ((ch>'0') && (ch<='9')) {	// parse %4d --> size=4
				char tmp[10];
				int i=0;
				while ((ch>='0') && (ch<='9')) {
					tmp[i++]=ch;
					ch=*++fmt;
				}
				tmp[i]='\0';
				size=str2num(tmp,10);
			}
			switch (ch) {
				case '%':
					term_putc('%');
					break;
				case 'c':
					ch = (char)va_arg(ap, int);
					term_putc(ch);
					break;
				case 's':
					p = va_arg(ap, char *);
					term_puts(p);
					break;
				case 'd':
					ul = va_arg(ap, long);
					if ((long)ul < 0) {
						term_putc('-');
						ul = -(long)ul;
						size--;
					}
					num2str(s, ul, 10, size, sp);
					term_puts(s);
					break;
				case 'u':
					ul = va_arg(ap, unsigned int);
					num2str(s, ul, 10, size, sp);
					term_puts(s);
					break;
				case 'o':
					ul = va_arg(ap, unsigned int);
					num2str(s, ul, 8, size, sp);
					term_puts(s);
					break;
				case 'p':
					term_putc('0');
					term_putc('x');
					ul = va_arg(ap, unsigned int);
					num2str(s, ul, 16, size, sp);
					term_puts(s);
					break;
				case 'x':
					ul = va_arg(ap, unsigned int);
					num2str(s, ul, 16, size, sp);
					term_puts(s);
					break;
				default:
				    term_putc(*fmt);
			}
		} else term_putc(*fmt);
		fmt++;
	}
	va_end(ap);
}


//-----------------------------
//  readline functions
//-----------------------------

static char *buffer=NULL;
static const char *prompt=NULL;
static int  maxlen=0;
static int  pos=0;
static int  len=0;

static unsigned tmp_cx, tmp_cy;

static void term_save_pos(void)
{
	term_ansi("s");
	tmp_cx=term_cx;
	tmp_cy=term_cy;
}

static void term_restore_pos(void)
{
	term_cx=tmp_cx;
	term_cy=tmp_cy;
	term_ansi("u");
}

/*
void dbg(int x, int y, int c)
{
	term_ansi("s");
	term_gotoxy(x,y);
	term_ansi("K");term_printf("pos = %d",pos);
	term_gotoxy(x,y+1);
	term_ansi("K");term_printf("len = %d",len);
	term_gotoxy(x,y+2);
	term_ansi("K");term_printf("char = %x",c);
	term_ansi("u");
}*/

int term_readline (const char *prompt_str, char *buf, int maxlength) 
{
	int c;
	
	if (!buf) return 0;
  
	prompt=prompt_str;
	buffer=buf;
	*buffer = '\0';
	maxlen=maxlength;

	pos=0;
	len=0;

	term_clreol();
	if (prompt) term_puts(prompt);

	while(1) {
		c=term_getc();
  		if (c<255) {
			if (len < maxlen) {
				char *s = &buffer[pos];
				unsigned l=strlen(s);
      
				memmove(s+1, s, l+1);
				buffer[pos] = (char)c;
				term_clreol();				// erase to end of line
				pos++;
				len++;
				term_save_pos();				// save cursor pos
				term_puts(s);
				term_restore_pos();				// restore cursor pos
				term_right(1);
			}
  	
  		} else switch (c) {
  			case KC_SUPPR:
				if (buffer[pos]!='\0') {
					char * s=&buffer[pos];
					strcpy(s,s+1);
					term_clreol();			//   erase to end of line
        			len--;
					term_save_pos();         //   save cursor pos
					term_puts(s);
					term_restore_pos();         //   restore cursor pos
				}
				break;
			case KC_BACKSPACE:				// back space
				if (pos > 0) {
					char *s = &buffer[pos];
					strcpy(s-1, s);
			        term_putc('\b');
					term_clreol();			//   erase to end of line
					pos--;
					len--;
					term_save_pos();         //   save cursor pos
					term_puts(s-1);
					term_restore_pos();         //   restore cursor pos
				}
				break;
			case KC_HOME:					// cursor to begin of line
				if (pos>0) {
					term_left(pos);
					pos=0;
				}
				break;
			case KC_END:					// cursor to end of line
				if (pos<len) {
					term_right(len-pos);
					pos=len;
				}
				break;
			case KC_RIGHT:
				if (pos<len) {
					term_right(1);
					pos++;
				}
				break;
			case KC_LEFT:
				if (pos>0) {
					term_left(1);
					pos--;
				}
				break;
			case KC_ENTER:
				return len;
			case KC_EOT:					// ctrl D
				return -1;
		}
	}
	return len;
}
