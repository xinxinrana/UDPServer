#ifndef ABSTRACTWGT_H
#define ABSTRACTWGT_H

#include <QWidget>
class AbstractWgt :public QWidget
{
    Q_OBJECT

public:

    explicit AbstractWgt(QObject* parent);
    QObject *QWidget;


};




#endif //ABSTRACTWGT_H
