/*TcpServer    TcpClient
epoll + 线程池
好处：I/O代码和业务代码分开*/

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>
#include <string>
using namespace muduo;
using namespace muduo::net;
using namespace std;
using namespace placeholders;
/*
基于muduo网络库 1.组合TcpServer对象 2.创建EventLoop事件循环对象指针 3.确TcpServer构造函数需要什么参数，输出chatServer的构造函数 
4.当前服务器类的构造函数当中，注册处理连接的回调函数和处理读写事件的回调函数 5. 设置合适的服务端线程数量muduo库会自动划分io线程和worker线程
*/

class ChatServer
{
public://当创建ChatServer对象时，可以传入相应的参数，并初始化_server和_loop成员变量。
    ChatServer(EventLoop *loop,//事件循环
               const InetAddress &listenAddr,//ip+端口
               const string &nameArg) 
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        //给服务器注册用户连接的创建和断开回调
        _server.setConnectionCallback(std::bind(& ChatServer::onConnection, this, _1));
        //给服务器注册用户读写事件回调
        _server.setMessageCallback(std::bind(& ChatServer::onMessage, this, _1, _2, _3));
        //设置服务器端的线程数量
        _server.setThreadNum(4);
    }

    void start() {//开启事件循环
        _server.start();
    }

private:
    //专门处理用户的连接创建和断开  epoll listenfd accept
    void onConnection(const TcpConnectionPtr& conn) 
    {
        if (conn->connected())
        {
            cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << "state:online" << endl;
        }
        else
        {
            cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << "state:offline" << endl;
            conn->shutdown();
            //_loop.quit();
        }
    }   
    //专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn,//连接
                   Buffer *buffer,//缓冲区
                   Timestamp time)//接收数据的时间信息
    {
        string buf = buffer->retrieveAllAsString();
        cout << "recv data:" << buf << "time:" << time.toString() << endl;
        conn->send(buf);
    }

    TcpServer _server;
    EventLoop *_loop; // 2 epoll
};

int main() {
    EventLoop loop;
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");
    server.start();
    loop.loop();//epoll wait 以阻塞方式等待新用户链接，已连接的读写事件
    return 0;
}