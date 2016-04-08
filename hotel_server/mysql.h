#ifndef  MYSQL_H
#define  MYSQL_H
#include <mysql/mysql.h>
#include "server_data.h"
extern MYSQL *conn;
//�������ݿ�ͱ�
void init_sql();

void create_room_data();

void load_user_data_from_mysql_database(MYSQL *conn);

void load_room_data_from_mysql_database(MYSQL * conn);

void insert_Client_info(MYSQL *conn,int account,char *passwd,int balance,char *register_time, int state);//�����û���Ϣ

void insert_room_info(MYSQL *conn,int room_ID,int room_type,int bed_number,int window, int price,int owner_account);//���뷿����Ϣ
 
void change_usr_name(MYSQL *conn,int account,char *name);//�޸��û�����

void change_usr_passwd(MYSQL *conn,int account,char *passwd);//�޸��û�����

void update_room_info(MYSQL *	conn,int room_ID,int owner_account);

void update_cancel_room_info(MYSQL *	conn,int room_ID,int owner_account);


#endif
