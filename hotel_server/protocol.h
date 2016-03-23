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
    unsigned long usr_account;
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

//初始化好友列表请求
typedef struct init_friend
{
    unsigned long  MyAcoount;
} init_friend_request_t;
//初始化好友列表回应
typedef struct friend_list_info
{
    int ack;
    int head_num;//头像
    unsigned long friend_account;
    int state;
    char friend_name[15];
} friend_list_info_t;

//初始化群列表请求
typedef struct init_community
{
    unsigned long  MyAcoount;
} init_community_t;

//初始化群列表回应
typedef struct group_list_info
{
    int ack;
    unsigned long group_account;
    unsigned long group_owner_account;
    char group_name[15];
} group_list_info_t;

//初始化群成员列表请求
typedef struct init_group_member
{
    unsigned long group_account;
} init_group_member_t;

//初始化群成员列表回应
typedef struct init_group_member_rep
{
    int ack;
    unsigned long       usr_account;
    int     head_picture_num;
    char           usr_name[15];
} init_group_member_rep_t;
/*************************添加好友*******************/
//添加好友请求 报文(申请者发送给服务器)
typedef struct add_fri
{
    //好友的账号
    unsigned long   fri_account;
} add_fri_t;

//申请添加好友请求(服务器发送给被申请者)
typedef struct  ask_for_add_friend
{
    //申请者的头像
    int head_picture_num;
    //申请者的账号
    unsigned  long  asker_account;
    //申请者的昵称
    char  asker_name[15];
} ask_for_add_friend_t;

//同意申请应答报文(被申请者发送给服务器)
typedef struct  ask_for_add_friend_rep
{
    int ack;
    //申请者账号
    unsigned long asker_account;
} ask_for_add_friend_rep_t;


//添加好友应答报文(服务器发给申请者)
typedef struct  tag_add_fri_rep
{
    int ack;
    //好友的姓名账号头像
    unsigned long  fri_account;
    int fri_head_picture_num;
    char     fri_name[15];
} add_fri_rep_t;


/******************删除好友*********************/
//删除好友请求 报文(申请者发送给服务器)
typedef struct del_fri
{
    //好友的账号
    unsigned long   fri_account;
} del_fri_t;

//删除好友应答(服务器发给申请者)
typedef struct del_fri_rep
{
    //删除成功与否
    int  ack;
} del_fri_rep_t;


/*********************更新状态与修改密码************/


// 通告上线或者下线
typedef struct notify_user_state
{
    int state;
    //好友ID
    unsigned long user_id;
    int  head_num;
} notify_user_state_t;


// 更新好友列表
typedef struct update_friend_list
{
    unsigned long user_id;
} up_fri_list_t;

// 更新好友列表响应
typedef struct update_friend_list_rep
{
    int  ack;
    //好友头像
    int friend_head_picture_num;
    // 用户ID
    unsigned long  user_id;
    // 该用户状态 0 或者1
    int  status;
    char name[15];
} update_friend_list_rep_t;


// 更新群列表
typedef struct update_group_list
{
    unsigned long user_id;
} up_group_list_t;

// 更新群列表响应
typedef struct update_group_list_rep
{
    int  ack;
    unsigned long  group_id;
    unsigned long  owner_id;
    char group_name[15];
} update_group_list_rep_t;

//修改密码
typedef     struct tag_change_passwd
{
    //用户的账号
    unsigned long account;
    //原始密码
    char origin_passwd[15];
    //新密码
    char     new_passwd[15];
} change_passwd_t;

//修改密码回应报文
typedef  struct tag_change_passwd_rep
{
    //修改成功
    //修改失败
    int ack;
} change_passwd_rep_t;


/*********************点对点聊天************/

//获取头像
typedef struct get_head
{
    unsigned long friend_account;
} get_head_num_t;

//获取头像应答
typedef struct get_head_num
{
    int  head_num;
} get_head_num_rep_t;

// 点对点聊天
typedef struct chat_p2p
{
    // 自己的ID
    unsigned long            user_id;
    //发起者的昵称
    char       asker_name[15];
    // 聊天对象的ID
    unsigned long            friend_id;
    // 聊天内容
    char           content[512];
} chat_p2p_t;

// 点对点聊天应答
typedef struct chat_p2p_rep
{
    // 0---对方不在线
    // 1---发送成功
    int ack;
} chat_p2p_rep_t;

//接收离线消息申请
typedef struct offline_message_ask
{
	unsigned long myaccount;
}offline_message_ask_t;

//离线消息
typedef struct offline_msg
{
	unsigned long  sender;
	unsigned long  recerver;
	char		content[512];
}offline_msg_t;

// 离线消息
typedef struct offline_msg_rep
{
	int ack;
      chat_p2p_t  p2p;
}offline_msg_rep_t;

/*********************对群的操作************/

//申请创建群
typedef struct  ask_for_creat_group
{
    //用户账号-->群主
    unsigned long  account;
    //群名
    char      group_name[15];
} ask_for_creat_group_t;

//创建群应答
typedef struct ask_for_creat_group_rep
{
    //群账号
    unsigned  long  group_account;
    // 0---创建失败
    // 1---创建成功
    int ack;
} ask_for_creat_group_rep_t;

//申请删除群
typedef struct  ask_for_del_group
{
    //用户账号-->群主
    unsigned long  account;
    //群账号
    unsigned long  group_account;
} ask_for_del_group_t;

//删除群应答
typedef struct ask_for_del_group_rep
{
    // 0---删除失败
    // 1---删除成功
    int ack;
} ask_for_del_group_rep_t;


//申请加入群
typedef struct  ask_for_join_group
{
    //群账号
    unsigned  long  group_account;
    //用户账号
    unsigned  long  user_account;
} ask_for_join_group_t;


//群主是否答应入群
typedef struct  join_group_ok_no
{
    //申请者的账号
    unsigned long    user_account;
    //申请加入的群账号
    unsigned long group_accound;
    //申请加入的群名
    char        group_name[15];
    //申请者的昵称
    char        asker_name[15];
} join_group_ok_no_t;

//加入群应答
typedef struct  ask_for_join_group_rep
{
    // 0---账号不存在
    // 1---拒绝申请
    // 2---申请成功
    int     ack;
    unsigned long group_account;
    unsigned long asker_account;
    char        group_name[15];
    char           asker_name[15];
} ask_for_join_group__rep_t;

//退出群组
typedef struct  exit_group
{
    //群账号
    unsigned long   group_account;
    //用户账号
    unsigned long user_account;
} exit_group_t;

//退出群组应答
typedef struct  exit_group_rep
{
    // 0---退出群成功
    // 1---退出群失败
    int ack;
} exit_group_rep_t;


//群聊
typedef struct tag_group_chat
{
    //群账号
    unsigned  long  group_account;
    //用户账号
    unsigned  long  user_account;
    //发送内容
    char        context[512];
} group_chat_t;

//群发的内容
typedef  struct group_chat_context
{
     //群账号
    unsigned  long  group_account;
    //群发的内容
    char   context[512];
    //发送者账号
    unsigned  long  sender_account;
    //发送者昵称
    char   sender_name[15];
} group_chat_context_t;




//文件下载请求
typedef struct file_download
{
    // 请求文件信息
    // 0--- 请求文件大小
    // 1--- 请求文件下载
    char filename[255];
    int  ack;
    int type;
} file_download_t;

//文件下载应答
typedef struct file_download_rep
{
    // 0 文件不存在
    // 1 返回文件大小
    // 2 下载中
    // 3 下载结束
    char file_content[512];
    int  ack;
    unsigned long  file_tota_size;
    unsigned long filesize;
    int type;
} file_download_rep_t;

// 文件上传请求
typedef struct file_upload
{
    //  0 -- 长传请求
    char       filename[255];
    int        ack;
    unsigned long  file_tota_size;
    int type;
} file_upload_t;

// 文件上传请求响应
typedef struct file_upload_rep
{
    // 1 -- 接受上传请求
    // 2 -- 接受完成
    //服务器拒绝上传
    int        ack;
	int type;
} file_upload_rep_t;

//开始上传
typedef struct file_uploading
{
    //  1 -- 上传中
    //  2 -- 上传结束
    char       file_content[512];
    int        ack;
	int type;
} file_uploading_t;

typedef  struct change_head_num
{
    int user_account;
    int head_num;
}change_head_num_t;
#endif
