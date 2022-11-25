
#ifndef UART_H
#define UART_H

void uart_init();
void uart_writeChar(unsigned int c);
char uart_readChar();
void uart_writeArray(const char *s);
void uart_writeHex(unsigned int d);

#endif // UART_H