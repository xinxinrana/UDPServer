#ifndef MYUDPSERVER_H
#define MYUDPSERVER_H

#include <QNetworkDatagram>
#include <QUdpSocket>

class MyUDPServer : public QUdpSocket
{
    Q_OBJECT
public:
    explicit MyUDPServer(const int &port = 5555,QObject *parent = nullptr);

    bool send(const QString &str,const QHostAddress& host);
    bool ListeningPortControl(const bool &setStatus);

signals:


private:
    int m_port = 5555;


};

#endif // MYUDPSERVER_H
