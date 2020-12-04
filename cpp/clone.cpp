#include <sched.h>
#include <signal.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

static int child_func(void * arg)
{
    char * buf = (char *)arg;
    printf("Child sees buf = \"%s\"\n", buf);
    strcpy(buf, "hello from child");
    return 0;
}

int main(int argc, char * argv[])
{
    const int STACKSIZE = 65536;
    char * stack = (char *)malloc(STACKSIZE);
    if (! stack)
    {
        perror("malloc");
        exit(1);
    }

    unsigned long flags = 0;
    if (argc > 1 && ! strcmp(argv[1], "tm"))
    {
        flags |= CLONE_VM;
    }

    char buf[100];
    strcpy(buf, "hello from parent");
    if (clone(child_func, stack + STACKSIZE, flags | SIGCHILD, buf) == -1)
    {
        perror("clone");
        exit(1);
    }

    int status;
    if (wait(&status) == -1)
    {
        perror("wait");
        exit(1);
    }

    printf("Child exited with status: %d, buf=\"%s\"\n", status, buf);
    return 0;
}
