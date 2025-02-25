#include "kernel/types.h"
#include "user.h"

#define LENGTH 280

/*
*   Make a new process and share
*   reading end of the pipe for 
*   the parent process
*/
void neighbour(int ppipe) __attribute__((noreturn));

void init(void);

int
main(int argc, char* argv[])
{
    
    init();
    exit(0);
}

void
neighbour(int ppipe)
{

    int p[2];
    pipe(p);

    int start;
    int received;

    int created = 0;
    int pid;

    read(ppipe, &start, sizeof(int));
    printf("prime %d\n", start);

    while (read(ppipe, &received, sizeof(int)) > 0)
    {
        if (received % start != 0) {
            write(p[1], &received, sizeof(int));
            if (!created)
            {
                created = 1;
                pid = fork();
                if (pid == 0)
                {
                    close(ppipe);
                    close(p[1]);
                    neighbour(p[0]);
                }
            }
        }
    }

    close(ppipe);
    close(p[1]);
    if (created) { wait(0); }
    exit(0);
}

void init(void)
{
    int p[2];
    pipe(p);

    int pid = fork();

    if (pid == 0) {
        close(p[1]);
        neighbour(p[0]);
    }
    else {
        close(p[0]);

        int current = 2;
        while (current <= LENGTH) {
            write(p[1], &current, sizeof(int));
            current++;
        }

        close(p[1]);
        wait(0);
        exit(0);
    }
}
