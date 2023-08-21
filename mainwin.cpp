#include "mainwin.h"
#include "./ui_mainwin.h"

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    ui->setupUi(this);
    init();
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::udpSocketControl(bool isOpen)
{
    if(mySocket){
        if(isOpen){
//            mySocket->bind(QHostAddress::Broadcast,9090);
            if(!mySocket->bind(QHostAddress::Any,5555)){
    qDebug()<<"UDPSocket bind failed [id]:" << mySocket->errorString();
            }else{
    qDebug()<<"UDPSocket bind successful";

            }
        }else{
            mySocket->abort();
        }
    }
}

static int staI = 0;
void MainWin::sendUDPInfo()
{
    ++staI;
    auto udpSocket = new QUdpSocket(this);
    QString str = "hello :";
    str = str+ QVariant(staI).toString();
//    if(!udpSocket->writeDatagram(str.toUtf8(),QHostAddress::Broadcast,5555)){
//        qDebug()<<udpSocket->error();
//    }

//    auto hostAddress = QHostAddress::Broadcast;
    auto hostAddress = QHostAddress{"192.168.0.106"};
    if(!udpSocket->writeDatagram(str.toUtf8(),hostAddress,5555)){
        qDebug()<<udpSocket->error();
    }else{
        qDebug()<<"send :"<<str<<"is OK";
    }
}

void MainWin::readPendingDatagrams()
{
    while (mySocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = mySocket->receiveDatagram();
        processTheDatagram(datagram);
    }
}

void MainWin::init()
{
    initUdpSocket();

    initUIConnect();
}

void MainWin::initUIConnect()
{
    connect(ui->btnOpenUDP,&QPushButton::clicked,this,&MainWin::udpSocketControl);
    connect(ui->btnSendUDP,&QPushButton::clicked,this,&MainWin::sendUDPInfo);
}

void MainWin::initUdpSocket()
{
    mySocket =  new QUdpSocket(this);
    connect(mySocket,&QUdpSocket::readyRead,this,&MainWin::readPendingDatagrams);
}

void MainWin::processTheDatagram(const QNetworkDatagram &data){


    auto address = data.senderAddress().toString();
    auto port = QVariant(data.senderPort()).toString();
    auto str = (QString)data.data();

    auto desAddress = data.destinationAddress().toString();
    auto desPort = QVariant(data.destinationPort()).toString();
    str = str + "\n address:";
    str = str + address;
    str = str + "\n port:";
    str = str + port;

    str = str + "\n desAddress:";
    str = str + desAddress;
    str = str + "\n desPort:";
    str = str + desPort;

    ui->label->setText(str);
    qDebug() << address;
}

