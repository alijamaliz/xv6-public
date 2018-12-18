#include "types.h"

#define TIMES_TABLE_SIZE 100

struct timesTable
{
    uint start_times[100];
    uint finish_times[100];
    uint run_times[100];
    uint response_times[100];
};

struct timesContainer
{
    uint start_time;
    uint finish_time;
    uint run_time;
    uint response_time;
};

int setStartTime(int proc_id, uint time);
int setFinishTime(int proc_id, uint time);
int increamentRunTime(int proc_id, uint increament);
int increamentResponseTime(int proc_id, uint increament);
int getTimesOfSpecificProcess(int proc_id, struct timesContainer *timesContainer);