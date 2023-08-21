#include "receiverecodewgt.h"
#include "ui_receiverecodewgt.h"

#include <QDateTime>
#include <QFileDialog>
#include <windows.h>

ReceiveRecodeWgt::ReceiveRecodeWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReceiveRecodeWgt)
{
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);

    // 保存 清理
    connect(ui->btnSave,&QPushButton::clicked,this,&ReceiveRecodeWgt::saveRecode);
    connect(ui->btnClear,&QPushButton::clicked,this,&ReceiveRecodeWgt::clearRecede);
}

ReceiveRecodeWgt::~ReceiveRecodeWgt()
{
    delete ui;
}

void ReceiveRecodeWgt::recode(const QByteArray &data)
{
    auto time = QDateTime::currentDateTime().toString("mm:ss.zzz");


    ui->plainTextEdit->insertPlainText({"\n\n[--"+time+">>]"});
    ui->plainTextEdit->insertPlainText(data);
    ui->plainTextEdit->moveCursor(QTextCursor::Start);
}

void ReceiveRecodeWgt::saveRecode()
{
    auto url = QFileDialog::getSaveFileUrl(nullptr,tr("保存日志文件"),QUrl("C:"),tr("Log(*.txt)"));
//    if(url.isValid()){
//        return;
//    }

    QFile f(url.toLocalFile());
    f.open(QFileDevice::ReadWrite);
    if(f.isOpen()){
        f.write(ui->plainTextEdit->toPlainText().toLocal8Bit());
        f.close();
    }

    auto cmdStr = QString{"notepad.exe "+url.toLocalFile().toUtf8()}.toLocal8Bit();
    WinExec(cmdStr,SW_SHOW);

}

void ReceiveRecodeWgt::clearRecede()
{
    ui->plainTextEdit->clear();
}
