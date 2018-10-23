/*
 *设置epoll多路复用
 *
 * */
#include "setepoll.h"
#include "nonblock.h"
#include "tcpinitnet.h"
#include "list.h"


#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

extern linklist list;
extern char recvbuf[128];

void setepoll(int sockfd,int epollfd){
    struct epoll_event ev;
    ev.data.fd = sockfd;
    ev.events = EPOLLIN | EPOLLET;
    if(epoll_ctl(epollfd,EPOLL_CTL_ADD,sockfd,&ev) == -1){
        perror("epoll_ctl");
        close(sockfd);
        exit(0);
    }
    nonblock(sockfd);
}

//处理进入的连接
int deal_with_link(int sockfd,int epollfd,int return_epoll,struct epoll_event* events){
    int i = 0;
    for(i = 0;i < return_epoll;i++){
        int listenfd = events[i].data.fd;
        if(listenfd == sockfd){
            //接受客户的IP信息
            IP4 client;
            char p_ip[64];
            socklen_t client_size = sizeof(client);
            printf("one coming\n");
            int connfd = accept(sockfd,(IP*)&client,&client_size);
            if(connfd < 0){
                perror("accept");
                break;
            }
            else{
                printf("%s\n",inet_ntop(AF_INET,&(client.sin_addr),p_ip,64));
                setepoll(connfd,epollfd);
                insert_netnode(&list,connfd);
                printf("save successful\n");
            }
        }
        else if(events[i].events & EPOLLIN){
            printf("event once\n");
            while(1){
                memset(recvbuf,0,128);
                int rect = read(listenfd,recvbuf,128); 
                if(rect == 0){
                    printf("empty...\n");
                    close(listenfd);
                } 
                else if(rect < 0){
                    if(errno == EAGAIN || errno == EWOULDBLOCK){
                        printf("read later\n");
                        break;
                    }
                    perror("read");
                    close(listenfd);    
                    break;
                }
                //printf("%s\n",recvbuf);
            }
        }
    }

}
