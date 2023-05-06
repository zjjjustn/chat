#pragma once 
#define USER_LOGIN 0x12
#define REGISTER 0x11
#define LOGIN_REPLAY 0x13
#define REGISTER_REPLAY 0x14

#define UPLINE_USERS 0x22

#define REGISTER_ERROR 0x44
#define REGISTER_SUCCESS 0x55

#define SUCCESS 1
#define ERROR -1

#define MSG_SEND 0x33
#define MSG_RECV 0x44 


//协议头
struct msg_header
{
    //消息起始标志SQJY
    unsigned char header[4];
    //具体请求服务器进行的操作
    unsigned short control_mask;
    //正文的长度
    unsigned int content_len;
    //保留位
    unsigned short reservert;
};

//注册正文结构体
struct user_struct
{
    unsigned char user_name[32];
    unsigned char pass_word[32];
};

struct server_replay
{
    unsigned char error_msg[1024];
    unsigned char code;
};


struct oline_user
{
    unsigned char user_names[1023][32];

    unsigned short count;
};

struct msg_define
{
    unsigned char user_name[1024];
    unsigned char msg[1024];
    int is_send_all;
};

struct file