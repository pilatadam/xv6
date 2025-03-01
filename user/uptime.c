#include "kernel/types.h"
#include "user.h"

int
main(int argc, char* argv[])
{
    uint64 up;
    up = uptime();
    printf("UPTIME: %ld\n", up);
    exit(0);
}