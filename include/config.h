/****************************************************************************
 * IRQ Priority
 ****************************************************************************/
#define SYSTICK_PRIORITY			0
#define SVC_PRIORITY				0

#define EXTI0_IRQ_PRIORITY			8
#define EXTI1_IRQ_PRIORITY			8
#define EXTI2_IRQ_PRIORITY			8
#define EXTI3_IRQ_PRIORITY			8
#define EXTI4_IRQ_PRIORITY			8
#define EXTI9_5_IRQ_PRIORITY		8
#define EXTI15_10_IRQ_PRIORITY		8

#define TIM2_IRQ_PRIORITY			4
#define TIM3_IRQ_PRIORITY			4
#define TIM4_IRQ_PRIORITY			4
#define TIM5_IRQ_PRIORITY			4

#define	USART1_IRQ_PRIORITY			3
#define	USART2_IRQ_PRIORITY			3
#define	USART6_IRQ_PRIORITY			3

#define	I2C1_IRQ_PRIORITY			2
#define	I2C1_IRQERR_PRIORITY		1
#define	I2C2_IRQ_PRIORITY			2
#define	I2C2_IRQERR_PRIORITY		1
#define	I2C3_IRQ_PRIORITY			2
#define	I2C3_IRQERR_PRIORITY		1

#define SPI1_IRQ_PRIORITY			4
#define SPI2_IRQ_PRIORITY			4
#define SPI3_IRQ_PRIORITY			4
#define SPI4_IRQ_PRIORITY			4
#define SPI5_IRQ_PRIORITY			4

#define ADC1_IRQ_PRIORITY			5

#define DMA1_STREAM0_PRIORITY		2
#define DMA1_STREAM1_PRIORITY		2
#define DMA1_STREAM2_PRIORITY		2
#define DMA1_STREAM3_PRIORITY		6
#define DMA1_STREAM4_PRIORITY		2
#define DMA1_STREAM5_PRIORITY		2
#define DMA1_STREAM6_PRIORITY		2
#define DMA1_STREAM7_PRIORITY		2

#define DMA2_STREAM0_PRIORITY		2
#define DMA2_STREAM1_PRIORITY		2
#define DMA2_STREAM2_PRIORITY		2
#define DMA2_STREAM3_PRIORITY		2
#define DMA2_STREAM4_PRIORITY		2
#define DMA2_STREAM5_PRIORITY		2
#define DMA2_STREAM6_PRIORITY		2
#define DMA2_STREAM7_PRIORITY		2

/****************************************************************************
 * GPIO Pin and use configuration 
 ****************************************************************************/
#ifdef USE_MBEDSHIELD
	// LEDS: libshield/leds.[ch]
	#define LED_RED_GPIO_PORT		_GPIOB
	#define LED_RED_GPIO_PINS		PIN_4
	#define LED_RED_GPIO_CFG		PIN_MODE_OUTPUT             |   \
									PIN_OPT_RESISTOR_NONE       |   \
									PIN_OPT_OUTPUT_PUSHPULL     |   \
									PIN_OPT_OUTPUT_SPEED_MEDIUM
	
	#define LED_GREEN_GPIO_PORT		_GPIOC
	#define LED_GREEN_GPIO_PINS		PIN_7
	#define LED_GREEN_GPIO_CFG		PIN_MODE_OUTPUT             |   \
									PIN_OPT_RESISTOR_NONE       |   \
									PIN_OPT_OUTPUT_PUSHPULL     |   \
									PIN_OPT_OUTPUT_SPEED_MEDIUM
	
	#define LED_BLUE_GPIO_PORT		_GPIOA
	#define LED_BLUE_GPIO_PINS		PIN_9
	#define LED_BLUE_GPIO_CFG		PIN_MODE_OUTPUT             |   \
									PIN_OPT_RESISTOR_NONE       |   \
									PIN_OPT_OUTPUT_PUSHPULL     |   \
									PIN_OPT_OUTPUT_SPEED_MEDIUM
	
	// SWITCHES: libshield/sw.[ch]
	#define SW_UP_GPIO_PORT			_GPIOA
	#define SW_UP_GPIO_PINS			PIN_4
	#define SW_UP_GPIO_CFG			PIN_MODE_INPUT | PIN_OPT_RESISTOR_NONE
	
	#define SW_DOWN_GPIO_PORT		_GPIOB
	#define SW_DOWN_GPIO_PINS		PIN_0
	#define SW_DOWN_GPIO_CFG		PIN_MODE_INPUT | PIN_OPT_RESISTOR_NONE
	
	#define SW_LEFT_GPIO_PORT		_GPIOC
	#define SW_LEFT_GPIO_PINS		PIN_1
	#define SW_LEFT_GPIO_CFG		PIN_MODE_INPUT | PIN_OPT_RESISTOR_NONE
	
	#define SW_RIGHT_GPIO_PORT		_GPIOC
	#define SW_RIGHT_GPIO_PINS		PIN_0
	#define SW_RIGHT_GPIO_CFG		PIN_MODE_INPUT | PIN_OPT_RESISTOR_NONE
	
	#define SW_CENTER_GPIO_PORT		_GPIOB
	#define SW_CENTER_GPIO_PINS		PIN_5
	#define SW_CENTER_GPIO_CFG		PIN_MODE_INPUT | PIN_OPT_RESISTOR_NONE
	
	
	// LCD: lcd_128x32.[ch]
	#define LCD_A0_GPIO_PORT		_GPIOA
	#define LCD_A0_GPIO_PINS		PIN_8
	#define LCD_A0_GPIO_CFG			PIN_MODE_OUTPUT             |   \
									PIN_OPT_RESISTOR_NONE       |   \
									PIN_OPT_OUTPUT_PUSHPULL     |   \
									PIN_OPT_OUTPUT_SPEED_MEDIUM
	
	#define LCD_CS_N_GPIO_PORT		_GPIOB
	#define LCD_CS_N_GPIO_PINS		PIN_6
	#define LCD_CS_N_GPIO_CFG		PIN_MODE_OUTPUT             |   \
									PIN_OPT_RESISTOR_NONE       |   \
									PIN_OPT_OUTPUT_PUSHPULL     |   \
									PIN_OPT_OUTPUT_SPEED_MEDIUM
	
	#define LCD_RESET_GPIO_PORT		_GPIOA
	#define LCD_RESET_GPIO_PINS		PIN_6
	#define LCD_RESET_GPIO_CFG		PIN_MODE_OUTPUT             |   \
									PIN_OPT_RESISTOR_NONE       |   \
									PIN_OPT_OUTPUT_PUSHPULL     |   \
									PIN_OPT_OUTPUT_SPEED_MEDIUM
#endif



/****************************************************************************
 * TIMER Pin and use configuration:
 ****************************************************************************/

//#define USE_TIM3
//#define TIM3_GPIO_PORT	
//#define TIM3_GPIO_PINS	
//#define TIM3_GPIO_CFG		

/****************************************************************************
 * USART Pin and use configuration:
 ****************************************************************************/
// USART2: Tx --> PA9, Rx --> PA10

#define USE_USART1
#define USART1_GPIO_PORT  _GPIOA
#define USART1_GPIO_PINS  PIN_9 | PIN_10
#define USART1_GPIO_CFG   PIN_MODE_ALTFUNC|PIN_OPT_OUTPUT_SPEED_MEDIUM|PIN_OPT_AF7

// USART2: Tx --> PA2, Rx --> PA3

#define USE_USART2
#define USART2_GPIO_PORT	_GPIOA
#define USART2_GPIO_PINS	PIN_2 | PIN_3
#define USART2_GPIO_CFG		PIN_MODE_ALTFUNC|PIN_OPT_OUTPUT_SPEED_MEDIUM|PIN_OPT_AF7

// USART2: Tx --> PA11, Rx --> PA12
#define USE_USART6
#define USART6_GPIO_PORT	_GPIOA
#define USART6_GPIO_PINS	PIN_11 | PIN_12
#define USART6_GPIO_CFG	    PIN_MODE_ALTFUNC|PIN_OPT_OUTPUT_SPEED_MEDIUM|PIN_OPT_AF8

/****************************************************************************
 *  I2C Pin and use configuration:
 ****************************************************************************/

// I2C1 : SCL --> PB8, SDA --> PB9
//#define USE_I2C1
//#define I2C1_GPIO_PORT	
//#define I2C1_GPIO_PINS	
//#define I2C1_GPIO_CFG		

//#define USE_I2C2
//#define I2C2_GPIO_PORT
//#define I2C2_GPIO_PINS
//#define I2C2_GPIO_CFG

//#define USE_I2C3
//#define I2C3_GPIO_PORT
//#define I2C3_GPIO_PINS
//#define I2C3_GPIO_CFG

/****************************************************************************
 *  SPI pin and use configuration:
 ****************************************************************************/

#ifdef USE_MBEDSHIELD
	// SPI1 pins : LCD_SCK   --> D13 --> PA5 : SPI1_SCK
	//             LCD_MOSI  --> D11 --> PA7 : SPI1_MOSI
	#define USE_SPI1
	#define SPI1_GPIO_PORT		_GPIOA
	#define SPI1_GPIO_PINS		PIN_5|PIN_7
	#define SPI1_GPIO_CFG		PIN_MODE_ALTFUNC|PIN_OPT_OUTPUT_SPEED_MEDIUM|PIN_OPT_AF5
#endif

//#define USE_SPI2
//#define SPI2_GPIO_PORT	
//#define SPI2_GPIO_PINS	
//#define SPI2_GPIO_CFG		

//#define USE_SPI3
//#define SPI3_GPIO_PORT
//#define SPI3_GPIO_PINS			
//#define I2C3_GPIO_CFG

//#define USE_SPI4
//#define SPI4_GPIO_PORT
//#define SPI4_GPIO_PINS			
//#define I2C4_GPIO_CFG

//#define USE_SPI5
//#define SPI5_GPIO_PORT
//#define SPI5_GPIO_PINS			
//#define I2C5_GPIO_CFG

/****************************************************************************
 *  ADC pin and use configuration:
 ****************************************************************************/

// ADC1: ADC1_0 --> PA0, ADC1_1 -->PA1
//#define USE_ADC1
//#define ADC1_GPIO_PORT	
//#define ADC1_GPIO_PINS	
//#define ADC1_GPIO_CFG		

/****************************************************************************
 *  USB device pin and use configuration:
 ****************************************************************************/

// USBD: SOF out --> PA8 (not used), VBUS detect --> PA9, DM -->PA11, DP --> PA12
//#define USE_USBD
//#define USBD_GPIO_PORT		
//#define USBD_GPIO_PINS		
//#define USBD_GPIO_CFG		
