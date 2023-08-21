#ifndef MAINWIN2_H
#define MAINWIN2_H

#include <QMainWindow>
#include <QUdpSocket>

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
    void initReceiveWin();

protected slots:
    void send();
    void setReceiveEnable(bool enable);
    void readPendingDatagrams();


private:
    Ui::MainWin2 *ui;

    QUdpSocket m_udpSendServer;
    QUdpSocket m_udpReceiveServer;
};

#endif // MAINWIN2_H
