/*
 *设置epoll多路复用
 *
 * */

#ifndef     __SEREPOLL_H__
#define     __SEREPOLL_H__
#include <sys/epoll.h>

//设置多路复用
void setepoll(int sockfd,int epollfd);
//将连接存入缓存
int deal_with_link(int sockfd,int epollfd,int return_epoll,struct epoll_event* events);
#endif
