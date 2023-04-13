#ifndef USART_H
#define USART_H

#include <Arduino.h>

#include "../config.h"

uint8_t usart_CRC8(char *data);
void usart_send_char(char byte);
void usart_send_string(char *str);
void usart_print_value_parameter_decimal(char *text, double value, char *unit);
void usart_print_value_parameter(char *text, double value, char *unit);
void usart_send_ack(char *text);
void usart_send_nack(char *text);
void usart_send_version(int ver, int rev, int pat);

#endif