#ifndef _TIMER_H_
#define _TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include "include/board.h"

typedef void (*OnTick)(void);

/***************************************************************************/
/* timer_wait_ms
 *   wait for ms millisecoonds function
 */
int timer_wait_ms(TIM_t *tmr, uint32_t ms, OnTick cb);

/* timer_wait_us
 *   wait for us microsecoonds function
 */
int timer_wait_us(TIM_t *tmr, uint32_t us, OnTick cb);

/***************************************************************************/
/* timer_tick_init
 *   setup timer to call cb function periodically, each tick_ms
 */
int timer_tick_init(TIM_t *tmr, uint32_t tick_ms, OnTick cb);

/* timer_tick_period
 *   change the tick_ms period
 */
int timer_tick_period(TIM_t *tmr, uint32_t tick_ms);

/* timer_count_init
 *   setup timer to count each timebase_us us
 */
int timer_count_init(TIM_t *tmr, uint32_t timebase_us);

/* timer_start
 *   start counting to generate ticks
 */
void timer_start(TIM_t *tmr);

/* timer_stop
 *   stop and reset counting
 */
void timer_stop(TIM_t *tmr);

/* timer_read
 *   return the counter value
 */
uint32_t timer_read(TIM_t *tmr);

/***************************************************************************/
#define PWM_CHANNEL_1		0
#define PWM_CHANNEL_2		1
#define PWM_CHANNEL_3		2
#define PWM_CHANNEL_4		3

/* pwm_init
 *   setup pwm timer period, each tick_ms
 */
int pwm_init(PWM_t *pwm, uint32_t period_ms, OnTick cb);

/* pwm_channel_enable
 *   set up pwm channel
 */
int pwm_channel_enable(PWM_t *pwm, uint32_t channel, uint32_t dutycycle, uint32_t oe);

/* pwm_channel_disable
 *   disable pwm channel
 */
int pwm_channel_disable(PWM_t *pwm, uint32_t channel);

/* pwm_channel_set
 *   set up dutycycle for pwm channel
 */
int pwm_channel_set(PWM_t *pwm, uint32_t channel, uint32_t dutycycle);

/* pwm_start
 *   start counting
 */
#define pwm_start(pwm)	timer_start(pwm)

/* pwm_stop
 *   stop and reset counting
 */
#define pwm_stop(pwm)	timer_stop(pwm)

/***************************************************************************/
#define TIM_IN_RISING
#define TIM_IN_FALLING


#ifdef __cplusplus
}
#endif
#endif
