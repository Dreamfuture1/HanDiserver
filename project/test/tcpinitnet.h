/*
 *初始化TCP网络
 * */
#ifndef     __TCPINITNET_H__
#define     __TCPINITNET_H__


#define IP      struct sockaddr
#define IP4     struct sockaddr_in
void init_tcp_net(int fd);

#endif
