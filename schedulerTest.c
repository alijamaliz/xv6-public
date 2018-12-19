#include "types.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "times.h"

#define NUM_OF_PROCESSES 50

int stdout = 1;
char buf[8192];

void bigwrite(void)
{
    int fd, sz;

    // printf(1, "bigwrite test\n");

    unlink("bigwrite");
    for (sz = 499; sz < 12 * 512; sz += 471)
    {
        fd = open("bigwrite", O_CREATE | O_RDWR);
        if (fd < 0)
        {
            // printf(1, "cannot create bigwrite\n");
            exit();
        }
        int i;
        for (i = 0; i < 2; i++)
        {
            int cc = write(fd, buf, sz);
            if (cc != sz)
            {
                // printf(1, "write(%d) ret %d\n", sz, cc);
                exit();
            }
        }
        close(fd);
        unlink("bigwrite");
    }

    // printf(1, "bigwrite ok\n");
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
                bigwrite();
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
