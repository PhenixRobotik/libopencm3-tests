#include "i2c.h"


#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>

#include "usart_usb.h"

void i2c_setup() {
	// TODO interrupt on gpio useful ?
	// gpio_mode_setup(GPIOA,
	// 		GPIO_MODE_OUTPUT,
	// 		GPIO_PUPD_NONE,
	// 		GPIO0);

	// TODO clean HAL and debug libopencm3
	rcc_periph_clock_enable(RCC_GPIOB);
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO8 | GPIO9);
	gpio_set_output_options(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_HIGH, GPIO8 | GPIO9);
	gpio_set_af(GPIOB, GPIO_AF4, GPIO8 | GPIO9);

	rcc_periph_clock_enable(RCC_I2C1);
	// RCC_CFGR3 |= RCC_CFGR3_I2C1SW;
	// rcc_set_i2c_clock_hsi(I2C1);

	I2C_TIMINGR(I2C1) = 0x0000020B & 0xF0FFFFFF;
	i2c_reset(I2C1);
	i2c_set_speed(I2C1, i2c_speed_fmp_1m, 8);
	i2c_peripheral_disable  (I2C1);
	i2c_set_7bit_addr_mode  (I2C1);
	i2c_enable_stretching   (I2C1);
	i2c_enable_analog_filter(I2C1);
	i2c_peripheral_enable   (I2C1);
}


// void i2c_setup() {
// 	rcc_periph_clock_enable(RCC_I2C1);
// 	rcc_periph_clock_enable(RCC_GPIOB);
// 	// rcc_set_i2c_clock_hsi(I2C1);
//
// 	i2c_reset(I2C1);
// 	/* Setup GPIO pin GPIO_USART2_TX/GPIO9 on GPIO port A for transmit. */
// 	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO8 | GPIO9);
// 	gpio_set_af(GPIOB, GPIO_AF4, GPIO6 | GPIO7);
// 	i2c_peripheral_disable(I2C1);
//
// 	//configure ANFOFF DNF[3:0] in CR1
// 	i2c_enable_analog_filter(I2C1);
// 	i2c_set_digital_filter(I2C1, 0);
// 	/* HSI is at 8Mhz */
// 	// i2c_set_speed(I2C1, i2c_speed_sm_100k, 8);
// 	//configure No-Stretch CR1 (only relevant in slave mode)
// 	// i2c_enable_stretching(I2C1);
// 	//addressing mode
// 	i2c_set_7bit_addr_mode(I2C1);
// 	i2c_peripheral_enable(I2C1);
// }

void i2c_test() {
	usart_usb_send_line("sending", 7);

	uint8_t a = 0x14;
	// i2c_HAL_write_register(0x52, 0xC0, &a, 1);
	i2c_transfer7(I2C1, 0xC0, NULL, 0, &a, 1);
	usart_usb_send_line("sent", 4);
}
