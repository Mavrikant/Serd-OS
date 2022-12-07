#include "debug.h"
#include "delay.h"
#include "handler.h"
#include "lib.h"
#include "print.h"
#include "rand.h"
#include "uart.h"

uint64_t get_system_time() { return (uint64_t)get_system_timer() / 1000; }

void Serd_OS_main()
{
    uart_init();
    rand_init();
    // init_timer();
    // enable_irq();

    // TODO initilaze other peripherals

    printk("\r\n%u ms: ** Initialization complete! **\r\n\r\n", (uint64_t)get_system_timer() / 1000);

    printk("Current Exception Level: %u\r\n", (uint64_t)get_el());
    /*int num = 10;
    printk("Num: %d\r\n", num);
    printk("Str: %s\r\n", "num");
    printk("Hex: %x\r\n", num);

    int num2 = 0;
    memcpy(&num, &num2, 4);

    printk("Num: %d\r\n", num);
    printk("Hex: %x\r\n", num);
    printk("Str: %s\r\n", "num");
    printk("Long: %u\r\n", (uint64_t)2147483647L);
    printk("Rand int: %d\r\n", rand(0, 100));
*/
    printk("%d ms: Starting Schedular\r\n", get_system_time());

    while (1)
    {
        uint64_t frameStart = get_system_time();

        uint64_t task1_start = get_system_time();
        printk("%d ms: Task1 running...\r\n", task1_start);
        wait_msec(rand(0, 600));

        printk("%d ms: Task1 took %d ms \r\n", get_system_time(), get_system_time() - task1_start);
        if ((frameStart + 500) < get_system_time())
        {
            printk("%d ms: Deadline miss reboot\r\n", get_system_time());
        }
        while ((frameStart + 500) > get_system_time())
        {
            asm volatile("nop"); // Wait
        }

        uint64_t task2_start = get_system_time();

        printk("%d ms: Task2 running...\r\n", task2_start);
        wait_msec(rand(0, 200));

        printk("%d ms: Task2 took %d ms \r\n", get_system_time(), get_system_time() - task2_start);
        if ((frameStart + 1000) < get_system_time())
        {
            printk("%d ms: Deadline miss reboot\r\n", get_system_time());
        }
        while ((frameStart + 1000) > get_system_time())
        {
            asm volatile("nop"); // Wait
        }
    }

    /*
    while (1)
    {
        char c = uart_readChar();
        uart_writeChar(c);
        if (c == 'A')
        {
            printk("\r\nA is pressed\r\n");
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
    */
}