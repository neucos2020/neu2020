#include "mainwindow.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <QApplication>
int main(int argc, char *argv[])
{
QApplication a(argc, argv);
    MainWindow w;
    w.show();
   return a.exec();
   /* lms ls;
    ls.print();
    ls.imwrite(ls,"./debug/file.dat");
    ls.print();*/
/*
    lms ls;
    ls.shellsort(ls.base,ls.length,3);
    ls.print();*/
}
