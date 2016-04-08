#ifndef PROTOCOL_H
#define PROTOCOL_H

///////////////////�Զ���Э��///////////////

//ͨ����Ϣ�ṹ
//һ��Э��

typedef struct tag_msg
{
    //��Ϣ����
    unsigned int msg_type;
    //��Ϣ��������
    char msg_buf[1024];
} msg_t;

////////////����Э��/////////////////

/*********************ע������롢��ʼ���ͻ���************/
//ע������
typedef struct tag_reg
{
    //����
    char usr_passwd[16];
} reg_t;

//ע��Ӧ��
typedef struct tag_reg_rep
{
    // 0---ע��ʧ��
    // 1---ע��ɹ�
    unsigned int ack;
    unsigned int user_account;
} reg_rep_t;

//��������
typedef struct tag_login
{
    //�û�ID�˺�
    int usr_account;
    //�û�����
    char usr_passwd[15];

} login_t;
//����Ӧ����
typedef struct tag_login_rep
{
    int ack;
    int head_picture_num;
    char   name[15];
} login_rep_t;


typedef struct get_room_data{
	int user_account;
}get_room_data_t;

typedef struct reservation{
	int room_ID;
	int user_account;//��ס���û�ID
}user_reservation_t;

typedef struct cancel_reservation{
	int room_ID;
	int user_account;//��ס���û�ID
}cancel_reservation_t;

//�޸�����
typedef struct user_change_passwd
{
    //�û����˺�
    int account;
  //ԭʼ����
    char origin_passwd[15];
    //������
    char     new_passwd[15];
} change_passwd_t;
 

#endif
