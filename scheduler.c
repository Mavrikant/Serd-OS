#include "scheduler.h"
#include "datatypes.h"
#include "debug.h"
#include "delay.h"
#include "powercontrol.h"
#include "print.h"
#include "rand.h"

static void check_schedule(const ScheduleType *schedule)
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

void start_schedular(const ScheduleType *schedule)
{
    check_schedule(schedule);
    printk("%d ms: Starting Schedular\r\n\r\n", get_system_timer_ms());

    while (1)
    {
        for (uint32_t i = 0; i < schedule->mainTaskCount; i++)
        {
            uint64_t startTime = get_system_timer_ms();
            MainTaskType mainTask = schedule->taskList[i];
            for (uint32_t j = 0; j < mainTask.subTaskCount; j++)
            {
                SubTaskType subTask = mainTask.subTaskList[j];
                if (subTask.isExecute == TRUE)
                {
                    subTask.task();
                }
            }

            printk("%d ms: Main Task took %d ms.\r\n\r\n", get_system_timer_ms(), (get_system_timer_ms() - startTime));
            if ((startTime + mainTask.mainTaskDuration_Ms) < get_system_timer_ms())
            {
                printk("%d ms: Deadline miss reboot\r\n", get_system_timer_ms());
                reboot();
            }
            while ((startTime + mainTask.mainTaskDuration_Ms) > get_system_timer_ms())
            {
                asm volatile("nop"); // Wait
            }
        }
    }
}