#include "kernel/types.h"
#include "user.h"

void usage(void);

int
main(int argc, char* argv[])
{
    if (argc != 2){
        fprintf(2, "Error: ");
        usage();
        exit(1);
    }

    sleep(atoi(argv[1]));
    exit(0);
}

void
usage(void)
{
    fprintf(2, "sleep [time]\n");
}