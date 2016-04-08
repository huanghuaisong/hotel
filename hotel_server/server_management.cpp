#include "c_socket.h"
#include "define.h"
#include "command_process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "server_management.h"
#include "protocol.h"
#include "server_data.h"
#include "cJSON.h"
#include <unistd.h>
#include "define.h"
#include "string_int_transform.h"
#include <assert.h>

pthread_mutex_t mutex_pool;
pthread_cond_t  cond_pool;
int             connect_sid;

void parse_json_data(msg_t *msg,char *socket_buf)
{
	cJSON *jsonobject=cJSON_Parse(socket_buf);//网络字符串解析成json对象
	int message_type=cJSON_GetObjectItem(jsonobject,"messageType")->valueint;
	switch(message_type){
		case USER_REGISTER:
		{
			msg->msg_type=USER_REGISTER;
     		char *password=NULL;
			password=cJSON_GetObjectItem(jsonobject,"password")->valuestring;
			reg_t reg;
			memset(&reg,0,sizeof(reg));
			memcpy(reg.usr_passwd,password,strlen(password));
			memcpy(msg->msg_buf,&reg,sizeof(reg));	
		}
		break;
		
		case LOGIN:
		{
			msg->msg_type=LOGIN;
			char *account=NULL;
			account=cJSON_GetObjectItem(jsonobject,"account")->valuestring;
			char *password=NULL;
			password=cJSON_GetObjectItem(jsonobject,"password")->valuestring;
			login_t login;
			memset(&login,0,sizeof(login));
		    login.usr_account=my_atoi(account);
			memcpy(login.usr_passwd,password,strlen(password));
			memcpy(msg->msg_buf,&login,sizeof(login));	
		}
		break;

		case DO_RESERVATION:
		{
			plog("sdfsd");
			msg->msg_type=DO_RESERVATION;
			user_reservation_t user_reservation;
			user_reservation.user_account=cJSON_GetObjectItem(jsonobject,"userAccount")->valueint;
			user_reservation.room_ID=cJSON_GetObjectItem(jsonobject,"roomID")->valueint;
			memcpy(msg->msg_buf,&user_reservation,sizeof(user_reservation));
		}
		break;
		
		case DO_CANCEL_RESERVATION:
		{
			plog("sdfsd");
			msg->msg_type=DO_CANCEL_RESERVATION;
			cancel_reservation_t cancel_reservation;
			cancel_reservation.user_account=cJSON_GetObjectItem(jsonobject,"userAccount")->valueint;
			cancel_reservation.room_ID=cJSON_GetObjectItem(jsonobject,"roomID")->valueint;
			memcpy(msg->msg_buf,&cancel_reservation,sizeof(cancel_reservation));
		}
		break;

		case CHANGE_PASSWORD:
		{
			msg->msg_type=CHANGE_PASSWORD;
			change_passwd_t change_passwd;
			memset(&change_passwd,0,sizeof(change_passwd));
			change_passwd.account=cJSON_GetObjectItem(jsonobject,"userAccount")->valueint;
			char *new_passwd=cJSON_GetObjectItem(jsonobject,"newPassword")->valuestring;;
			char *origin_passwd=cJSON_GetObjectItem(jsonobject,"originPassword")->valuestring;
			
			memcpy(change_passwd.new_passwd,new_passwd,strlen(new_passwd));
			memcpy(change_passwd.origin_passwd,origin_passwd,strlen(origin_passwd));

			plog("a===>%s %s %d",change_passwd.new_passwd,change_passwd.origin_passwd,change_passwd.account);
			
			memcpy(msg->msg_buf,&change_passwd,sizeof(change_passwd));
		}
		break;
		
		default:
			break;
	}
}

//客户服务线程
void *client_service_thread(void *arg)
{
    while(1)
	{
		char socket_buf[1024];
		memset(&socket_buf,0,sizeof(socket_buf));
	    int c_sid ;//单聊线程连接号
	    int i = 0;
	    int ret = 0;
	    void *p_ret = NULL;
		
	    pthread_mutex_lock(&mutex_pool);//锁住
	    pthread_cond_wait(&cond_pool,&mutex_pool);//线程阻塞并等待条件变量成立
	    c_sid = connect_sid;
	    pthread_mutex_unlock(&mutex_pool);
		//刚开始不知道此用户配置信息属于哪个用户
	    client_config_t *cli_cfg = NULL;
		plog("client connect,connect id=%d",c_sid);
	
        i = 0;
        msg_t genmsg;
        memset(&genmsg,0,sizeof(genmsg));
		
        //等待用户发请求报文
        plog("sdasdasd\n");
        //ret = socket_read(c_sid, &genmsg, sizeof(genmsg));		
		ret = read(c_sid, socket_buf, sizeof(socket_buf));
		if(ret == 0)
        {
            plog("close c_sid = %d",c_sid);
            socket_close(c_sid);
            return NULL;
        }
		plog("socket_buf=%s\n",socket_buf);
		parse_json_data(&genmsg,socket_buf);
        plog("c_sid = %d, cmd = %d",c_sid, genmsg.msg_type);
        while(g_cmd_list[i].cmd >= 0)
        {
            //遍历状态机
            if(g_cmd_list[i].cmd == genmsg.msg_type)
            {
                //内容传进data参数中
                p_ret = g_cmd_list[i].cmd_handle(c_sid, genmsg.msg_buf, cli_cfg);
                if(g_cmd_list[i].cmd == LOGIN)
                {
                    if(p_ret != NULL)
                    {
                        cli_cfg = (client_config_t *)p_ret;
                    }
                }
            }
            i++;
        }
    }   
    return NULL;
}


//客户监听线程
void *client_listen_thread(void *arg)
{
    int     j;
    int         c_sid;
    pthread_t   c_pid;//线程ID

    //创建客户监听套接字
    server_cfg.client_listen_socket_id = socket_set_server(server_cfg.port, server_cfg.max_client);
    if(server_cfg.client_listen_socket_id < 0)
    {
        perror("server client_listen_thread socket create error\n");
        return NULL;
    }
    for(j=0; j<THREAD_POOL_MAX_NUM; j++)
	//创建线程池，全部进入阻塞，等待条件变量成立
    {
        if(pthread_create(&c_pid, NULL,client_service_thread, NULL) < 0)
        {
            perror("client client_service_thread created failed\n");
            return NULL;
        }
    }
    while(1)//连接客户端
    {
        c_sid = socket_accept(server_cfg.client_listen_socket_id);//等待连接该端口的客户端连接,然后返回一个临时的连接端口
        plog("client_listen_thread  client connect,connect id=%d",c_sid);
        if(c_sid < 0)
        {
            perror("client chat sid accept error\n");
            return NULL;
        }
        //连接成功则连接该客户端的服务线程,进入客户服务线程
        pthread_mutex_lock(&mutex_pool);//连接枷锁，保护connect_sid能够正确赋值
        connect_sid = c_sid;
        pthread_cond_signal(&cond_pool);//发送条件变量满足信号，线程导通
        pthread_mutex_unlock(&mutex_pool);
    }
    return NULL;
}

//初始化服务器
int init_server()
{
	int status;
    memset(&server_cfg,0,sizeof(server_config_t));
	server_cfg.max_client=MAX_NUM;//最大连接的客户数量
	server_cfg.port=SERVER_PORT;//服务器端口
	
	client_cfg.room_list.reserve(50);
	client_cfg.user_list.reserve(50);

	//创建客户监听线程
	if(pthread_create(&server_cfg.client_listen_thread_id, NULL, client_listen_thread, NULL ) != 0)		
    {
        perror("chat listen thread create error\n");
        return -1;
    }
	pthread_join(server_cfg.client_listen_thread_id,(void **)&status);
}

//关闭服务器
int close_server(){}
