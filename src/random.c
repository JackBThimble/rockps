#include "random.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int urandom_fd = -2;

void
urandom_init(void)
{
        urandom_fd = open("/dev/urandom", O_RDONLY);

        if (urandom_fd == -1) {
                int errsv = urandom_fd;
                printf("Error opening [/dev/urandom]: %i\n", errsv);
                exit(1);
        }
}

unsigned long
urandom(void)
{
        unsigned long  buf_impl;
        unsigned long *buf = &buf_impl;

        if (urandom_fd == -2) {
                urandom_init();
        }

        read(urandom_fd, buf, sizeof(long));
        return buf_impl;
}
