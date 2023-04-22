#ifndef PARSER_H
#define PARSER_H

#include <Arduino.h>

#include "main.h"
#include "motor.h"
#include "asv.h"

#include "../config.h"

typedef enum
{
  PREAMBLE         = 0,
  DATA             = 1,
  CSUM             = 2
} m_parser;

extern unsigned long start;

void parser(uint8_t byte);
void parse_info(char *text);
void send_data();

#endif