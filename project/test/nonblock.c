
/*
 *将sockfd设为未阻塞
 *
 * */
#include "nonblock.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
void nonblock(int fd){
    int old_flag = fcntl(fd,F_GETFL);
    if(old_flag < 0){
        perror("old fcntl");
        return;
    }
    int new_flag = old_flag | O_NONBLOCK;
    if(fcntl(fd,F_SETFL,new_flag) < 0){
        perror("new fcntl");
        return;
    }
}

