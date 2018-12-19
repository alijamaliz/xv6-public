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
    long temp = 0;
    for (int k = 0; k < 1000000; k++)
    {
        for (int i = 0; i < 1000000; i++)
        {
            for (int j = 0; j < 1000000; j++)
            {
                temp = temp + (i * j);
                temp = temp + (i * j);
            }
            temp = 0;
        }
    }
}

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
                printf(stdout, "IO %d: start: %d, finish: %d, response time: %d\n", pid, timesContainer->start_time, timesContainer->finish_time, timesContainer->response_time);
                exit();
            }
            else
            {
                int pid = getpid();
                cpuIntensiveTask();
                struct timesContainer *timesContainer = malloc(sizeof(struct timesContainer));
                times(pid, timesContainer);
                printf(stdout, "CPU %d: start: %d, finish: %d, response time: %d\n", pid, timesContainer->start_time, timesContainer->finish_time, timesContainer->response_time);
                exit();
            }
        }
    }
    for (int i = 0; i < NUM_OF_PROCESSES; i++)
    {
        wait();
    }
    exit();
}
