#ifndef PROTOCOL_H
#define PROTOCOL_H

///////////////////自定义协议///////////////

//通用消息结构
//一层协议

typedef struct tag_msg
{
    //消息类型
    unsigned int msg_type;
    //消息具体内容
    char msg_buf[1024];
} msg_t;

////////////二层协议/////////////////

/*********************注册与登入、初始化客户端************/
//注册请求
typedef struct tag_reg
{
    //密码
    char usr_passwd[16];
} reg_t;

//注册应答
typedef struct tag_reg_rep
{
    // 0---注册失板
    // 1---注册成功
    unsigned int ack;
    unsigned int user_account;
} reg_rep_t;

//登入请求
typedef struct tag_login
{
    //用户ID账号
    int usr_account;
    //用户密码
    char usr_passwd[15];

} login_t;
//登入应答报文
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
	int user_account;//入住的用户ID
}user_reservation_t;

typedef struct cancel_reservation{
	int room_ID;
	int user_account;//入住的用户ID
}cancel_reservation_t;

//修改密码
typedef struct user_change_passwd
{
    //用户的账号
    int account;
  //原始密码
    char origin_passwd[15];
    //新密码
    char     new_passwd[15];
} change_passwd_t;
 

#endif
