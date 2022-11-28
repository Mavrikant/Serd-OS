
#ifndef UART_H
#define UART_H
#include "stdint.h"

void uart_init();
void uart_writeChar(unsigned int c);
char uart_readChar();
void uart_writeArray(const char *s);
void uart_writeHex(uint64_t d);

#endif // UART_H