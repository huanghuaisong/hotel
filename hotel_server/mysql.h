#ifndef  MYSQL_H
#define  MYSQL_H
#include <mysql/mysql.h>
#include "server_data.h"
extern MYSQL *conn;
//建立数据库和表
void init_sql();

void create_room_data();

void load_user_data_from_mysql_database(MYSQL *conn);

void load_room_data_from_mysql_database(MYSQL * conn);

void insert_Client_info(MYSQL *conn,int account,char *passwd,int balance,char *register_time, int state);//插入用户信息

void insert_room_info(MYSQL *conn,int room_ID,int room_type,int bed_number,int window, int price,int owner_account);//插入房间信息
 
void change_usr_name(MYSQL *conn,int account,char *name);//修改用户名字

void change_usr_passwd(MYSQL *conn,int account,char *passwd);//修改用户密码

void update_room_info(MYSQL *	conn,int room_ID,int owner_account);

void update_cancel_room_info(MYSQL *	conn,int room_ID,int owner_account);


#endif
