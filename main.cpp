#include "mainwindow.h"
#include "mywindow.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyWindow *window = new MyWindow;
    window->show();

    Interface *inter = new Interface;
    QObject::connect(window, SIGNAL(Sig(QString)), inter, SLOT(Message(QString)));

    return a.exec();
}
