#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include "datatypes.h"

typedef void (*TASK) (void);

#define MAIN_TASK_COUNT_LIMIT         10U
#define SUB_TASK_COUNT_LIMIT          10U

typedef struct SubTaskType
{
    BOOL isExecute;
    TASK task;
} SubTaskType;

typedef struct MainTaskType
{
    uint64_t mainTaskDuration_Ms;
    uint32_t subTaskCount;
    SubTaskType subTaskList[SUB_TASK_COUNT_LIMIT];
} MainTaskType;

typedef struct ScheduleType
{
    uint32_t mainTaskCount;
    MainTaskType taskList[MAIN_TASK_COUNT_LIMIT];
} ScheduleType;

void start_schedular(const ScheduleType * schedule);

#endif // _SCHEDULER_H