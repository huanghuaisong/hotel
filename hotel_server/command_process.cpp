#include "string_int_transform.h"
#include "command_process.h"
#include "protocol.h"
#include "cJSON.h"
#include "server_data.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "define.h"
#include <time.h>//该头文件是必须包含的
#include <curses.h>
#include <assert.h>  
#include <vector>
#include "mysql.h"
#include <mysql/mysql.h>
#include <vector>
//void *memcpy(void *dest, const void *src, size_t n);
unsigned long  register_id = 123456;
CMD_PROCESS_T g_cmd_list[] =
{
    {USER_REGISTER,         do_register},
	{LOGIN,                 do_login},
	{DO_RESERVATION,        do_user_room_reservation},
    {DO_CANCEL_RESERVATION, do_cancel_user_room_reservation},
    {CHANGE_PASSWORD,		do_change_passwd},
    {-1,NULL}
};

char *get_system_time(){
	time_t t;//定义一个时间变量
	t=time(NULL);
	return ctime(&t);
}

void *do_register(int c_sid,void *data,client_config_t *cli_cfg_info)
{
	reg_t *reg=(reg_t *)data;
	client_info_t cli;
	memset(&cli,0,sizeof(cli));
	cli.balance=0;
	strcpy(cli.passwd,reg->usr_passwd);
	strcpy(cli.register_time,get_system_time());
	cli.state=USER_NO_ONLINE;
	cli.usr_account=register_id;

	client_cfg.user_list.push_back(cli);
	//插入到数据库中
	insert_Client_info(conn,cli.usr_account,cli.passwd,cli.balance,cli.register_time, cli.state);//插入联系人信息
	
	cJSON * register_json = NULL;
	register_json = cJSON_CreateObject();
	if(NULL == register_json)
	{
		//error happend here
		plog("cJSON_CreateObject error ");
		return NULL;
	}
	char account[10]="";
	my_itoa(register_id++, account, 10);
	
	cJSON_AddStringToObject(register_json, "account",account);
	cJSON_AddNumberToObject(register_json, "ack", REGISTER_SUCCESS);
	char send_buffer[1024];
	memcpy(send_buffer,cJSON_Print(register_json),strlen(cJSON_Print(register_json)));
	write(c_sid,send_buffer,sizeof(send_buffer));
	
}

void* do_login(int c_sid,void *data,client_config_t *cli_cfg_info)
{
	login_t *login=(login_t *)data;
	char send_buffer[1024];
	cJSON * login_json = NULL;
	login_json = cJSON_CreateObject();
	if(NULL == login_json)
	{
		plog("cJSON_CreateObject error.");
		return NULL;
	}
	vector<client_info_t>::iterator it;
	for (it=client_cfg.user_list.begin() ; it !=client_cfg.user_list.end() ; it++) 
    {  
    	plog("%d %d,%s %s",it->usr_account, login->usr_account,it->passwd,login->usr_passwd);
        if(it->usr_account == login->usr_account )
        {
			if(strcmp(it->passwd,login->usr_passwd) == 0)  
        	{
				it->state=USER_IS_ONLINE;//设置为上线状态
				cJSON_AddNumberToObject(login_json, "usr_account",it->usr_account);
				cJSON_AddStringToObject(login_json, "passwd",it->passwd);
				cJSON_AddNumberToObject(login_json, "balance",it->balance);
				cJSON_AddNumberToObject(login_json, "ack",LOGIN_SUCCESS);
			}
			else{
				cJSON_AddNumberToObject(login_json, "usr_account",0);
				cJSON_AddStringToObject(login_json, "passwd","");
				cJSON_AddNumberToObject(login_json, "balance",0);
				cJSON_AddNumberToObject(login_json, "ack",LOGIN_FAILURE);
			}
			break;
        }
    }
	
	memcpy(send_buffer,cJSON_Print(login_json),strlen(cJSON_Print(login_json)));
	write(c_sid,send_buffer,sizeof(send_buffer));
	
}

void* do_send_room_data_to_phone(int c_sid,void *data,client_config_t *cli_cfg_info)
{	
	get_room_data_t *get_room_data=(get_room_data_t *)data;
	char send_buffer[1024];//发送数据缓冲区
	memset(send_buffer,0,sizeof(send_buffer));
	vector<room_info_t>::iterator it;
	int count=0;
	for(it=client_cfg.room_list.begin();it!=client_cfg.room_list.end();it++)
	{
		if(0 == it->owner_account)//空房
		{
			//发送该房间数据给客户端
			cJSON * room_data_json = NULL;
			room_data_json = cJSON_CreateObject();
			cJSON_AddNumberToObject(room_data_json, "ack",ROOM_DATA_LOADING);
			cJSON_AddNumberToObject(room_data_json, "room_ID", it->room_ID);
			cJSON_AddNumberToObject(room_data_json, "room_type", it->room_type);
			cJSON_AddNumberToObject(room_data_json, "bed_number", it->bed_number);
			cJSON_AddNumberToObject(room_data_json, "window", it->window);
			cJSON_AddNumberToObject(room_data_json, "price", it->price);
			cJSON_AddNumberToObject(room_data_json, "owner_account",it->owner_account);
			memcpy(send_buffer,cJSON_Print(room_data_json),strlen(cJSON_Print(room_data_json)));
			write(c_sid,send_buffer,sizeof(send_buffer));
			memset(send_buffer,0,sizeof(send_buffer));
			count++;
		}
	}
	
	plog("%d",count);
	/*
	if(it == client_cfg.room_list.end())
	{
		cJSON * room_data_json1 = NULL;
		room_data_json1 = cJSON_CreateObject();
		cJSON_AddNumberToObject(room_data_json1, "ack",ROOM_DATA_LOAD_COMPLETED);
		
		cJSON_AddNumberToObject(room_data_json1, "room_ID", 11111);
		cJSON_AddNumberToObject(room_data_json1, "room_type", 11111);
		cJSON_AddNumberToObject(room_data_json1, "bed_number", 11111);
		cJSON_AddNumberToObject(room_data_json1, "window", 11111);
		cJSON_AddNumberToObject(room_data_json1, "price", 11111);
		cJSON_AddNumberToObject(room_data_json1, "owner_account",11111);

		memcpy(send_buffer,cJSON_Print(room_data_json1),strlen(cJSON_Print(room_data_json1)));
		write(c_sid,send_buffer,sizeof(send_buffer));	
	}
	*/
	
}


void *do_change_passwd(int c_sid,void * data,client_config_t * cli_cfg_info)
{
	plog("dfdfsd");
	//客户端发送用户账号/原始密码/新密码过来，服务器进行判断后进行修改并且添加，如果验证正确，则修改数据库，
	//否则不修改
	
	//1.先更改链表
	change_passwd_t* change_passwd=(change_passwd_t*)data;

	char send_buffer[1024];
	cJSON * change_password_json = NULL;
	change_password_json = cJSON_CreateObject();
	if(NULL == change_password_json)
	{
		plog("cJSON_CreateObject error.");
		return NULL;
	}
	
	vector<client_info_t>::iterator it;
	for (it=client_cfg.user_list.begin() ; it !=client_cfg.user_list.end() ; it++) 
	{
		if(it->usr_account == change_passwd->account )//账号相同
		{
			plog("%d",it->usr_account);
			if(strcmp(it->passwd,change_passwd->origin_passwd) == 0)//密码相同
			{plog("it->passw=%s,change_passwd->new_passwd=%s",it->passwd,change_passwd->new_passwd);
				memcpy(it->passwd,change_passwd->new_passwd,strlen(change_passwd->new_passwd));//修改密码
				change_usr_passwd(conn,change_passwd->account,change_passwd->new_passwd);
				cJSON_AddNumberToObject(change_password_json, "ack",CHANGE_SUCCESS);
			}
			else{//密码不用
				cJSON_AddNumberToObject(change_password_json, "ack",ORIGIN_PASSWD_ERROR);//原始密码错误
			}
			break;
		}
	}
	
	memcpy(send_buffer,cJSON_Print(change_password_json),strlen(cJSON_Print(change_password_json)));
	write(c_sid,send_buffer,sizeof(send_buffer));
	
}

void* do_user_room_reservation(int c_sid,void *data,client_config_t * cli_cfg_info)
{
	//客户端发送房间编号过来，服务器端将更改数据库中该房间的拥有者，同时更改该链表

	//1.先更改链表
	user_reservation_t* user_reservation=(user_reservation_t*)data;
	plog("a=%d,b=%d",user_reservation->room_ID,user_reservation->user_account);
	char send_buffer[1024];
	memset(send_buffer,0,sizeof(send_buffer));
	
	cJSON * reservation_json = NULL;
	reservation_json = cJSON_CreateObject();
	if(NULL == reservation_json)
	{
		plog("cJSON_CreateObject error.");
		return NULL;
	}
	
	vector<room_info_t>::iterator it;
	
	for (it=client_cfg.room_list.begin();it != client_cfg.room_list.end() ; it++) 
	{
		printf("it->room_ID=%d user_reservation->room_ID=%d\n",it->room_ID,user_reservation->room_ID);
		if(it->room_ID == user_reservation->room_ID)//查找相同编号相同的ID
		{
			plog("%d",it->owner_account);
			
			if(0 == it->owner_account )//如果没有人入住
			{
				//如果房间为空，则入住，并且设置数据库，同时向客户端发送一段成功数据
				it->owner_account=user_reservation->user_account;//入住用户名
				update_room_info(conn,it->room_ID,it->owner_account);
			//	cJSON_AddStringToObject(reservation_json, "ack","ROOM_RESERVATION_SUCCESS");
				cJSON_AddNumberToObject(reservation_json, "ack", ROOM_RESERVATION_SUCCESS);
				plog("csdsd");
				
			}
			else
			{
				//如果房间为非空,则向客户端发送一段失败数据
				//cJSON_AddStringToObject(reservation_json, "ack","ROOM_RESERVATION_FAILURE");
				cJSON_AddNumberToObject(reservation_json, "ack", ROOM_RESERVATION_FAILURE);
				plog("csdsd");
			}
			break;
			
		}
		
	}
	
	memcpy(send_buffer,cJSON_Print(reservation_json),strlen(cJSON_Print(reservation_json)));
	write(c_sid,send_buffer,sizeof(send_buffer));
	plog("csdsd");
	
}


void *do_cancel_user_room_reservation(int c_sid,void * data,client_config_t * cli_cfg_info)
{
	//客户端发送房间编号过来，服务器端将更改数据库中该房间的拥有者，同时更改该链表

	//1.先更改链表
	cancel_reservation_t* cancel_reservation=(cancel_reservation_t*)data;
	plog("a=%d,b=%d",cancel_reservation->room_ID,cancel_reservation->user_account);
	char send_buffer[1024];
	memset(send_buffer,0,sizeof(send_buffer));
	
	cJSON * cancel_reservation_json = NULL;
	cancel_reservation_json = cJSON_CreateObject();
	if(NULL == cancel_reservation_json)
	{
		plog("cJSON_CreateObject error.");
		return NULL;
	}
	
	vector<room_info_t>::iterator it;
	
	for (it=client_cfg.room_list.begin();it != client_cfg.room_list.end() ; it++) 
	{
		printf("it->room_ID=%d user_reservation->room_ID=%d\n",it->room_ID,cancel_reservation->room_ID);
		if(it->room_ID == cancel_reservation->room_ID)//查找相同编号相同的ID
		{
			plog("%d",it->owner_account);
			
			if(cancel_reservation->user_account == it->owner_account )//如果没有人入住
			{
				//如果房间为空，则入住，并且设置数据库，同时向客户端发送一段成功数据
				it->owner_account=0;//入住用户名
				update_room_info(conn,it->room_ID,0);
			//	cJSON_AddStringToObject(reservation_json, "ack","ROOM_RESERVATION_SUCCESS");
				cJSON_AddNumberToObject(cancel_reservation_json, "ack", CANCEL_ROOM_RESERVATION_SUCCESS);
				plog("csdsd");
				
			}
			else
			{
				//如果房间为非空,则向客户端发送一段失败数据
				//cJSON_AddStringToObject(reservation_json, "ack","ROOM_RESERVATION_FAILURE");
				cJSON_AddNumberToObject(cancel_reservation_json, "ack", CANCEL_ROOM_RESERVATION_FAILURE);
				plog("csdsd");
			}
			break;
			
		}
		
	}
	
	memcpy(send_buffer,cJSON_Print(cancel_reservation_json),strlen(cJSON_Print(cancel_reservation_json)));
	write(c_sid,send_buffer,sizeof(send_buffer));
	plog("csdsd");
	
}

void show_list()
{
	vector<client_info_t>::iterator it;
	for (it=client_cfg.user_list.begin() ; it !=client_cfg.user_list.end() ; it++) 
	{
		printf("%s,%d\n",it->passwd,it->usr_account);
	}
}