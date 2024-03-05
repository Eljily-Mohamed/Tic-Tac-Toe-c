#ifndef _SPI_H_
#define _SPI_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include "include/board.h"

#define SPI_MODE0				0
#define SPI_MODE1				1
#define SPI_MODE2				2
#define SPI_MODE3				3

#define SPI_LSB_FIRST			(1<<7)
#define SPI_DATA_16				(1<<11)

#define SPI_BUSY				1  		// transfer busy
#define SPI_OK					0		// transfer ended No Errors
#define SPI_ERROR				-1  	// err: general error

/* spi_init
 *   initialize SPI device
 */
int spi_master_init(SPI_t *spi, uint32_t max_rate, uint32_t cfg);

/* spi_write
 *   write data
 */
void spi_write(SPI_t *spi, uint8_t *data, uint32_t n);
void spi_write_byte(SPI_t *spi, uint8_t data);

void spi_transmit(SPI_t *spi, uint8_t *data, int size);
void spi_receive(SPI_t *spi, uint8_t *data, int size);
void spi_transmit_receive(SPI_t *spi, uint8_t *data, int size);

int spi_dma_write(SPI_t *spi, uint8_t *data, uint32_t n);
int spi_dma_write_n(SPI_t *spi, uint8_t data, uint32_t n);
int spi_dma_write16(SPI_t *spi, uint16_t *data, uint32_t n);
int spi_dma_write16_n(SPI_t *spi, uint16_t data, uint32_t n);

#ifdef __cplusplus
}
#endif
#endif