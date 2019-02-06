#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <stdbool.h>
#include <stddef.h>

// #include "i2c.h"

static void clock_setup(void)
{
	// rcc_clock_setup_hsi(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);
}


int main(void)
{
	clock_setup();
	// i2c_setup();
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8 | GPIO4);
	// gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO13);


	// for (uint32_t i = 0; i < 1000; i++) {
	// 	gpio_toggle(GPIOA, GPIO5);
	// 	for (uint32_t j = 0; j < i; j++) {
	// 		__asm__("nop");
	// 	}
	// }


	size_t second = 1600000;

	bool led_on = true;
	size_t freq = second/1024;

	while (1) {

		freq -= 50;
		if (freq <= 50) {
			freq = second/1024;
		}

		size_t periods = second / freq/40;

		for (size_t i = 0; i < periods; i++) {

			for (uint32_t i = 0; i < freq; i++) {
				__asm__("nop");
			}
			if (led_on) {
				gpio_set(GPIOA, GPIO8 | GPIO4);
			} else {
				gpio_clear(GPIOA, GPIO8 | GPIO4);
			}

			led_on = !led_on;

		}

		// if (!gpio_get(GPIOC, GPIO13)) {
		// 	gpio_toggle(GPIOA, GPIO5);
		// 	for (uint32_t i = 0; i < 400000; i++) {
		// 		__asm__("nop");
		// 	}
		// } else {
		// 	gpio_clear(GPIOA, GPIO5);
		// }
	}

	return 0;
}
