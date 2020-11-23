#include "mainwindow.h"
#include "userinfowindow.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
