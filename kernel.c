#include "lib.h"
#include "print.h"
#include "uart.h"

void Serd_OS_main()
{
    uart_init();
    uart_writeArray("UART is initialized!\r\n");

    // TODO initilaze other peripherals

    uart_writeArray("Initialization complete!\r\n");

    int num = 10;
    printk("Num= %d\r\n", num);
    printk("Hex= %x\r\n", num);
    printk("Str= %s\r\n", "num");

    int num2 = 0;
    memcpy(&num, &num2, 4);

    printk("Num= %d\r\n", num);
    printk("Hex= %x\r\n", num);
    printk("Str= %s\r\n", "num");

    ASSERT(1);

    while (1)
    {
        char c = uart_readChar();
        uart_writeChar(c);
        if (c == 'A')
        {
            uart_writeArray("\r\nA is pressed\r\n");
            ASSERT(0);
        }
    }
}