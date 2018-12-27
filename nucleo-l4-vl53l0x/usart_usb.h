#pragma once

#include <stdint.h>

void usart_usb_setup();
void usart_usb_send_c(char c);
void usart_usb_send_line(char* line, uint32_t len);
void usart_usb_backspace();
