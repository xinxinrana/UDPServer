#include "mainwin.h"
#include "mainwin2.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWin2 w;
    w.show();
    return a.exec();
}
