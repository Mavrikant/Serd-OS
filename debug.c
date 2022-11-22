#include "debug.h"
#include "print.h"

void error_check(char *file, uint64_t line)
{
    printk("\r\n-----------------------------------");
    printk("\r\n             ERROR CHECK           ");
    printk("\r\n-----------------------------------");
    printk("\r\nAssertion Failed [%s: %u]", file, line);
    printk("\r\nKERNEL STOPPED!\r\n");

    while (1) 
    { 
        asm volatile("nop"); // Wait
    }
}