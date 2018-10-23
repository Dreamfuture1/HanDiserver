#include <time.h>
/*
 *每次wechat端发起与服务器的连接的时候,服务器同时也与一台充电桩发起了连接
 *根据连接的时间差来判断是否超时来断开连接
 * 
 *
 *
 * */

//命令发送给的充电桩的id,端口，和命令,这三个数据可以保证对象唯一
typedef struct cmd_node{
    //11位终端ID
    long TerminalId;
    //2位终端POTR
    char TerminalPort;
    //用户类型
    char UserType;
    //2位功能码
    char CmdCode;
    //命令连接或者再次访问的时间
    time_t linktime;

    struct cmd_node* p_next;
}cmdnode;
//记录连接描述符和本次连接时间
typedef struct net_node{
    //连接描述符
    int web_fd;
    //每次发生连接的时候的链接时间
    time_t linktime;
    //指向下一个本类型节点的指针
    struct net_node* p_next;
    struct net_node* p_prev;
    //指向 存储本次连接传来命令概要信息 的节点的指针
    cmdnode* p_cmdnode;
}netnode;

typedef struct{
    netnode head;
    netnode tail;
    //用来遍历节点，取其中的数据
    netnode* p_cur;
}linklist;


//完整命令结构体
typedef struct web_cmd_node{
    //11位终端ID
    long TerminalId;
    //2位终端POTR
    char TerminalPort;
    //用户类型
    char UserType;
    //2位功能码
    char CmdCode;
    union
    {
	//1位数据或2位数据或1段时间数据
	char  ucData;
	struct
	{
	    short   usPart1;
	    short   usPart2;
	};
	struct tm   stTime;
	char	    cBuf[128];
    };
	//命令失败重试次数，A5 A4初始化命令CMDLIFE次用
	char  ucTimes;
}webcmdnode;




