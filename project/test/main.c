
#include "list.h"
#include "setepoll.h"
#include "tcpinitnet.h"
#include "setepoll.h"

#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>

//初始化全局的链表
linklist list = {0};
//全局变量read
char recvbuf[128] = {0};

int main(){
    //初始化链表
    init_list(&list);
    //变量声明
    int sockfd,epollfd,return_epoll;
    int datafd;
    time_t ltime;
    struct epoll_event events[100];
    //tcp通讯套接字和epollfd检测句柄
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    epollfd = epoll_create(10000);
    //初始化TCP网络
    init_tcp_net(sockfd);
    //设置epoll多路复用
    setepoll(sockfd,epollfd);
    //遍历链表前对链表的设置
    begin_list(&list);
    while(1){
        return_epoll = epoll_wait(epollfd,events,100,500);
        if(return_epoll == 0){
            //printf("out time...\n");
            continue;
        }
        if(return_epoll < 0){
            perror("epoll_wait");
            break;
        }
        if(return_epoll > 0){
            deal_with_link(sockfd,epollfd,return_epoll,events);
        }
        if(!get_list(&list,&datafd,&ltime)){
            printf("datafd:%d  ltime:%ld\n",datafd,ltime);
        }
    }
    close(sockfd);
    return 0;
}
