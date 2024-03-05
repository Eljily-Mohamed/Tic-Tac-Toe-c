#ifndef _SW_H_
#define _SW_H_

#define SW_RIGHT_NUM	    (0)
#define	SW_LEFT_NUM		    (1)
#define SW_UP_NUM		    (2)
#define	SW_DOWN_NUM		    (3)
#define	SW_CENTER_NUM	    (4)
#define SW_RIGHT            (1 << SW_RIGHT_NUM)
#define	SW_LEFT		        (1 << SW_LEFT_NUM)
#define SW_UP		        (1 << SW_UP_NUM)
#define	SW_DOWN		        (1 << SW_DOWN_NUM)
#define	SW_CENTER	        (1 << SW_CENTER_NUM)


/* sw_init
 *
 * configure gpio to read the switches state
 */
uint32_t sw_init(void);

/* sw_right
 *
 * return 1 the first time the right switch stablely pressed
 */
uint32_t sw_right(void);

/* sw_left
 *
 * return 1 the first time the left switch stablely pressed
 */
uint32_t sw_left(void);

/* sw_up
 *
 * return 1 the first time the up switch stablely pressed
 */
uint32_t sw_up(void);

/* sw_down
 *
 * return 1 the first time the down switch stablely pressed
 */
uint32_t sw_down(void);

/* sw_center
 *
 * return 1 the first time the center switch stablely pressed
 */
uint32_t sw_center(void);

/* sw_input
 *
 * return state of the 5 buttons
 * {CENTER, DOWN, UP, LEFT, RIGHT}
 */
uint32_t sw_input(void);


# endif /* _SW_H_ */
