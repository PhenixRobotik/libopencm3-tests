#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "i2c.h"
#include "usart_usb.h"

static void clock_setup(void)
{
	// rcc_clock_setup_hsi(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);
}


int main(void)
{
	clock_setup();
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
	gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO13);

	usart_usb_setup();
	usart_usb_backspace();
	usart_usb_send_line("", 0);











	while (1) {
		usart_usb_send_line("goodbye !", 9);
		gpio_toggle(GPIOA, GPIO5);
		for (uint32_t i = 0; i < 4000000; i++) {
			__asm__("nop");
		}
	}

	return 0;
}
