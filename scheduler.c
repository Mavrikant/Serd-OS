#include "rand.h"
#include "delay.h"
#include "print.h"
#include "powercontrol.h"
#include "debug.h"
#include "scheduler.h"
#include "datatypes.h"

static void check_schedule(const ScheduleType * schedule)
{
    printk("%d ms: Checking Schedular\r\n", get_system_timer_ms());

    ASSERT(schedule != NULL);

    for (uint32_t i = 0; i < schedule->mainTaskCount; i++)
    {
        for (uint32_t j = 0; j < schedule->taskList[i].subTaskCount; j++)
        {
            ASSERT(schedule->taskList[i].subTaskList[j].task != NULL);
        }
    }
}

void start_schedular(const ScheduleType * schedule)
{
    check_schedule(schedule);
    printk("%d ms: Starting Schedular\r\n\r\n", get_system_timer_ms());

    while (1){
        for (uint32_t i = 0; i < schedule->mainTaskCount; i++)
        {
            uint64_t startTime = get_system_timer_ms();
            
            for (uint32_t j = 0; j < schedule->taskList[i].subTaskCount; j++)
            {
                if(schedule->taskList[i].subTaskList[j].isExecute == TRUE)
                {
                    schedule->taskList[i].subTaskList[j].task();    
                }
            }

            printk("%d ms: Main Task took %d ms.\r\n\r\n", get_system_timer_ms(), (get_system_timer_ms() - startTime));
            if ((startTime + schedule->taskList[i].mainTaskDuration_Ms) < get_system_timer_ms())
            {
                printk("%d ms: Deadline miss reboot\r\n", get_system_timer_ms());
                reboot();
            }
            while ((startTime + schedule->taskList[i].mainTaskDuration_Ms) > get_system_timer_ms())
            {
                asm volatile("nop"); // Wait
            }
        }
    }
}