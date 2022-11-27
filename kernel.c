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

    printk("\r\n%u ms: ** Initialization complete! **\r\n", (uint64_t)get_system_timer() / 1000);

    int num = 10;
    printk("Num= %d\r\n", num);
    printk("Str= %s\r\n", "num");
    printk("Hex= %x\r\n", num);

    int num2 = 0;
    memcpy(&num, &num2, 4);

    printk("Num= %d\r\n", num);
    printk("Hex= %x\r\n", num);
    printk("Str= %s\r\n", "num");

    ASSERT(1);

    printk("We are at EL %u\r\n", (uint64_t)get_el());

    /*
    while (1)
    {
        wait_msec(1000);
        uart_writeArray("Rand int: ");
        uart_writeHex(rand(0, 100));
        uart_writeArray("\n");
    }
    */

    while (1)
    {
        char c = uart_readChar();
        uart_writeChar(c);
        if (c == 'A')
        {
            uart_writeArray("\r\nA is pressed\r\n");
            char *p = (char *)0xffff000000000000;
            *p = 1;
        }
    }
}