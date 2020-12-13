#include "testapplication.h"
#include "userinfowindow.h"
#include "statisticswindow.h"
#include "itoquizwindow.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestApplication w;
    w.show();

    return a.exec();
}
