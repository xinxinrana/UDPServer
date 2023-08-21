#include "myudpserver.h"

MyUDPServer::MyUDPServer(const int &port,QObject *parent)
    : QUdpSocket{parent}
{
//    port = port;
}
