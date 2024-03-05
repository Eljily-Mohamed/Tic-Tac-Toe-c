#ifndef _RCC_H_
#define _RCC_H_

#ifdef __cplusplus
extern "C" {
#endif 

#define HSI_VALUE	16000000U
#define HSE_VALUE	8000000U

typedef struct _Clock_t {
	uint32_t	main_osc_is_hse;
	uint32_t	ahb_freq;
	uint32_t	apb1_freq;
	uint32_t	apb1_timer_freq;
	uint32_t	apb2_freq;
	uint32_t	apb2_timer_freq;
	uint32_t	i2s_freq;			/* PLL I2S output */
} Clock_t;

typedef struct {
	uint32_t	M, N, R;
} I2SClkCfg_t;

enum {
	CLOCK_CONFIG_HSE_8MHz=0,
	CLOCK_CONFIG_HSE_48MHz,
	CLOCK_CONFIG_HSE_84MHz,
	CLOCK_CONFIG_HSE_96MHz,
	CLOCK_CONFIG_HSI_16MHz,
	CLOCK_CONFIG_HSI_48MHz,
	CLOCK_CONFIG_HSI_84MHz,
	CLOCK_CONFIG_HSI_96MHz,
	CLOCK_CONFIG_END
};

void rcc_sys_clk_cfg(uint32_t config);
void rcc_i2s_clk_cfg(const I2SClkCfg_t *cfg);

#ifdef __cplusplus
}
#endif

#endif
