//
// Spawns 3 dummy processes with different ticket quantities
//

#include "types.h"
#include "stat.h"
#include "user.h"


int main(void)
{
    int rc, tickets;
    settickets(100);  // give the parent priority while forking dummy tasks

    for (int i = 0; i < 3; i++)
    {
        rc = fork();
        tickets = (i + 1) * 10;
        if (rc == 0)
        {
            settickets(tickets);
            for(;;);
        }
        else
        {
            printf(1, "Spawned pid #%d with %d tickets\n", rc, tickets);
        }
    }

    exit();
}
