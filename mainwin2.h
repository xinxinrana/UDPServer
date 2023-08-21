#ifndef MAINWIN2_H
#define MAINWIN2_H

#include <QMainWindow>
#include <QUdpSocket>

class ReceiveRecodeWgt;
namespace Ui {
class MainWin2;
}

class MainWin2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWin2(QWidget *parent = nullptr);
    ~MainWin2();

private:
    void processTheDatagram(const QNetworkDatagram &data);



    void init();
    void initUI();
    void initLogger();
    void initReceiveWin();

protected slots:
    void send();
    void setReceiveEnable(bool enable);
    void setRecodeWgtShow(bool isShow);
    void readPendingDatagrams();


private:
    Ui::MainWin2 *ui;
    ReceiveRecodeWgt *m_recodeWgr;

    QUdpSocket m_udpSendServer;
    QUdpSocket m_udpReceiveServer;
    int m_defenePort = 9090;
};

#endif // MAINWIN2_H
