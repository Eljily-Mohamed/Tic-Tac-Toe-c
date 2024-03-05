#ifndef _DMA_H_
#define _DMA_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include "include/board.h"

/************************* DMA Status ***************************/
#define	DMA_TC					(0)
#define DMA_BAD_DMA				(-1)
#define DMA_BAD_STREAM			(-2)
#define DMA_FIFO_ERR			(-3)
#define DMA_DIRECT_ERR			(-4)
#define DMA_STREAM_ERR			(-5)
#define DMA_UNSUPPORTED			(-6)

/************************ DMA EndPoints *************************/
// Mem and Periph options
#define EP_FMT_BYTE				(0<<11)	/* MSIZE -> CR[14:13] / PSIZE -> CR[12:11] */
#define EP_FMT_HALF				(1<<11)
#define EP_FMT_WORD				(2<<11)

#define EP_BURST_1				(0<<21)	/* MBURST -> CR[24:23] / PBURST -> CR[22:21] */
#define EP_BURST_4				(1<<21)
#define EP_BURST_8				(2<<21)
#define EP_BURST_16				(3<<21)

#define EP_AUTOINC				(1<<9)	/* MINC -> CR[10] / PINC -> CR[9] */

// Mem EndPoint specific options
#define EP_BUF_CIRC				(1<<6)	/* Circular buffer CR[8] */
#define EP_BUF_DBL				((1<<16)|(1<<6))	/* Double buffer   CR[18] and CR[8] */

// Periph Endpoint specific options
#define EP_FLOWCTRL				(1<<5)	/* CR[5] */

typedef enum {
	EP_UART_TX,
	EP_UART_RX,
	EP_I2C_TX,
	EP_I2C_RX,
	EP_SPI_TX,
	EP_SPI_RX,
	EP_ADC,
	EP_MEM
} Peripheral;

typedef struct _DMAEndPoint {
	Peripheral	type;
	void*		addr0;
	void*		addr1;
	int			channel;
	uint32_t	cfg;
} DMAEndPoint_t;

/************************ DMA Streams **************************/
/* stream init configuration */
#define STRM_PRIO_LOW			(0<<16)
#define STRM_PRIO_MEDIUM		(1<<16)
#define STRM_PRIO_HIGH			(2<<16)
#define STRM_PRIO_VERYHIGH		(3<<16)

#define STRM_FIFO_ON			(0x4)
#define STRM_FIFO_TH1			(0x4)
#define STRM_FIFO_TH2			(0x5)
#define STRM_FIFO_TH3			(0x6)
#define STRM_FIFO_TH4			(0x7)

typedef void (*OnTC)(uint32_t stream, uint32_t bufid);


DMA_Stream_t* dma_stream_init(DMA_t* dma, uint32_t stream, DMAEndPoint_t *src, DMAEndPoint_t *dest, uint32_t mode, OnTC cb);

int dma_start(DMA_Stream_t* s, uint16_t size);
int dma_stop (DMA_Stream_t *s);

int dma_complete(DMA_Stream_t *s);

int dma_status(DMA_t* dma, uint32_t stream);

#ifdef __cplusplus
}
#endif
#endif
