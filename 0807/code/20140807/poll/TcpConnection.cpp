#include "TcpConnection.h"
using namespace std;
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)


TcpConnection::TcpConnection(int sockfd)
    :sockfd_(sockfd),
     buffer_(sockfd)
{
}

TcpConnection::~TcpConnection()
{
    shutdown();
}
//主要进行了一些错误处理
ssize_t TcpConnection::readn(char *usrbuf, size_t n)
{
    int nread = buffer_.readn(usrbuf, n); 
    if(nread == -1)
        ERR_EXIT("readn");
    return nread;
}

ssize_t TcpConnection::readLine(char *usrbuf, size_t n)
{
    int nread = buffer_.readline(usrbuf, n);
    if(nread == -1)
        ERR_EXIT("readLine");
    return nread;
}


ssize_t TcpConnection::writen(const char *usrbuf, size_t n)
{
    int nwrite = buffer_.writen(usrbuf, n);
    if(nwrite == -1)
        ERR_EXIT("write");
    return nwrite;
}

//发送字符串string进行了包装,转化为c风格型字符串
void TcpConnection::sendString(const std::string &s)
{
    writen(s.c_str(), s.size());
}

//接收字符串进行包装,返回了string
std::string TcpConnection::receiveString()
{
    char buf[1024];
    readLine(buf, 1024);
    return std::string(buf);
}

void TcpConnection::shutdown()
{
    sockfd_.shutdownWrite();
}







