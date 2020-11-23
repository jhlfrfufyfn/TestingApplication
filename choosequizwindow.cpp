#include <QTreeWidgetItem>

#include "choosequizwindow.h"
#include "ui_choosequizwindow.h"

ChooseQuizWindow::ChooseQuizWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseQuizWindow)
{
    ui->setupUi(this);

    ui->takeTestButton->setEnabled(false);

    ui->treeWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("Тесты:");

    QTreeWidgetItem *item1 = new QTreeWidgetItem();
    item1->setText(0, "Мотивационный рельеф");
    ui->treeWidget->addTopLevelItem(item1);

    QTreeWidgetItem *item2 = new QTreeWidgetItem();
    item2->setText(0, "Тест Люшера");
    ui->treeWidget->addTopLevelItem(item2);

    connect(ui->treeWidget,&QTreeWidget::itemSelectionChanged, this, &ChooseQuizWindow::processQuizSelecting);
    connect(ui->backToMenuButton, &QPushButton::pressed, this, &ChooseQuizWindow::backToMenuButtonPressed);
    connect(ui->takeTestButton, &QPushButton::pressed, this, &ChooseQuizWindow::processQuizChoosing);
}

ChooseQuizWindow::~ChooseQuizWindow()
{
    delete ui;
}

void ChooseQuizWindow::processQuizSelecting()
{
    ui->takeTestButton->setEnabled(!ui->treeWidget->selectedItems().isEmpty());
}

void ChooseQuizWindow::processQuizChoosing()
{
    QTreeWidgetItem *selectedItem = ui->treeWidget->selectedItems()[0];
    int selectedIndex = ui->treeWidget->indexOfTopLevelItem(selectedItem);
    switch(selectedIndex){
        case 0:
            emit quizChosen(State::QUIZ_MOTIVATION_RELIEF);
            break;
        case 1:
            //emit quizChosen(State::LUSHER_QUIZ);
            break;
        default:
            break;
    }
}
