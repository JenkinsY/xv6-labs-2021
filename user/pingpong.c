#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, const char * argv[])
{
    int pipep[2], pipec[2];
    pipe(pipep);
    pipe(pipec);

    int fd = fork();
    if (fd != 0) {
        write(pipec[1], "!", 1);
        char buf;
        read(pipep[0], &buf, 1);
        printf("%d: received pong\n", getpid());
        wait(0);
    }
    else {
        char buf;
        read(pipec[0], &buf, 1);
        printf("%d: received ping\n", getpid());
        write(pipep[1], &buf, 1);
    }
    exit(0);
}
