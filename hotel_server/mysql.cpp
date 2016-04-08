#include "define.h"
#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include "server_data.h"
#include "mysql.h"
using namespace std;

MYSQL *conn = NULL;

//�������ݿ�ͱ�
void init_sql()
{
    conn=mysql_init(NULL);//������߳�ʼ������mysql_real_connect����Ӧ��MYSQL����
    if(mysql_real_connect(conn,"127.0.0.1","root","540870","client",3306,NULL,0)==NULL)
    {
        printf("connect error %s\n",mysql_error(conn));
        return ;
    }
  //mysql_query(conn,"drop database if exists client;");
  //mysql_query(conn,"create database client;");
  	mysql_query(conn,"USE client;");//���ݿⷢ��һ����ѯ���
  //mysql_query(conn,"create table client_info(usr_account int ,passwd varchar(15),balance int,register_time varchar(32),state int);");
  //mysql_query(conn,"create table room_info(room_ID int ,room_type int,bed_number int,window int,price int,owner_account int);");
}


void create_room_data()
{
	room_info_t room_info;
	memset(&room_info,0,sizeof(room_info));
	
	int room_floor1=100,room_floor2=200,room_floor3=300,room_floor4=400,room_floor5=500;
	int i;
	for(i=0;i<5;i++)
	{
		room_info.room_ID=room_floor1++;
		room_info.room_type=1;//��׼����
		room_info.bed_number=1;
		room_info.window=1;//�д���
		room_info.price=100;
		room_info.owner_account=0;//�շ�	
		client_cfg.room_list.push_back(room_info);
		insert_room_info(conn,room_info.room_ID,room_info.room_type,room_info.bed_number,room_info.window,room_info.price,room_info.owner_account);
		memset(&room_info,0,sizeof(room_info));
	}
	for(i=0;i<5;i++)
	{
		room_info.room_ID=room_floor2++;
		room_info.room_type=1;//��׼����
		room_info.bed_number=2;
		room_info.window=1;//�д���
		room_info.price=140;
		room_info.owner_account=0;//�շ�	
		client_cfg.room_list.push_back(room_info);
		insert_room_info(conn,room_info.room_ID,room_info.room_type,room_info.bed_number,room_info.window,room_info.price,room_info.owner_account);
		memset(&room_info,0,sizeof(room_info));
	}
	for(i=0;i<5;i++)
	{
		room_info.room_ID=room_floor3++;
		room_info.room_type=2;//��������
		room_info.bed_number=1;
		room_info.window=1;//�д���
		room_info.price=150;
		room_info.owner_account=0;//�շ�	
		client_cfg.room_list.push_back(room_info);
		insert_room_info(conn,room_info.room_ID,room_info.room_type,room_info.bed_number,room_info.window,room_info.price,room_info.owner_account);
		memset(&room_info,0,sizeof(room_info));
	}

}

void load_user_data_from_mysql_database(MYSQL * conn)
{
	MYSQL_FIELD *fd;
    char buf[10][20];
    char str[255];
    sprintf(str,"select * from client_info;");
    mysql_query(conn,str);
    MYSQL_RES *res;//�����洢�ṹ
    res=mysql_store_result(conn);
    int row1=mysql_num_rows(res);
    int col =mysql_num_fields(res);
    int i,j;	
    MYSQL_ROW row;//����ȡ���ݵĽṹ������ָ��
	client_info_t cli;
	memset(&cli,0,sizeof(cli));
    if(res)
    {
        while((row=mysql_fetch_row(res))!=NULL)//����ȡ������е���
        {
            for(i=0; i<col; i++)//������buf
                sprintf(buf[i],"%s",row[i]);
            cli.usr_account = atoi(buf[0]);
			strcpy(cli.passwd,buf[1]);
			cli.balance=atoi(buf[2]);
			strcpy(cli.register_time,buf[3]);
			cli.state=atoi(buf[4]);	//sprintf(str,"\"%d\",\"%s\",\"%d\",\"%s\",\"%d\");",account,passwd,balance,register_time, state);
			
			client_cfg.user_list.push_back(cli);//���ݿ�����ݲ�������

			memset(&cli,0,sizeof(cli));

			register_id++;//�˺ŵ���
        }
    }
}

void load_room_data_from_mysql_database(MYSQL * conn)
{
	MYSQL_FIELD *fd;
    char buf[10][20];
    char str[255];
    sprintf(str,"select * from room_info;");
    mysql_query(conn,str);
    MYSQL_RES *res;//�����洢�ṹ
    res=mysql_store_result(conn);
    int row1=mysql_num_rows(res);
    int col =mysql_num_fields(res);
    int i,j;	
    MYSQL_ROW row;//����ȡ���ݵĽṹ������ָ��
	room_info_t room_info;
	memset(&room_info,0,sizeof(room_info));
    if(res)
    {
        while((row=mysql_fetch_row(res))!=NULL)//����ȡ������е���
        {
            for(i=0; i<col; i++)//������buf
                sprintf(buf[i],"%s",row[i]);
			room_info.room_ID= atoi(buf[0]);
			room_info.room_type= atoi(buf[1]);
			room_info.bed_number=atoi(buf[2]);
			room_info.window=atoi(buf[3]);
			room_info.price=atoi(buf[4]);
			room_info.owner_account=atoi(buf[5]);
			
			client_cfg.room_list.push_back(room_info);//���ݿ�����ݲ�������
			
			memset(&room_info,0,sizeof(room_info));

        }
    }
}
	
//�����û���Ϣ
void insert_Client_info(MYSQL *conn,int account,char *passwd,int balance,char *register_time, int state)//������ϵ����Ϣ
{
  //create table room_info(room_ID int ,room_type int,bed_number int,window int,price int,owner_account int);
    char str[255];
    sprintf(str,"\"%d\",\"%s\",\"%d\",\"%s\",\"%d\");",account,passwd,balance,register_time, state);
    char sql1[128]="insert into client_info values(";
    strcat(sql1,str);
	plog("%s",sql1);
    mysql_query(conn,sql1);
}

//�����û���Ϣ
void insert_room_info(MYSQL *conn,int room_ID,int room_type,int bed_number,int window, int price,int owner_account)
{
    char str[255];
    sprintf(str,"\"%d\",\"%d\",\"%d\",\"%d\",\"%d\",\"%d\");",room_ID,room_type,bed_number,window, price,owner_account);
    char sql1[128]="insert into room_info values(";
    strcat(sql1,str);
	plog("%s",sql1);
    mysql_query(conn,sql1);
}

void update_room_info(MYSQL *	conn,int room_ID,int owner_account)
{
	char str[255];
    sprintf(str,"update room_info set owner_account=%d where room_ID=%d;",owner_account,room_ID);
    mysql_query(conn,str);
}


void update_cancel_room_info(MYSQL *	conn,int room_ID,int owner_account)
{
	char str[255];
	sprintf(str,"update room_info set owner_account=%d where room_ID=%d;",owner_account,room_ID);
	mysql_query(conn,str);

}


//�޸��û�����
void change_usr_passwd(MYSQL *conn,int account,char *passwd)
{
    char str[255];
    sprintf(str,"update client_info set passwd='%s' where usr_account=%d;",passwd,account);
    mysql_query(conn,str);
}
 
//�޸��û�����
void change_usr_name(MYSQL *conn,int account,char *name)
{
    char str[255];
    sprintf(str,"update client_info set usr_name='%s' where usr_account=%d;",name,account);
    mysql_query(conn,str);
}



 
 

