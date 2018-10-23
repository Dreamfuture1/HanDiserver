/*
 *初始化TCP网络
 * */
#include "tcpinitnet.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>


#define IP      struct sockaddr
#define IP4     struct sockaddr_in
void init_tcp_net(int fd){
    //初始化本地网络信息
    IP4 server;
    server.sin_family = AF_INET;
    server.sin_port = htons(6666);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    //设置端口复用
    int optval = 1;//端口复用选项的值
    if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval))){
        perror("setsockopt");
        exit(0);
    }
    //绑定本地网络信息到fd上
    if(bind(fd,(IP*)&server,sizeof(server)) == -1){
        perror("bind");
        exit(0);
    }
    if(listen(fd,128)){
        perror("listen");
        exit(0);
    }

}   

