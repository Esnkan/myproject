#ifndef _COMMON_H_
#define _COMMON_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sqlite3.h>
#include<sys/wait.h>
#include<signal.h>
#include<time.h>
#include<pthread.h>
#include<sys/stat.h>
#include<sqlite3.h>


#define STAFF_DATABASE 	 "staff_manage_system.db"


#define USER_LOGIN 	0x00000000  // login	登陆    0x00000001
#define USER_MODIFY 	0x00000001  // user-modification  修改
#define USER_QUERY 	0x00000002  // user-query   查询


#define ADMIN_LOGIN 	0x10000000  // login	登陆    0x00000001
#define ADMIN_MODIFY 	0x10000001 // admin_modification
#define ADMIN_ADDUSER 	0x10000002 // admin_adduser
#define ADMIN_DELUSER 	0x10000004 // admin_deluser
#define ADMIN_QUERY 	0x10000008  //hitory_query
#define ADMIN_HISTORY 	0x10000010  //hitory_query

#define QUIT 		0x11111111


#define ADMIN 0	//管理员
#define USER  1	//用户

#define NAMELEN 16
#define DATALEN 128


/*员工基本信息*/
typedef struct staff_info{
	int  no; 		//员工编号
	int  usertype;  	//ADMIN 1，USER 2	 
	char name[NAMELEN];	//姓名
	char passwd[8]; 	//密码
	int  age; 		// 年龄
	char phone[NAMELEN];	//电话
	char addr[DATALEN]; 	// 地址
	char work[DATALEN]; 	//职位
	char date[DATALEN];	//入职年月
	int level;		// 等级
	double salary ;		// 工资
}staff_info_t;


/*定义双方通信的结构体信息*/
typedef struct {
	int  msgtype;    	 //请求的消息类型
	int  usertype;   	 //ADMIN 1	USER 2	   
	char username[NAMELEN];  //姓名
	char passwd[8];		//登陆密码
	char recvmsg[DATALEN];   //通信的消息
	int  flags;      	//标志位
	staff_info_t info;      //员工信息
}MSG;


/*定义线程处理的结构体信息*/
typedef struct thread_data{
	int acceptfd;
	pthread_t thread;
	int state; //线程状态
	MSG *msg; 
	void *prvi_data;
}thread_data_t;


//扩展:线程链表信息
typedef struct thread_node{
	thread_data_t data;
	struct thread_node *next;
}linklist, *plinklist;


/*-------------------------客户端接口-------------------------*/
int do_login(int sockfd);//登录模式选择
int admin_or_user_login(int sockfd,MSG *msg);//欢迎用户和管理员界面

void user_menu(int sockfd,MSG *msg);//用户欢迎界面
void do_user_query(int sockfd,MSG *msg);//用户查询
void do_user_modification(int sockfd,MSG *msg);//用户修改

void admin_menu(int sockfd,MSG *msg);//管理员欢迎界面
void do_admin_query(int sockfd,MSG *msg);//管理员查询
void do_admin_modification(int sockfd,MSG *msg);//管理员修改
void do_admin_adduser(int sockfd,MSG *msg);//管理员添加用户
void do_admin_deluser(int sockfd,MSG *msg);//管理员删除用户
void do_admin_history (int sockfd,MSG *msg);//管理员查看历史记录

void show_userinfo(MSG *msg);//查看信息结果

/*-------------------------服务器端接口-------------------------*/
int process_user_or_admin_login_request(int acceptfd,MSG *msg);//用户和管理员登录模式请求
int process_client_request(int acceptfd,MSG *msg);//客户端请求处理

int process_user_query_request(int acceptfd,MSG *msg);//用户查询处理
int process_user_modify_request(int acceptfd,MSG *msg);//用户修改处理

int process_admin_query_request(int acceptfd,MSG *msg);//管理员查询处理
int process_admin_modify_request(int acceptfd,MSG *msg);//管理员修改处理
int process_admin_adduser_request(int acceptfd,MSG *msg);//管理员添加用户处理
int process_admin_deluser_request(int acceptfd,MSG *msg);//管理员删除用户处理
int process_admin_history_request(int acceptfd,MSG *msg);//管理员查看历史记录处理


void get_system_time(char* timedata);//获取系统时间
void history_init(MSG *msg,char *buf);//处理历史内容buf
int history_callback(void *arg, int ncolumn, char **f_value, char **f_name);//历史查询回调函数


#endif

