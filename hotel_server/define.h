#ifndef _DEFINE_H
#define _DEFINE_H

#include <vector>
#include <sys/types.h>          /* See NOTES */
#include <pthread.h>
#include <stdio.h>
#include <time.h>             
using namespace std;                                                       
/**********************************消息类型****
/*连接服务器*/                                    
enum   message_type                     
{
        LOGIN ,             //请求登陆                                           
        LOGIN_SUCCESS,      //登陆成功1
        LOGIN_FAILURE,      //登录失败
        USER_NO_EXIST,      //用户不存在
        USER_IS_ONLINE,     //用户在线
        USER_NO_ONLINE,     //用户不在线                                                                                                                                                                            
        USER_ALREADY_EXIST, //用户已经存在

        USER_REGISTER,      //注册账号6
        REGISTER_SUCCESS,   //注册成功
        REGISTER_FAILED,    //注册失败
        CHANGE_PASSWORD,    //修改密码9
        CHANGE_SUCCESS,     //修改成功
        PASSWORD_ERROR,     //密码错误
        ORIGIN_PASSWD_ERROR,//原始密码错误12

		GET_ROOM_DATA,   	//获取可入住的房间
		ROOM_DATA_LOADING,	//不断获取房间数据
		ROOM_DATA_LOAD_COMPLETED,//获取完成
		ROOM_RESERVATION_SUCCESS,//入住成功
		ROOM_RESERVATION_FAILURE,//入住失败
		DO_RESERVATION,

		CANCEL_ROOM_RESERVATION_SUCCESS,//退房成功
        CANCEL_ROOM_RESERVATION_FAILURE,//退房失败
        DO_CANCEL_RESERVATION,
};

/*连接设置*/
#define SERVER_PORT 8887         //点对点聊天端口号
#define LOCAL_IP  "127.0.0.1"    //本地IP
#define SERVER_IP "127.0.0.1"    //服务器IP
#define MAX_NUM   2000           //最大客户端数目
#define THREAD_POOL_MAX_NUM 20   //最大线程池数

//用户信息
typedef struct client_info
{
    int   usr_account;        //用户ID
    char            passwd[15];         //密码
    int 			balance;			//余额
	char            register_time[32];  //注册时间 
    int             state;              // 用户状态 0--->离线 1--->在线
} client_info_t;

//房间信息
typedef struct room_info
{
    int			    room_ID;        	//房间ID
    int 			room_type;			//房间类型
    int 			bed_number;			//床位数量
	int             window;				//是否有窗户
	int 			price;				//房间价格
	int 			owner_account;		//拥有者ID
} room_info_t;

/* 服务器上用户描述信息 */
typedef struct client_config
{
    vector<client_info_t>                   user_list;            //用户链表
    vector<room_info_t>                     room_list;            //已经预定的房间链表
} client_config_t;

typedef struct server_config
{
	int  port;//服务器端口
    int  max_client;// 最大允许用户数目
	pthread_t client_listen_socket_id;//客户监听套接字ID
	pthread_t client_listen_thread_id;//客户监听线程ID		
}server_config_t;


#endif
