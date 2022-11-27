#include "uart.h"
#include "delay.h"
#include "mbox.h"
#include "print.h"
#include "registers.h"
#include "stdint.h"

// TODO This file needs refactoring!

/* PL011 UART registers */
#define UART0_DR ((volatile unsigned int *)(MMIO_BASE + 0x00201000))
#define UART0_FR ((volatile unsigned int *)(MMIO_BASE + 0x00201018))
#define UART0_IBRD ((volatile unsigned int *)(MMIO_BASE + 0x00201024))
#define UART0_FBRD ((volatile unsigned int *)(MMIO_BASE + 0x00201028))
#define UART0_LCRH ((volatile unsigned int *)(MMIO_BASE + 0x0020102C))
#define UART0_CR ((volatile unsigned int *)(MMIO_BASE + 0x00201030))
#define UART0_IMSC ((volatile unsigned int *)(MMIO_BASE + 0x00201038))
#define UART0_ICR ((volatile unsigned int *)(MMIO_BASE + 0x00201044))

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void uart_init()
{
    register unsigned int r;

    /* initialize UART */
    *UART0_CR = 0; // turn off UART0

    /* set up clock for consistent divisor values */
    mbox[0] = 9 * 4;
    mbox[1] = MBOX_REQUEST;
    mbox[2] = MBOX_TAG_SETCLKRATE; // set clock rate
    mbox[3] = 12;
    mbox[4] = 8;
    mbox[5] = 2;       // UART clock
    mbox[6] = 4000000; // 4Mhz
    mbox[7] = 0;       // clear turbo
    mbox[8] = MBOX_TAG_LAST;
    mbox_call(MBOX_CH_PROP);

    /* map UART0 to GPIO pins */
    r = *GPFSEL1;
    r &= ~((7 << 12) | (7 << 15)); // gpio14, gpio15
    r |= (4 << 12) | (4 << 15);    // alt0
    *GPFSEL1 = r;
    *GPPUD = 0; // enable pins 14 and 15
    r = 150;
    while (r--)
    {
        asm volatile("nop");
    }
    *GPPUDCLK0 = (1 << 14) | (1 << 15);
    r = 150;
    while (r--)
    {
        asm volatile("nop");
    }
    *GPPUDCLK0 = 0; // flush GPIO setup

    *UART0_ICR = 0x7FF; // clear interrupts
    *UART0_IBRD = 2;    // 115200 baud
    *UART0_FBRD = 0xB;
    *UART0_LCRH = 0x7 << 4; // 8n1, enable FIFOs
    *UART0_CR = 0x301;      // enable Tx, Rx, UART

    printk("\r\n%u ms: -------------------\r\n", (uint64_t)get_system_timer() / 1000);
    printk("%u ms: UART is initialized!\r\n", (uint64_t)get_system_timer() / 1000);
}

/**
 * Send a character
 */
void uart_writeChar(unsigned int c)
{
    while ((*UART0_FR) & (1 << 5)) // Until Tx is available
    {
        asm volatile("nop"); // Wait
    }
    *UART0_DR = c; // write to buffer
}

/**
 * Receive a character
 */
char uart_readChar()
{
    char r = 0;
    while ((*UART0_FR) & (1 << 4)) // Until Rx is available
    {
        asm volatile("nop"); // Wait
    }
    r = (char)(*UART0_DR);       // read from register
    return r == '\r' ? '\n' : r; // convert carrige return to newline
}

/**
 * Display a string
 */
void uart_writeArray(const char *s)
{
    while (*s)
    {
        /* convert newline to carrige return + newline */
        if (*s == '\n')
            uart_writeChar('\r');
        uart_writeChar(*s++);
    }
}

/**
 * Display a binary value in hexadecimal
 */
void uart_writeHex(uint32_t d)
{
    uart_writeArray("0x");
    for (int32_t c = 28; c >= 0; c -= 4)
    {
        // get highest tetrad
        uint32_t n = (d >> c) & 0xF;
        // 0-9 => '0'-'9', 10-15 => 'A'-'F'
        n += n > 9 ? 0x37 : 0x30;
        uart_writeChar(n);
    }
}
