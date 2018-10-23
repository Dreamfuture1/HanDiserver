#ifndef __LINK_H__
#define __LINK_H__
#include "struct.h"

//初始化链表
void init_list(linklist* list);

//向链表添加netnode
void insert_netnode(linklist* list,int fd);

//开始遍历链表
void begin_list(linklist* list);

    //获取链表中netnode的数据
int get_list(linklist* list,int* fd,time_t* ltime);

#endif
