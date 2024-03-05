#include <stdlib.h>
#include <stdarg.h>
#include "uart.h"
#include "io.h"
#include "util.h"
                             
#ifdef USE_USART1
static OnUartRx usart1_cb=0;

void USART1_IRQHandler(void)
{
	uint32_t sr = _USART1->SR;
	
	if (sr & (1<<5)) {			// Read data register not empty interrupt
		if (!((sr & (1<<2)) || (sr & (1<<2)))) {
			if (usart1_cb) usart1_cb((char)_USART1->DR);
		} else {				// Noise or framing error or break detected
			_USART1->DR;
		}
	} else if (sr & (1<<4)) {	// idle interrupt
		_USART1->DR;
	} else if (sr & (1<<3)) {	// overrun interrupt
		_USART1->DR;
	} else if (sr & (1<<0)) {	// parity error interrupt
		_USART1->DR;
	}
}
#endif

#ifdef USE_USART2
static OnUartRx usart2_cb=0;

void USART2_IRQHandler(void)
{
	uint32_t sr = _USART2->SR;

	if (sr & (1<<5)) {			// Read data register not empty interrupt
		if (!((sr & (1<<2)) || (sr & (1<<2)))) {
			if (usart2_cb) usart2_cb((char)_USART2->DR);
		} else {				// Noise or framing error or break detected
			_USART2->DR;
		}
	} else if (sr & (1<<4)) {	// idle interrupt
		_USART2->DR;
	} else if (sr & (1<<3)) {	// overrun interrupt
		_USART2->DR;
	} else if (sr & (1<<0)) {	// parity error interrupt
		_USART2->DR;
	}
}
#endif

#ifdef USE_USART6
static OnUartRx usart6_cb=0;

void USART6_IRQHandler(void)
{
	uint32_t sr = _USART6->SR;
	
	if (sr & (1<<5)) {			// Read data register not empty interrupt
		if (!((sr & (1<<2)) || (sr & (1<<2)))) {
			if (usart6_cb) usart6_cb((char)_USART6->DR);
		} else {				// Noise or framing error or break detected
			_USART6->DR;
		}
	} else if (sr & (1<<4)) {	// idle interrupt
		_USART6->DR;
	} else if (sr & (1<<3)) {	// overrun interrupt
		_USART6->DR;
	} else if (sr & (1<<0)) {	// parity error interrupt
		_USART6->DR;
	}
}
#endif

/*
 * uart_init : polling Tx and IRQ Rx
 */
int uart_init(USART_t *u, uint32_t baud, uint32_t mode, OnUartRx cb)
{
	IRQn_t	irq_number;
	uint32_t irq_priority;
	
	if (u == _USART1) {
#ifdef USE_USART1
		// enable USART clocking
		 _RCC->APB2ENR |= (1<<4);
		// configure Tx/Rx pins : Tx -->, Rx --> 
		io_configure(USART1_GPIO_PORT, USART1_GPIO_PINS, USART1_GPIO_CFG, NULL);
		// configure USART speed
		u->BRR = sysclks.apb2_freq/baud;
#else
		return -1;
#endif
	 } else if (u == _USART2) {
#ifdef USE_USART2
		// enable USART clocking
		_RCC->APB1ENR |= (1<<17);
		// configure Tx/Rx pins : Tx --> PA2, Rx --> PA3
		io_configure(USART2_GPIO_PORT, USART2_GPIO_PINS, USART2_GPIO_CFG, NULL);
		// equivalent to io_configure(_GPIOA, PIN_2|PIN_3, USART_PIN_CONFIG);
		
		usart2_cb=cb;
		irq_number=38;
		irq_priority=3;
		// configure USART speed
		u->BRR = sysclks.apb1_freq/baud;
#else
		return -1;
#endif
	} else if (u == _USART6) {
#ifdef USE_USART6
		// enable USART clocking
		 _RCC->APB2ENR |= (1<<5);
		// configure Tx/Rx pins
		io_configure(USART6_GPIO_PORT, USART6_GPIO_PINS, USART6_GPIO_CFG, NULL);

		usart6_cb=cb;
		irq_number=71;
		irq_priority=3;

		// configure USART speed
		u->BRR = sysclks.apb2_freq/baud;
#else
		return -1;
#endif
	} else {
		return -1;
	}
	
	u->GTPR = 0;
	u->CR3 = 0;
	u->CR2 = UART_STOP_1;
	u->CR1 = (UART_CHAR_8 | UART_PAR_NO | (1<<13) | (1<<2) | (1<<3) | (1<<5)) ;
			 
	// Setup NVIC
	if (cb) {
		// configure NVIC
		NVIC_SetPriority(irq_number, irq_priority ); //voir include/cmsis/core_cm4.h & include/config.h
	    NVIC_EnableIRQ(irq_number);
	}
	
    return 1;
}

/*
 * uart_getc : get a char from the serial link (blocking)
 */
char uart_getc(USART_t *u) {
  // Wait for Data Register full
  while (!(u->SR & (1 << 5))) {}
  // Read the received character
  return (char)u->DR;
}


/*
 * uart_getchar : check if a char has been received from the serial link
 * (non-blocking)
 */
int uart_getchar(USART_t *u, char *c)
{
	if(u->DR == *c){
		return 1;
	}
	return 0;
}

/*
 * uart_putc : send a char over the serial link (polling)
 */
void uart_putc(USART_t *u, char c)
{
	// wait for Data Register empty
	while((u->SR & (1<<7)) == 0){}
	// write char to send
	u->DR = c;										
}

/*
 * uart_puts : send a string over the serial link (polling)
 */
void uart_puts(USART_t *u, const char *s)
{
	while(*s){
		// wait for Data Register empty
		while((u->SR & (1<<7)) == 0){}
		// send a char
		u->DR = *s++;
	}
	
}

/*
 * uart_printf : print formatted text to serial link
 */
void uart_printf(USART_t * u, const char* fmt, ...)
{
	va_list        ap;
	char          *p;
	char           ch;
	unsigned long  ul;
	char           s[34];
	
	va_start(ap, fmt);
	while (*fmt != '\0') {
		if (*fmt =='%') {
			switch (*++fmt) {
				case '%':
					uart_putc(u,'%');
					break;
				case 'c':
					ch = (char)va_arg(ap, int);
					/* A COM    PLETER */
					break;
				case 's':
					/* A COMPLETER */
					break;
				case 'd':
					/* A COMPLETER */
					break;
				case 'u':
					/* A COMPLETER */
					break;
				case 'x':
					/* A COMPLETER */
					break;
				default:
				    uart_putc(u, *fmt);
			}
		} else uart_putc(u, *fmt);
		fmt++;
	}
	va_end(ap);
}
