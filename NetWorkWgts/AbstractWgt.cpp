#include "AbstractWgt.h"

AbstractWgt::AbstractWgt(QObject* parent):QWidget(parent),ui(new Ui::AbstractWgt())
{
    ui->setup();
}
