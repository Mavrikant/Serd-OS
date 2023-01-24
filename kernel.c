#include "debug.h"
#include "delay.h"
#include "handler.h"
#include "lib.h"
#include "powercontrol.h"
#include "print.h"
#include "rand.h"
#include "uart.h"
#include "scheduler.h"

void task1_1(void)
{
    uint64_t task_start = get_system_timer_ms();
    printk("%d ms: Task1_1 running...\r\n", task_start);
    wait_msec(rand(0, 55));
}
void task1_2(void)
{
    uint64_t task_start = get_system_timer_ms();
    printk("%d ms: Task1_2 running...\r\n", task_start);
    wait_msec(rand(0, 55));
}
void task1_3(void)
{
    uint64_t task_start = get_system_timer_ms();
    printk("%d ms: Task1_3 running...\r\n", task_start);
    wait_msec(rand(0, 55));
}

void task2_1(void)
{
    uint64_t task_start = get_system_timer_ms();
    printk("%d ms: Task2_1 running...\r\n", task_start);
    wait_msec(rand(0, 55));
}

void task3_1(void)
{
    uint64_t task_start = get_system_timer_ms();
    printk("%d ms: Task3_1 running...\r\n", task_start);
    wait_msec(rand(0, 55));
}
void task3_2(void)
{
    uint64_t task_start = get_system_timer_ms();
    printk("%d ms: Task3_2 running...\r\n", task_start);
    wait_msec(rand(0, 55));
}

void Serd_OS_main()
{
    init_uart();
    init_rand();
    // init_timer();
    // enable_irq();

    // TODO initilaze other peripherals

    printk("\r\n%u ms: ** Initialization complete! **\r\n\r\n", get_system_timer_ms());

    printk("Current Exception Level: %u\r\n", (uint64_t)get_el());
    //int num = 10;
    //printk("Num: %d\r\n", num);
    //printk("Str: %s\r\n", "num");
    //printk("Hex: %x\r\n", num);
    //int num2 = 0;
    //memcpy(&num, &num2, 4);
    //printk("Num: %d\r\n", num);
    //printk("Hex: %x\r\n", num);
    //printk("Str: %s\r\n", "num");
    //printk("Long: %u\r\n", (uint64_t)2147483647L);
    //printk("Rand int: %d\r\n", rand(0, 100));

    ScheduleType schedule = {0};
    schedule.mainTaskCount = 3;
    schedule.taskList[0].mainTaskDuration_Ms = 150;
    schedule.taskList[0].subTaskCount = 3;
    schedule.taskList[0].subTaskList[0].isExecute = TRUE;
    schedule.taskList[0].subTaskList[0].task = &task1_1;
    schedule.taskList[0].subTaskList[1].isExecute = TRUE;
    schedule.taskList[0].subTaskList[1].task = &task1_2;
    schedule.taskList[0].subTaskList[2].isExecute = TRUE;
    schedule.taskList[0].subTaskList[2].task = &task1_3;
    schedule.taskList[1].mainTaskDuration_Ms = 50;
    schedule.taskList[1].subTaskCount = 1;
    schedule.taskList[1].subTaskList[0].isExecute = TRUE;
    schedule.taskList[1].subTaskList[0].task = &task2_1;
    schedule.taskList[2].mainTaskDuration_Ms = 100;
    schedule.taskList[2].subTaskCount = 2;
    schedule.taskList[2].subTaskList[0].isExecute = TRUE;
    schedule.taskList[2].subTaskList[0].task = &task3_1;
    schedule.taskList[2].subTaskList[1].isExecute = TRUE;
    schedule.taskList[2].subTaskList[1].task = &task3_2;

    start_schedular(&schedule);

    // while (1)
    //{
    //     uint64_t frameStart = get_system_time();

    //    uint64_t task1_start = get_system_time();
    //    printk("%d ms: Task1 running...\r\n", task1_start);
    //    wait_msec(rand(0, 800));

    //    printk("%d ms: Task1 took %d ms \r\n", get_system_time(), get_system_time() - task1_start);
    //    if ((frameStart + 500) < get_system_time())
    //    {
    //        printk("%d ms: Deadline miss reboot\r\n", get_system_time());
    //        reboot();
    //    }
    //    while ((frameStart + 500) > get_system_time())
    //    {
    //        asm volatile("nop"); // Wait
    //    }

    //
    //}

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