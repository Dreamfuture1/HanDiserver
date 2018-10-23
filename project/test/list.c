#include "list.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
/*
 *每次wechat端发起与服务器的连接的时候,服务器同时也与一台充电桩发起了连接
 *根据连接的时间差来判断是否超时来断开连接
 * 
 *
 *
 * */
//初始化链表
void init_list(linklist* list){
    list->head.p_prev = NULL;
    list->head.p_next = &(list->tail);
    list->tail.p_prev = &(list->head);
    list->tail.p_next = NULL;
    list->p_cur = NULL;
}

//向链表添加netnode
void insert_netnode(linklist* list,int fd){
    //接收分配的netnode动态内存
    netnode* p_node = NULL,*p_first = NULL,*p_mid = NULL,*p_last = NULL;
    p_node = (netnode*)malloc(sizeof(netnode));
    if(!p_node){
        return;
    }
    //netnode节点赋值
    p_node->web_fd = fd;
    p_node->linktime = time(NULL);
    p_node->p_prev = NULL;
    p_node->p_next = NULL;
    p_node->p_cmdnode = NULL;
    //顺序在链表中插入netnode节点
    p_first = list->tail.p_prev;
    p_mid = p_first->p_next;
    p_last = p_mid->p_next;
    p_first->p_next = p_node;
    p_node->p_prev = p_first;
    p_node->p_next = p_mid;
    p_mid->p_prev = p_node;
}

//开始遍历链表
void begin_list(linklist* list){
    list->p_cur = &list->head;
}
//获取链表中netnode的数据
int get_list(linklist* list,int* fd,time_t* ltime){
    if(!list->p_cur){
        return 1;
    }
    list->p_cur = list->p_cur->p_next;
    if(list->p_cur == &(list->tail)){
        return 1;
    }
    if(!list->p_cur){
        return 1;
    }
    *fd = list->p_cur->web_fd;
    *ltime = list->p_cur->linktime;
    return 0;
}

