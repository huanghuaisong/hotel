package com.example.administrator.jaja;

/**
 * Created by Administrator on 2016/3/17.
 */
public enum  messageType{
        LOGIN,             //请求登陆
        LOGIN_SUCCESS,      //登陆成功1
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


        ADD_FRIEND,         //添加好友13
        DEL_FRIEND,         //删除好友
        ADD_IS_REJECT,      //添加被拒绝
        DEL_FRIEND_SUCCESS, //删除成功
        ADD_FRIEND_SUCCESS, //添加好友成功
        ALREADY_YOUR_FRIEND,//已经是您的好友18
        NOT_YOUR_FRIEND,    //不是您的好友
        AGREE_TO_ADD,       //同意添加
        DISAGREE_TO_ADD,    //拒绝添加
        ADD_FRIEND_REP,     //被申请者发给服务器

        JOIN_GROUP,           //加入群组23
        JOIN_GROUP_REP,           //加入群组回应
        FOR_ASKER_JOIN_GROUP_REP,//给申请加入群的用户的回复
        DELETE_GROUP,        //删除群组
        DELETE_GROUP_SUCCESS,//删除群组成功
        DELETE_GROUP_FAILURE, //删除群组失败
        GROUP_ACCOUNT_UNEXIST,//群账号不存在
        NOT_GROUP_OWNER,        //不是群主30
        EXIT_GROUP,         //退出群组
        ADD_GROUP_SUCCESS,   //加入群组成功
        ADD_GROUP_FAILURE,   //加入群组失败
        AGREE_ADD_GROUP_OR_NOT, //是否同意加入群
        AGREE_ADD_GROUP,        //群主同意申请
        EXIT_GROUP_SUCCESS,  //退出群成功
        EXIT_GROUP_FAILURE, //退出群失败37
        CREATE_GROUP,          //创建群
        CREATE_GROUP_SUCCESS,//创建群成功
        CREATE_GROUP_FAILURE,//创建群失败
        JOIN_GROUP_REJECTED, //被拒绝加入41

        DOWNLOAD_FILE,      //下载文件42
        UPLODE_FILE,        //上传文件
        DOWNLOAD_SUCCESS,   //下载成功
        ACCEPT_UPLOAD_FILE, //接收上传文件
        BEGIN_UPLOAD,         //开始上传
        UPLOAD_SUCCESS,     //上传成功
        FILE_NO_EXIST,      //文件不存在
        RETURN_FILE_SIZE,  //返回文件大小
        FILE_DOWNLOADING, //文件正在下载
        FILE_UPLOADING, //文件正在上传
        DOWNLOAD_FAILURE,   //下载失败
        UPLOAD_FAILURE,     //上传失败

        GET_FACE_PICTURE,   //接收表情53
        SEND_FACE_PICTUER,  //发送表情
        P_TO_P_CHAT,        //单聊
        P_TO_P_CHAT_REP,        //单聊失败的原因
        GROUP_CHAT,         //群聊天
        NOTIFY_STATE,       //更新状态
        UPDATE_FRIEND,      //更新好友
        USER_DISCONNECT, //用户要下线
        UPDATE_FRIEND_STATE, //更新好友的状态60

        INIT_FRIEND_LIST,  //初始化好友列表
        FIREND_INITING,   //好友列表正在初始化
        FRIEND_INITED,     //好友列表初始化完成

        INIT_GROUP_LIST,  //初始化群列表
        GROUP_INITING,    //群列表正在初始化
        GROUP_INITED,    //群列表初始化完成

        INIT_GROUP_MEMBER_LIST,  //初始化群列表
        GROUP_MEMBER_INITING,    //群列表正在初始化
        GROUP_MEMBER_INITED,    //群列表初始化完成

        UPDATING_FRIEND,  //正在更新好友
        UPDATED_FRIEND, //更新好友完毕

        UPDATED_GROUP_LIST,
        UPDATEING_GROUP,
        UPDATED_GROUP,

        GET_HEAD_NUM,  //获取用户头像
        OFFLINE_MSG_SEND,     //发送离线消息一层头
        SENDING_OFFLINE_MSG,   //ack = 正在发送
        SENDED_OFFLINE_MSG,  //ack = 发送完成
        CHANGE_HEAD_NUM,      //设置头像
        P_to_P_FILE,
        GROUP_FILE,
    }