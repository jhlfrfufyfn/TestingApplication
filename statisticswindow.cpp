#include "statisticswindow.h"
#include "ui_statisticswindow.h"

#include <QFile>


StatisticsWindow::StatisticsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);

    connect(ui->toMenuButton, &QPushButton::pressed, this, &StatisticsWindow::returnToMenuButtonPressed);
    connect(ui->userComboBox, QOverload<int>::of(&QComboBox::activated), this, &StatisticsWindow::userSelected);

    for(const auto& test: TEST_LIST){
        ui->testComboBox->addItem(test);
    }

}

StatisticsWindow::~StatisticsWindow()
{
    delete ui;
}

void StatisticsWindow::prepareStatisticsWindow()
{
    ui->userComboBox->clear();
    ui->userComboBox->addItems(User::getUserList());
    ui->userComboBox->setCurrentIndex(-1);
}

void StatisticsWindow::userSelected(int index)
{
    if(index == -1){
        return;
    }
    QString selectedUser = ui->userComboBox->itemText(index);

    QString dateStr = selectedUser.split(" \"").at(1);
    dateStr.remove(dateStr.size()-1, 1);
    QDate date = QDate::fromString(dateStr);
    QString fileName = "data/" + selectedUser.split(" ").at(0) + selectedUser.split(" ").at(1)+ selectedUser.split(" ").at(2)
            + QString::number(date.day()) + QString::number(date.month()) + QString::number(date.year())+".txt";

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray saveData = file.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    updateVisualData(json);

}

void StatisticsWindow::createMotivationalReliefTableView()
{
    ui->tableWidget->setColumnCount(15);
    ui->tableWidget->setRowCount(36);

    for(int i=0;i<ui->tableWidget->columnCount();i++){
        ui->tableWidget->setColumnWidth(i,30);
    }

    for(int i=0;i<ui->tableWidget->rowCount();i++){
        ui->tableWidget->setRowHeight(i,15);
    }

    ui->tableWidget->setColumnWidth(1, 270);

    setCellText(0,2,"Ц");
    setCellText(0,3,"Д");
    setCellText(0,4,"Δ");
    int rowCell = 1;
    int colCell = 0;

    for(int i=0;i<(int)QUIZ_VALUES_NAMES.size();i++){
        for(int j=0;j<(int)QUIZ_VALUES_NAMES[i].size();j++){
            setCellText(rowCell, colCell, QString::number(j+1));
            setCellText(rowCell, colCell + 1,QUIZ_VALUES_NAMES[i][j]);
            rowCell++;
        }
        rowCell+=2;
    }

    ui->tableWidget->setColumnWidth(7, 135);

    rowCell = 0;
    colCell = 7;

    setCellText(rowCell,colCell,"№ Цср");
    colCell++;
    setCellText(rowCell,colCell,"Цср");
    colCell++;
    setCellText(rowCell,colCell,"/Δ/‌‌‌ср");
    colCell++;
    setCellText(rowCell,colCell,"Δ‌‌‌ср*");
    colCell++;
    setCellText(rowCell,colCell,"Δ‌‌ср");

    rowCell = 1;
    colCell = 7;

    for(const auto& it: CATEGORY_NAMES){
        setCellText(rowCell,colCell,it);
        rowCell++;
    }

    rowCell = 9;
    colCell = 7;

    setCellText(rowCell, colCell, "Потребности");
    rowCell++;

    for(const auto& it: CATEGORY_NAMES){
        setCellText(rowCell,colCell,it);
        rowCell++;
    }

    rowCell = 9;
    colCell = 7;
    colCell++;

    setCellText(rowCell, colCell, "Ц");
    colCell++;
    setCellText(rowCell, colCell, "Δ");
    colCell++;
    setCellText(rowCell, colCell, "Ц'");
    colCell++;
    setCellText(rowCell, colCell, "Δ'");
    colCell++;
    setCellText(rowCell, colCell, "Ц''");
    colCell++;
    setCellText(rowCell, colCell, "Δ''");
    colCell++;


    ui->tableWidget->setColumnWidth(8, 75);
    ui->tableWidget->setColumnWidth(9, 75);
    ui->tableWidget->setColumnWidth(11, 75);
}


void StatisticsWindow::createMotivationalReliefTableUserInfo(QJsonObject json)
{
    QJsonObject resObject = json["mqResult"].toObject();
    QJsonArray valueArray = resObject["value"].toArray();
    QJsonArray accessArray = resObject["access"].toArray();
    int rowCell = 1;
    int colCell = 2;
    for(int i=0;i<(int)QUIZ_VALUES_NAMES.size();i++){
        QJsonObject modelV = valueArray.at(i).toObject();
        QJsonObject modelA = accessArray.at(i).toObject();
        for(int j=0;j<(int)QUIZ_VALUES_NAMES[i].size();j++){
            int value = modelV[QUIZ_VALUES_NAMES[i][j]].toInt();
            int access = modelA[QUIZ_VALUES_NAMES[i][j]].toInt();
            setCellText(rowCell, colCell, QString::number(value));
            setCellText(rowCell, colCell+1, QString::number(access));
            setCellText(rowCell, colCell+2, QString::number(value-access));
            rowCell++;
        }
        rowCell+=2;
    }

    int rowOrig = 1;
    int colOrig = 2;

    int rowCalc = 10;
    int colCalc = 8;

    for(int i=0;i<(int)QUIZ_VALUES_NAMES.size();i++){
        for(int j=0;j<(int)QUIZ_VALUES_NAMES[i].size();j++){
            int number = getCellValueInt(rowOrig, colOrig);
            setCellText(rowCalc, colCalc, QString::number(number));

            number = getCellValueInt(rowOrig, colOrig + 2);
            setCellText(rowCalc, colCalc+1, QString::number(number));
            rowCalc++;
            rowOrig++;
        }
        rowCalc = 10;
        rowOrig+=2;
        colCalc+=2;

        if(i == (int)QUIZ_VALUES_NAMES.size() - 2){
            break;
        }
    }


    rowOrig = 1;
    colOrig = 2;

    rowCalc = 1;
    colCalc = 8;

    for(int i=0;i<(int)QUIZ_VALUES_NAMES[0].size();i++){
        double number = (getCellValueInt(rowOrig, colOrig) + getCellValueInt(rowOrig+9, colOrig)+getCellValueInt(rowOrig+18, colOrig))/3.;
        setCellText(rowCalc, colCalc, QString::number(number));

        number = (std::abs(getCellValueInt(rowOrig, colOrig+2)) + std::abs(getCellValueInt(rowOrig+9, colOrig+2))+std::abs(getCellValueInt(rowOrig+18, colOrig+2)))/3.;
        setCellText(rowCalc, colCalc+1, QString::number(number));

        number = (getCellValueInt(rowOrig, colOrig+2) <= 0 && getCellValueInt(rowOrig+9, colOrig+2) <= 0 &&getCellValueInt(rowOrig+18, colOrig+2)<=0)
                ?(getCellValueInt(rowOrig, colOrig+2)+getCellValueInt(rowOrig+9, colOrig+2)+getCellValueInt(rowOrig+18, colOrig+2))
               :(0);
        setCellText(rowCalc, colCalc+2, QString::number(number));

        number = (getCellValueInt(rowOrig, colOrig+2) + getCellValueInt(rowOrig+9, colOrig+2)+getCellValueInt(rowOrig+18, colOrig+2))/3.;
        setCellText(rowCalc, colCalc+3,QString::number(number));

        rowCalc++;
        rowOrig++;
    }

    QtCharts::QChartView* chartView;

    chartView = new QChartView(createMotProPerChart());
    ui->verticalLayout->addWidget(chartView, 1);

    chartView = new QChartView(createBarChart());
    ui->verticalLayout->addWidget(chartView, 1);

}

void StatisticsWindow::updateVisualData(QJsonObject json)
{
    int testIndex = ui->testComboBox->currentIndex();
    clearGraphicsArea();
    switch(testIndex){
    case 0:
        createMotivationalReliefTableView();
        createMotivationalReliefTableUserInfo(json);
        break;
    case 1:

        break;
    }
}

void StatisticsWindow::clearGraphicsArea()
{
    QLayoutItem *child;
    while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
        delete child->widget(); // delete the widget
        delete child;   // delete the layout item
    }

}

void StatisticsWindow::setCellText(int row, int col, const QString &str)
{
    ui->tableWidget->setItem(row, col, new QTableWidgetItem(str));
}

int StatisticsWindow::getCellValueInt(int row, int col)
{
    return ui->tableWidget->item(row, col)->text().toInt();
}

double StatisticsWindow::getCellValueDouble(int row, int col)
{
    return ui->tableWidget->item(row, col)->text().toDouble();
}

QChart* StatisticsWindow::createMotProPerChart()
{
    QChart *chart = new QChart();
    chart->setTitle("Мотивационный профиль личности");

    QString name("Цср ");
    QLineSeries* lineseries = new QLineSeries();
    lineseries->setName(name);
    int rowCell = 1;
    int colCell = 8;
    for(int i=0;i<(int)QUIZ_VALUES_NAMES[0].size();i++){
        lineseries->append(i, getCellValueDouble(rowCell, colCell));
        rowCell++;
    }
    chart->addSeries(lineseries);

    name = "/Δ/‌‌‌ср";
    QLineSeries* lineseries2 = new QLineSeries();
    lineseries2->setName(name);
    rowCell = 1;
    colCell = 9;
    for(int i=0;i<(int)QUIZ_VALUES_NAMES[0].size();i++){
        lineseries2->append(i, getCellValueDouble(rowCell, colCell));
        rowCell++;
    }
    chart->addSeries(lineseries2);

    QStringList categories;
    for(const auto& it: CATEGORY_NAMES){
        categories<<it;
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    lineseries->attachAxis(axisX);
    lineseries2->attachAxis(axisX);
    axisX->setRange(QString(CATEGORY_NAMES[0]), QString(CATEGORY_NAMES[CATEGORY_NAMES.size()-1]));
    axisX->setLabelsFont(QFont("Roboto", 8));

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    lineseries->attachAxis(axisY);
    lineseries2->attachAxis(axisY);
    axisY->setRange(0,7);
    axisY->setTickType(QValueAxis::TicksDynamic);
    axisY->setTickInterval(0.5);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    return chart;
}

QChart *StatisticsWindow::createProInsConChart()
{
    QChart *chart = new QChart();

    chart->setTitle("Мотивационный профиль личности");

    QString name("/Δ/‌‌‌ср");
    QLineSeries* lineseries = new QLineSeries();
    lineseries->setName(name);
    int rowCell = 1;
    int colCell = 9;
    for(int i=0;i<(int)QUIZ_VALUES_NAMES[0].size();i++){
        lineseries->append(i, getCellValueDouble(rowCell, colCell));
        rowCell++;
    }
    chart->addSeries(lineseries);

    QStringList categories;
    for(const auto& it: CATEGORY_NAMES){
        categories<<it;
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    lineseries->attachAxis(axisX);
    axisX->setRange(QString(CATEGORY_NAMES[0]), QString(CATEGORY_NAMES[CATEGORY_NAMES.size()-1]));
    axisX->setLabelsFont(QFont("Roboto", 8));

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    lineseries->attachAxis(axisY);
    axisY->setRange(0,7);
    axisY->setTickType(QValueAxis::TicksDynamic);
    axisY->setTickInterval(0.5);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    return chart;
}

QChart *StatisticsWindow::createBarChart()
{
    QChart *chart = new QChart();
    chart->setTitle("Мотивационный профиль личности");

    QStringList categories;
    for(const auto& it: CATEGORY_NAMES){
        categories<<it;
    }

    const QVector<QString> BAR_NAMES = {"Ц","Δ","Ц'","Δ`","Ц''","Δ``"};
    QBarSeries *barseries = new QBarSeries;
    QVector<QBarSet*> barsets;
    for(int i=0;i<BAR_NAMES.size();i++){
        QBarSet *bs = new QBarSet(BAR_NAMES[i]);
        barsets.push_back(bs);
    }

    int rowCell = 10;
    int colCell = 8;
    for(int i=0;i<BAR_NAMES.size();i++){
        for(int j=0;j<(int)QUIZ_VALUES_NAMES[0].size();j++){
            *barsets[i]<<getCellValueInt(rowCell, colCell);
            rowCell++;
        }
        barseries->append(barsets[i]);
        rowCell = 10;
        colCell++;
    }
    chart->addSeries(barseries);


    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    barseries->attachAxis(axisX);
    axisX->setRange(QString(CATEGORY_NAMES[0]), QString(CATEGORY_NAMES[CATEGORY_NAMES.size()-1]));
    axisX->setLabelsFont(QFont("Roboto", 8));

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    barseries->attachAxis(axisY);
    axisY->setRange(-7,7);
    axisY->setTickType(QValueAxis::TicksDynamic);
    axisY->setTickInterval(1);

    return chart;
}
