#include "debug.h"
#include "delay.h"
#include "handler.h"
#include "lib.h"
#include "powercontrol.h"
#include "print.h"
#include "rand.h"
#include "uart.h"
#include "lfb.h"

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
    // enable_irq();
    // init_timer();
    // TODO initilaze other peripherals

    printk("\r\n%u ms: ** Initialization complete! **\r\n\r\n", get_system_timer_ms());
    printk("Current Exception Level: %u\r\n", (uint64_t)get_current_el());

    init_lfb();
    lfb_showpicture(); // display a pixmap

    ScheduleType schedule = {0};
    schedule.mainTaskCount = 3;
 
    schedule.taskList[0].mainTaskDuration_Ms = 1500;
    schedule.taskList[0].subTaskCount = 3;
    schedule.taskList[0].subTaskList[0].isExecute = TRUE;
    schedule.taskList[0].subTaskList[0].task = &task1_1;
    schedule.taskList[0].subTaskList[1].isExecute = TRUE;
    schedule.taskList[0].subTaskList[1].task = &task1_2;
    schedule.taskList[0].subTaskList[2].isExecute = TRUE;
    schedule.taskList[0].subTaskList[2].task = &task1_3;
   
 
    schedule.taskList[1].mainTaskDuration_Ms = 500;
    schedule.taskList[1].subTaskCount = 1;
    schedule.taskList[1].subTaskList[0].isExecute = TRUE;
    schedule.taskList[1].subTaskList[0].task = &task2_1;
    
    schedule.taskList[2].mainTaskDuration_Ms = 1000;
    schedule.taskList[2].subTaskCount = 2;
    schedule.taskList[2].subTaskList[0].isExecute = TRUE;
    schedule.taskList[2].subTaskList[0].task = &task3_1;
    schedule.taskList[2].subTaskList[1].isExecute = TRUE;
    schedule.taskList[2].subTaskList[1].task = &task3_2;

    start_schedular(&schedule);
}