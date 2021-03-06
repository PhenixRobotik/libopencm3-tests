#include "pwm.h"

#include <libopencm3/stm32/l4/timer.h>
// #include <libopencm3/stm32/l4/gpio.h>

void pwm_init(Peripheral* timer, tim_oc_id channel,
        Pin outPin, AltFunction::Number altFunction,
        uint32_t prescaler, uint32_t period) {
  // Enable timer clock
  // m_timer->enable();
  // Enable GPIO clock
  // m_pin.port->enable();

  // Reset timer peripheral
  timer_set_mode (m_timer->Id,
                  TIM_CR1_CKD_CK_INT,
                  TIM_CR1_CMS_EDGE,
                  TIM_CR1_DIR_UP);

  timer_set_repetition_counter(m_timer->Id, 0);
  timer_enable_preload        (m_timer->Id);
  timer_continuous_mode       (m_timer->Id);
  timer_set_period            (m_timer->Id, period);
  timer_set_prescaler         (m_timer->Id, prescaler);

  // Setup GPIO
  gpio_mode_setup(m_pin.port->Id, GPIO_MODE_AF, GPIO_PUPD_NONE,    m_pin.number);
  gpio_set_af(    m_pin.port->Id, m_out_af, m_pin.number);
  gpio_set_output_options(
                  m_pin.port->Id, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, m_pin.number);


  timer_enable_break_main_output(m_timer->Id); // That's specific to Timer1
  timer_disable_oc_output (m_timer->Id, m_channel);
  timer_set_oc_mode       (m_timer->Id, m_channel, TIM_OCM_PWM1);
}
