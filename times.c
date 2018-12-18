#include "times.h"

struct timesTable times_table;

int setStartTime(int proc_id, uint time)
{
    times_table.start_times[proc_id] = time;
    return 0;
}

int setFinishTime(int proc_id, uint time)
{
    times_table.finish_times[proc_id] = time;
    return 0;
}

int getTimesOfSpecificProcess(int proc_id, struct timesContainer *timesContainer)
{
    timesContainer->start_time = times_table.start_times[proc_id];
    timesContainer->finish_time = times_table.finish_times[proc_id];
    timesContainer->response_time = times_table.response_times[proc_id] / times_table.number_of_schedulings[proc_id];
    return 0;
}

int increamentResponseTime(int proc_id, uint increament)
{
    times_table.number_of_schedulings[proc_id]++;
    times_table.response_times[proc_id] += increament;
    return 0;
}