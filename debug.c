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

uint32_t get_current_el()
{
    uint64_t el = 0;
    // read the current level from system register
    asm volatile("mrs %0, CurrentEL" : "=r"(el));
    return (el >> 2) & 0b11;
}