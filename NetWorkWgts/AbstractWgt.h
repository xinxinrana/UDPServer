#ifndef ABSTRACTWGT_H
#define ABSTRACTWGT_H

namespace Ui {
class AbstractWgt;
}

#include <QWidget>
class AbstractWgt :public QWidget
{
    Q_OBJECT

public:

    explicit AbstractWgt(QObject* parent);
    QObject *QWidget;

    Ui::AbstractWgt* ui;
};




#endif //ABSTRACTWGT_H
