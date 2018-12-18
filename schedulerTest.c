#include "types.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "times.h"

#define NUM_OF_PROCESSES 50

int stdout = 1;
char buf[8192];

void writetest(void)
{
    int fd;
    int i;

    // printf(stdout, "small file test\n");
    fd = open("small", O_CREATE | O_RDWR);
    if (fd >= 0)
    {
        // printf(stdout, "creat small succeeded; ok\n");
    }
    else
    {
        // printf(stdout, "error: creat small failed!\n");
        exit();
    }
    for (i = 0; i < 100; i++)
    {
        if (write(fd, "aaaaaaaaaa", 10) != 10)
        {
            // printf(stdout, "error: write aa %d new file failed\n", i);
            exit();
        }
        if (write(fd, "bbbbbbbbbb", 10) != 10)
        {
            // printf(stdout, "error: write bb %d new file failed\n", i);
            exit();
        }
    }
    // printf(stdout, "writes ok\n");
    close(fd);
    fd = open("small", O_RDONLY);
    if (fd >= 0)
    {
        // printf(stdout, "open small succeeded ok\n");
    }
    else
    {
        // printf(stdout, "error: open small failed!\n");
        exit();
    }
    i = read(fd, buf, 2000);
    if (i == 2000)
    {
        // printf(stdout, "read succeeded ok\n");
    }
    else
    {
        // printf(stdout, "read failed\n");
        exit();
    }
    close(fd);

    if (unlink("small") < 0)
    {
        // printf(stdout, "unlink small failed\n");
        exit();
    }
    // printf(stdout, "small file test ok\n");
}

void cpuIntensiveTask()
{
    int k = 0;
    for (int i = 0; i < 10000; i++)
    {
        for (int j = 0; j < 10000; j++)
        {
            k = k + (i * j);
        }
    }
}

int sum_of_turnaround_times = 0;
int sum_of_runtimes = 0;

int main(int argc, char *argv[])
{
    for (int i = 0; i < NUM_OF_PROCESSES; i++)
    {
        int proc = fork();
        if (proc < 0)
        {
            printf(stdout, "fork error");
            exit();
        }
        if (proc == 0)
        {
            if (i % 2 == 0)
            {
                int pid = getpid();
                writetest();
                struct timesContainer *timesContainer = malloc(sizeof(struct timesContainer));
                times(pid, timesContainer);
                sum_of_turnaround_times += (timesContainer->finish_time - timesContainer->start_time);
                sum_of_runtimes += timesContainer->run_time;
                printf(stdout, "IO %d: start: %d, finish: %d, run: %d, res: %d\n", pid, timesContainer->start_time, timesContainer->finish_time, timesContainer->run_time, timesContainer->response_time);
                exit();
            }
            else
            {
                int pid = getpid();
                cpuIntensiveTask();
                struct timesContainer *timesContainer = malloc(sizeof(struct timesContainer));
                times(pid, timesContainer);
                sum_of_turnaround_times += (timesContainer->finish_time - timesContainer->start_time);
                sum_of_runtimes += timesContainer->run_time;
                printf(stdout, "CPU %d: start: %d, finish: %d, run: %d, res: %d\n", pid, timesContainer->start_time, timesContainer->finish_time, timesContainer->run_time, timesContainer->response_time);
                exit();
            }
        }
    }
    for (int i = 0; i < NUM_OF_PROCESSES; i++)
    {
        wait();
    }
    printf(stdout, "turn: %d, run: %d\n", sum_of_turnaround_times, sum_of_runtimes);
    printf(stdout, "Number of jobs: %d\n", NUM_OF_PROCESSES);
    printf(stdout, "Tournaround time average: %d\n", sum_of_turnaround_times / NUM_OF_PROCESSES);
    printf(stdout, "Runtime time average: %d\n", sum_of_runtimes / NUM_OF_PROCESSES);
    exit();
}
