#ifndef RECEIVERECODEWGT_H
#define RECEIVERECODEWGT_H

#include <QWidget>

namespace Ui {
class ReceiveRecodeWgt;
}

class ReceiveRecodeWgt : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiveRecodeWgt(QWidget *parent = nullptr);
    ~ReceiveRecodeWgt();

    void recode(const QByteArray& data);

private slots:
    void saveRecode();
    void clearRecede();

private:
    Ui::ReceiveRecodeWgt *ui;


};

#endif // RECEIVERECODEWGT_H
