

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

int main(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
	gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO13);


	for (int32_t i = 0; i < 1000; i++) {
		gpio_toggle(GPIOA, GPIO5);
		for (uint32_t j = 0; j < i; j++) {
			__asm__("nop");
		}
	}


	while (1) {
		if (!gpio_get(GPIOC, GPIO13)) {
			gpio_toggle(GPIOA, GPIO5);
			for (uint32_t i = 0; i < 400000; i++) {
				__asm__("nop");
			}
		} else {
			gpio_clear(GPIOA, GPIO5);
		}
	}

	return 0;
}
