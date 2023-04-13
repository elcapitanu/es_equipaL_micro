#include "parser.h"

#include "usart.h"

float pwm = 0;

const char *CMD_OPTIONS[] = {"START", "STOP", "VERS", "RESET", "PWM"};

char text_received[BUFFER_SIZE];
char text_tx[BUFFER_SIZE * 2];
int cnt_text_received = 0;
uint8_t parser_state = PREAMBLE;
bool isToSendData = false;

unsigned long start;

void parser(uint8_t byte)
{
  if (byte == '@' && cnt_text_received == 0 && parser_state == PREAMBLE)
  {
    text_received[cnt_text_received++] = byte;
    parser_state = DATA;
  }
  else if (byte != '*' && cnt_text_received != 0)
  {
    if (parser_state == DATA)
    {
      text_received[cnt_text_received++] = byte;
    }
    else if (parser_state == CSUM)
    {
#if SPEW_DEBUG_PARSER
      usart_send_string(text_received);
      usart_send_char('\n');
      usart_send_char(usart_CRC8(text_received));
      usart_send_char('\n');
#endif

      if (byte == usart_CRC8(text_received))
      {
#if SPEW_DEBUG_PARSER
        usart_send_ack("CSUM");
#endif
        parse_info(text_received);
        text_received[0] = '\0';
      }
      else
      {
        usart_send_nack((char *)"CSUM");
      }
      parser_state = PREAMBLE;
      cnt_text_received = 0;
    }
  }
  else if (byte == '*' && cnt_text_received != 0)
  {
    text_received[cnt_text_received++] = byte;

#if USE_CSUM
    parser_state = CSUM;
#else
    parse_info(text_received);
    text_received[0] = '\0';
    parser_state = PREAMBLE;
    cnt_text_received = 0;
#endif
  }
  else
  {
    parser_state = PREAMBLE;
    cnt_text_received = 0;
  }
}

void parse_info(char *text)
{
  char *cmd;
  cmd = strtok(text, ",");
  sscanf(text, "@%s", cmd);
  if (strcmp(cmd, CMD_OPTIONS[0]) == 0)
  {
    start = millis();

    ASVmotors.pwmL = 7.5f;
    ASVmotors.pwmR = 7.5f;

    isToSendData = true;
    memset(&text_tx, '\0', sizeof(text_tx));
    sprintf(text_tx, "$RSP,ACK,*");
    usart_send_string(text_tx);
#if USE_CSUM
    usart_send_char(usart_CRC8(text_tx));
#endif
    usart_send_char('\n');
    delay(2);
  }
  else if (strcmp(cmd, CMD_OPTIONS[1]) == 0)
  {
    ASVmotors.pwmL = 7.5f;
    ASVmotors.pwmR = 7.5f;

    isToSendData = false;
    memset(&text_tx, '\0', sizeof(text_tx));
    sprintf(text_tx, "$STOP,*");
    usart_send_string(text_tx);
#if USE_CSUM
    usart_send_char(usart_CRC8(text_tx));
#endif
    usart_send_char('\n');
    delay(2);
  }
  else if (strcmp(cmd, CMD_OPTIONS[2]) == 0 && !isToSendData)
  {
    usart_send_version(DEV_VER, DEV_REV, DEV_PAT);
  }
  else if (strcmp(cmd, CMD_OPTIONS[3]) == 0)
  {
    while (1)
      ;
  }
  else if (strcmp(cmd, CMD_OPTIONS[4]) == 0 && isToSendData)
  {
    char *motor;

    motor = strtok(NULL, ",");

    cmd = strtok(NULL, ",");

    int perc = atoi(cmd);

    if (strcmp(motor, "L") == 0)
    {
      if (perc <= 100 && perc >= -100)
        ASVmotors.pwmL = (float)perc/40.0f + 7.5f;
    }
    else if (strcmp(motor, "R") == 0)
    {
      if (perc <= 100 && perc >= -100)
        ASVmotors.pwmR = (float)perc/40.0f + 7.5f;
    }
  }
}

void send_data()
{
  if (isToSendData)
  {
    /* memset(&text_tx, '\0', sizeof(text_tx));
    sprintf(text_tx, "$PRESS,%hd,*", 42);
    usart_send_string(text_tx);
#if USE_CSUM
    usart_send_char(usart_CRC8(text_tx));
#endif
    usart_send_char('\n');
    delay(2); */
  }
}