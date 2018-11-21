#include "types.h"
#include "user.h"
#include "counts.h"

int main(int argc, char *argv[])
{
    struct countsTable *table = malloc(sizeof(struct countsTable));
    counts(table);

    printf(1, "----------------\n");
    printf(1, "|  Fork :   %d  |\n", table->counts[0]);
    printf(1, "|  Exit :   %d  |\n", table->counts[1]);
    printf(1, "|  Wait :   %d  |\n", table->counts[2]);
    printf(1, "|  Pipe :   %d  |\n", table->counts[3]);
    printf(1, "|  Read :   %d  |\n", table->counts[4]);
    printf(1, "|  Kill :   %d  |\n", table->counts[5]);
    printf(1, "|  Exec :   %d  |\n", table->counts[6]);
    printf(1, "|  Fstat :  %d  |\n", table->counts[7]);
    printf(1, "|  Chdir :  %d  |\n", table->counts[8]);
    printf(1, "|  Dup :    %d  |\n", table->counts[9]);
    printf(1, "|  Getpid : %d  |\n", table->counts[10]);
    printf(1, "|  Sbrk :   %d  |\n", table->counts[11]);
    printf(1, "|  Sleep :  %d  |\n", table->counts[12]);
    printf(1, "|  Uptime : %d  |\n", table->counts[13]);
    printf(1, "|  Open :   %d  |\n", table->counts[14]);
    printf(1, "|  Write :  %d  |\n", table->counts[15]);
    printf(1, "|  Mknod :  %d  |\n", table->counts[16]);
    printf(1, "|  Unlink : %d  |\n", table->counts[17]);
    printf(1, "|  Link :   %d  |\n", table->counts[18]);
    printf(1, "|  Mkdir :  %d  |\n", table->counts[19]);
    printf(1, "|  Close :  %d  |\n", table->counts[20]);
    printf(1, "|  Counts : %d  |\n", table->counts[21]);
    printf(1, "----------------\n");
    exit();
}
