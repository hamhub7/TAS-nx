#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <errno.h>

#include <switch.h>
#include "udp_input.h"

int poll_udp_input(struct input_msg *buf)
{
    svcSleepThread(1e+9L/60);

    return 0;
}