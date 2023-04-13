#include "usart.h"
#include "parser.h"

//! Control UART buffer.
char rx_buffer[BUFFER_SIZE];
char tx_buffer[BUFFER_SIZE];
//! Counter id for buffer rx
int cnt_id_rx = 0;

uint8_t
usart_CRC8(char *data)
{
  uint8_t csum = 0x00;
  uint8_t t = 0;
  while (data[t] != '*')
  {
    csum ^= data[t];
    t++;
  }
  return (csum | 0x80);
  // return csum;
}

void usart_send_char(char byte)
{
  Serial.print(byte);
}

void usart_send_string(char *str)
{
  Serial.print(str);
}

void usart_send_ack(char *text)
{
  memset(&tx_buffer, '\0', sizeof(tx_buffer));
  sprintf(tx_buffer, "$RSP,ACK,%s,*", text);
  usart_send_string(tx_buffer);
#if USE_CSUM
  usart_send_char(usart_CRC8(tx_buffer));
#endif
  usart_send_char('\n');
}

void usart_send_nack(char *text)
{
  memset(&tx_buffer, '\0', sizeof(tx_buffer));
  sprintf(tx_buffer, "$RSP,NACK,%s,*", text);
  usart_send_string(tx_buffer);
#if USE_CSUM
  usart_send_char(usart_CRC8(tx_buffer));
#endif
  usart_send_char('\n');
}

void usart_send_version(int ver, int rev, int pat)
{
  memset(&tx_buffer, '\0', sizeof(tx_buffer));
  sprintf(tx_buffer, "$VERS,%d.%d.%d,*", ver, rev, pat);
  usart_send_string(tx_buffer);
#if USE_CSUM
  usart_send_char(usart_CRC8(tx_buffer));
#endif
  usart_send_char('\n');
}