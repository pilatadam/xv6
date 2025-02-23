#include "kernel/types.h"
#include "user.h"

void closepipe();

int
main(int agc, char* argv[])
{
    // Parent -> Child
    int p1[2];
    if (pipe(p1) < 0) {
        fprintf(2, "Error: pipe() failed.\n");
        exit(1);
    }

    // Child -> Parent
    int p2[2];
    if (pipe(p2) < 0) {
        fprintf(2, "Error: pipe() failed.\n");
        closepipe(p1);
        exit(1);
    }

    char byte[1];
    if (fork() == 0) {
        close(p1[1]);
        close(p2[0]);

        // Read
        if (read(p1[0], byte, 1) != 1) {
            fprintf(2, "Error: child read failed.\n");
            close(p1[0]);
            close(p2[1]);
            exit(1);
        }

        fprintf(0, "%d: received ping\n", getpid());
        close(p1[0]);

        write(p2[1], "A", 1);
        close(p2[1]); // Signalize EOF
        exit(0);
    
    }
    else {
        close(p1[0]);
        close(p2[1]);

        // Write and wait
        write(p1[1], "A", 1);
        close(p1[1]); // Signalize EOF
        wait(0);

        // Read
        if (read(p2[0], byte, 1) != 1) {
            fprintf(2, "Error: parent read failed.\n");
            close(p2[0]);
            exit(1);
        }

        fprintf(0, "%d: received pong\n", getpid());
        close(p2[0]);
        exit(0);
    }
}

void
closepipe(int p[2]) {
    close(p[0]);
    close(p[1]);
}