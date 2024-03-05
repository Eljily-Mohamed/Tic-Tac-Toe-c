#ifndef _LEDS_H_
#define _LEDS_H_


#define LED_RED_NUM	    (2)
#define LED_GREEN_NUM	(1)
#define LED_BLUE_NUM	(0)
#define LED_RED 	    (1 << LED_RED_NUM)
#define LED_GREEN   	(1 << LED_GREEN_NUM)
#define LED_BLUE    	(1 << LED_BLUE_NUM)


/* leds_init
 *
 * configure gpio to drive the RGB led
 */
uint32_t leds_init(void);

/* leds
 *
 * write 'val' on leds {red, green, blue}
 */
void leds(uint16_t val);

/* red_led
 *
 * on != 0 => red led on, on = 0 => red led off
 */
void red_led(uint32_t on);

/* green_led
 *
 * on != 0 => green led on, on = 0 => green led off
 */
void green_led(uint32_t on);

/* blue_led
 *
 * on != 0 => blue led on, on = 0 => blue led off
 */
void blue_led(uint32_t on);

# endif /* _LEDS_H_ */
