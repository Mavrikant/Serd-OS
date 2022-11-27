#include "print.h"
#include "stdint.h"
#include "uart.h"

void handler(uint64_t numid, uint64_t esr, uint64_t elr)
{
    switch (numid)
    {
    case 1:
        uart_writeArray("sync error at: ");
        uart_writeArray("\r\nesr:");
        uart_writeHex(esr);
        uart_writeArray("\r\nelr:");
        uart_writeHex(elr);
        while (1)
        {
            asm volatile("nop"); // Wait
        }
        break;

    default:
        uart_writeArray("unknown exception\r\n");
        while (1)
        {
            asm volatile("nop"); // Wait
        }
        break;
    }
}