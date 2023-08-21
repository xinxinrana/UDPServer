#include "mainwin2.h"
#include "qnetworkdatagram.h"
#include "ui_mainwin2.h"

#include <QDateTime>

MainWin2::MainWin2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWin2)
{
    ui->setupUi(this);

    init();
}

MainWin2::~MainWin2()
{
    delete ui;
    if(m_udpSendServer.isOpen()){
        m_udpSendServer.aboutToClose();
    }

    if(m_udpReceiveServer.isOpen()){
        m_udpReceiveServer.aboutToClose();
    }
}

void MainWin2::processTheDatagram(const QNetworkDatagram &data)
{
    auto sendAddress = data.senderAddress().toString();
    auto strData = data.data();

    ui->LEditReceiveAddress->setText(sendAddress);
    ui->TEditReceive->setPlainText(strData);
}

void MainWin2::init()
{
    initUI();
    initReceiveWin();
}

void MainWin2::initUI()
{
    this->resize(1000,600);
    this->setWindowTitle(tr("UDP发送接收测试工具"));
    this->setWindowIcon(QIcon(":/bm_10.png"));

    ui->checkTimeStamp->setChecked(true);
    connect(ui->btnSend,&QPushButton::clicked,this,&MainWin2::send);
}

void MainWin2::initReceiveWin()
{
    ui->btnReceiveEnable->setCheckable(true);
    ui->LEditReceiveAddress->setEnabled(false);

//    ui->TEditReceive->setEnabled(false);

    connect(ui->btnReceiveEnable,&QPushButton::clicked,this,&MainWin2::setReceiveEnable);
    connect(ui->LEditReceivePort,&QLineEdit::textChanged,[=](){
        this->ui->btnReceiveEnable->setChecked(false);
    });
    connect(&m_udpReceiveServer,&QUdpSocket::readyRead,this,&MainWin2::readPendingDatagrams);
}

void MainWin2::send()
{
    auto data = ui->TEditSend->toPlainText();
    if(ui->checkTimeStamp->isChecked()){
        data.append("\n\n --");
        data.append(QDateTime::currentDateTime().toLocalTime().toString("yyyy.MM.dd  :  hh.mm.ss.zzz"));
    }

    auto address = ui->LEditSendAddress->text().isEmpty() == true ?QHostAddress::Broadcast:QHostAddress{ui->LEditSendAddress->text()};
    auto port = ui->LEditSendPort->text().toInt();



    m_udpSendServer.writeDatagram(data.toUtf8(),address,port);
}

void MainWin2::setReceiveEnable(bool enable)
{
    auto port = ui->LEditReceivePort->text().toInt();

    if(enable){
        if(m_udpReceiveServer.state() == QUdpSocket::UnconnectedState){
            ui->btnReceiveEnable->setText(tr("关闭端口监听"));
            m_udpReceiveServer.bind(QHostAddress::Any,port);
        }
    }else{
        if(m_udpReceiveServer.state() != QUdpSocket::UnconnectedState){
            m_udpReceiveServer.abort();
        }
        ui->btnReceiveEnable->setText(tr("开启端口监听"));
    }
}


void MainWin2::readPendingDatagrams()
{
    while (m_udpReceiveServer.hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_udpReceiveServer.receiveDatagram();
        processTheDatagram(datagram);
    }
}
