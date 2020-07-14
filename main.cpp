#include "mainwindow.h"
#include <QApplication>
#include "lms.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    lms s;
  //  s.print();
//s.~lms();
    return a.exec();
}
