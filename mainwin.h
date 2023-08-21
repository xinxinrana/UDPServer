#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QNetworkDatagram>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWin; }
QT_END_NAMESPACE

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();

public slots:
    void udpSocketControl(bool isOpen);
    void sendUDPInfo();

protected slots:

    void readPendingDatagrams();


private:
    void init();
    void initUIConnect();
    void initUdpSocket();

    void processTheDatagram(const QNetworkDatagram &data);


private:
    Ui::MainWin *ui;

    QUdpSocket *mySocket = nullptr;
};
#endif // MAINWIN_H
