#ifndef _DEFINE_H
#define _DEFINE_H

#include <vector>
#include <sys/types.h>          /* See NOTES */
#include <pthread.h>
#include <stdio.h>
#include <time.h>             
using namespace std;                                                       
/**********************************��Ϣ����****
/*���ӷ�����*/                                    
enum   message_type                     
{
        LOGIN ,             //�����½                                           
        LOGIN_SUCCESS,      //��½�ɹ�1
        LOGIN_FAILURE,      //��¼ʧ��
        USER_NO_EXIST,      //�û�������
        USER_IS_ONLINE,     //�û�����
        USER_NO_ONLINE,     //�û�������                                                                                                                                                                            
        USER_ALREADY_EXIST, //�û��Ѿ�����

        USER_REGISTER,      //ע���˺�6
        REGISTER_SUCCESS,   //ע��ɹ�
        REGISTER_FAILED,    //ע��ʧ��
        CHANGE_PASSWORD,    //�޸�����9
        CHANGE_SUCCESS,     //�޸ĳɹ�
        PASSWORD_ERROR,     //�������
        ORIGIN_PASSWD_ERROR,//ԭʼ�������12

		GET_ROOM_DATA,   	//��ȡ����ס�ķ���
		ROOM_DATA_LOADING,	//���ϻ�ȡ��������
		ROOM_DATA_LOAD_COMPLETED,//��ȡ���
		ROOM_RESERVATION_SUCCESS,//��ס�ɹ�
		ROOM_RESERVATION_FAILURE,//��סʧ��
		DO_RESERVATION,

		CANCEL_ROOM_RESERVATION_SUCCESS,//�˷��ɹ�
        CANCEL_ROOM_RESERVATION_FAILURE,//�˷�ʧ��
        DO_CANCEL_RESERVATION,
};

/*��������*/
#define SERVER_PORT 8887         //��Ե�����˿ں�
#define LOCAL_IP  "127.0.0.1"    //����IP
#define SERVER_IP "127.0.0.1"    //������IP
#define MAX_NUM   2000           //���ͻ�����Ŀ
#define THREAD_POOL_MAX_NUM 20   //����̳߳���

//�û���Ϣ
typedef struct client_info
{
    int   usr_account;        //�û�ID
    char            passwd[15];         //����
    int 			balance;			//���
	char            register_time[32];  //ע��ʱ�� 
    int             state;              // �û�״̬ 0--->���� 1--->����
} client_info_t;

//������Ϣ
typedef struct room_info
{
    int			    room_ID;        	//����ID
    int 			room_type;			//��������
    int 			bed_number;			//��λ����
	int             window;				//�Ƿ��д���
	int 			price;				//����۸�
	int 			owner_account;		//ӵ����ID
} room_info_t;

/* ���������û�������Ϣ */
typedef struct client_config
{
    vector<client_info_t>                   user_list;            //�û�����
    vector<room_info_t>                     room_list;            //�Ѿ�Ԥ���ķ�������
} client_config_t;

typedef struct server_config
{
	int  port;//�������˿�
    int  max_client;// ��������û���Ŀ
	pthread_t client_listen_socket_id;//�ͻ������׽���ID
	pthread_t client_listen_thread_id;//�ͻ������߳�ID		
}server_config_t;


#endif
