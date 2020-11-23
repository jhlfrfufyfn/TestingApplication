#include "menuwindow.h"
#include "ui_menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);

    connect(ui->changeUserButton, &QPushButton::pressed, this, &MenuWindow::changeUserButtonPressed);
    connect(ui->quitButton, &QPushButton::pressed, this, &MenuWindow::quitButtonPressed);
    connect(ui->completeTestButton, &QPushButton::pressed, this, &MenuWindow::testButtonPressed);
    connect(ui->openStatisticsButton, &QPushButton::pressed, this, &MenuWindow::statButtonPressed);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}
