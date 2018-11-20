#include "counts.h"

struct countsTable counts_table;

int increament(int index)
{
    counts_table.counts[index]++;
    return 0;
}

int getCounts(struct countsTable *table)
{
    for (int i = 0; i < 22; i++)
    {
       table->counts[i] = counts_table.counts[i];
    }
    return 0;
}