#include "kernel/types.h"
#include "user.h"

#define LENGTH 280

/*
*   Make a new process and share
*   reading end of the pipe for 
*   the parent process
*
*   @param ppipe Read end of the pipe through
*   which parent reads numbers
*/
void
pipeparse(int ppipe) __attribute__((noreturn));

/*
*   Inicialize the first pipeline through
*   which parent process writes LENGTH numbers
*
*   @return Read end of the pipe
*/
int
pipeinit(void);

int
main(int argc, char* argv[])
{
    int ppipe = pipeinit();
    pipeparse(ppipe);
    exit(0);
}

void
pipeparse(int ppipe)
{
    int p[2];
    if (pipe(p) == -1) {
        printf("Error: pipeparse pipe() failed\n");
        exit(1);
    }

    int start;
    int received;

    int forked = 0;
    int pid;

    read(ppipe, &start, sizeof(int));
    printf("prime %d\n", start);

    while (read(ppipe, &received, sizeof(int)) > 0)
    {
        if (received % start != 0) {
            write(p[1], &received, sizeof(int));
            if (!forked)
            {
                forked = 1;
                pid = fork();

                if (pid == -1) {
                    printf("Error: pipeparse fork() failed\n");
                    close(ppipe);
                    close(p[1]);
                    exit(1);
                }
                if (pid == 0)
                {
                    close(ppipe);
                    close(p[1]);
                    pipeparse(p[0]);
                }
                else { close(p[0]); }
            }
        }
    }

    close(ppipe);
    close(p[1]);
    if (forked) { wait(0); }
    exit(0);
}

int 
pipeinit(void)
{
    int p[2];
    pipe(p);

    int pid = fork();

    if (pid == -1) {
        printf("Error: pipeinit fork() failed\n");
        close(p[0]);
        close(p[1]);
        exit(1);
    }

    if (pid == 0) {
        close(p[1]);
        return p[0];
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
