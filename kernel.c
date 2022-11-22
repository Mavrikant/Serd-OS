#include "uart.h"
#include "print.h"
void Serd_OS_main()
{
    uart_init();
    uart_writeArray("UART is initialized!\n");

    // TODO initilaze other peripherals

    uart_writeArray("Initialization complete!\n");

    int num = 10;
    printk("Num= %d\n",num);
    printk("Hex= %x\n",num);
    printk("Str= %s\n","num");

    while (1)
    {
        char c = uart_readChar();
        uart_writeChar(c);
        if (c == 'A')
        {
            uart_writeArray("\nA pressed\n");
        }
    }
}