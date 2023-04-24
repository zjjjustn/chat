#pragma once

struct conn_client_info
{
    const char ip[16];
    const int port;
    const int sockfd;
};
