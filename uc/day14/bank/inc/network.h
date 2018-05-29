#ifndef _NETWORK_H
#define _NETWORK_H
#include<sys/types.h>
//TCP服务器初始化
int init(unsigned short type);
//TCP服务器终结化
void deinit(int sockfd);
//TCP服务器接收交易请求
int rcvreq(int sockfd,void* req,size_t len);
//TCP服务器发送交易响应
int sndres(int connfd,const void* res,size_t len);
//TCP客户机发送交易请求
int sndreq(const char* server,unsigned short type,const void* req,size_t len);
//TCP客户机接收交易响应
int rcvres(int sockfd,void* res,size_t len);
#endif //_NETWORK_H