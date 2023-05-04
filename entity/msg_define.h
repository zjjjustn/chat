#pragma once 
#define LOGIN 0x10
#define REGISTER 0x11
#define UPLINE_USERS 0x22

#define SUCCESS 1
#define WRONG -1


//协议头
struct msg_header
{
    unsigned char header[4];

    unsigned short control_mask;

    unsigned int content_len;

    unsigned short reservert;
};

struct user_struct
{
    unsigned char user_name[32];
    unsigned char pass_word[32];
};

struct server_replay
{
    unsigned char error_msg[1024];
    unsigned char error_code;
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