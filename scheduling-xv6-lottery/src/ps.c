#include "types.h"
#include "param.h"
#include "pstat.h"
#include "user.h"


void
ps(struct pstat* pst)
{
    getpinfo(pst);
    printf(1, "%s\t%s\t%s\n", "PID", "TICKETS", "TICKS");
    for (int i = 0; i < NPROC; i++)
    {
        if (pst->inuse[i])
        {
            printf(1, "%d\t%d\t%d\n", pst->pid[i], pst->tickets[i], pst->ticks[i]);
        }
    }
}

int
main(int argc, char *argv[])
{
    struct pstat pst;
    ps(&pst);
    exit();
}
