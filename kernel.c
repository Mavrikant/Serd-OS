#include "debug.h"
#include "delay.h"
#include "lib.h"
#include "print.h"
#include "rand.h"
#include "uart.h"

void Serd_OS_main()
{
    uart_init();
    rand_init();

    // TODO initilaze other peripherals

    printk("\r\n%u ms: ** Initialization complete! **\r\n\r\n", (uint64_t)get_system_timer() / 1000);

    printk("Current Exception Level: %u\r\n", (uint64_t)get_el());
    int num = 10;
    printk("Num: %d\r\n", num);
    printk("Str: %s\r\n", "num");
    // printk("Hex: %x\r\n", num);

    int num2 = 0;
    memcpy(&num, &num2, 4);

    printk("Num: %d\r\n", num);
    // printk("Hex: %x\r\n", num);
    printk("Str: %s\r\n", "num");
    printk("Long: %u\r\n", (uint64_t)2147483647L);
    printk("Rand int: %d\r\n", rand(0, 100));

    while (1)
    {
        char c = uart_readChar();
        uart_writeChar(c);
        if (c == 'A')
        {
            uart_writeArray("\r\nA is pressed\r\n");
        }
        else if (c == 'R')
        {
            printk("\r\nRand int: %d\r\n", rand(0, 100));
        }
        else if (c == 'E') // Exception
        {
            char *p = (char *)0xffff000000000000;
            *p = 1;

            printk("\r\nReturn from exception\r\n");
        }
    }
}