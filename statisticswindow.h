#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QWidget>
#include <QObject>
#include <QComboBox>
#include <QJsonDocument>
#include <QtCharts>

#include "constants.h"
#include "user.h"


namespace Ui {
class StatisticsWindow;
}

class StatisticsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsWindow(QWidget *parent = nullptr);
    ~StatisticsWindow();

public slots:
    void prepareStatisticsWindow();
    void userSelected(int index);

signals:
    void returnToMenuButtonPressed();

private:
    void createMotivationalReliefTableView();
    void createMotivationalReliefTableUserInfo(QJsonObject);
    void updateVisualData(QJsonObject);
    void clearGraphicsArea();
    void setCellText(int row, int col, const QString& str);
    int getCellValueInt(int row, int col);
    double getCellValueDouble(int row,int col);
    QChart* createMotProPerChart();
    QChart* createProInsConChart();
    QChart* createBarChart();
private:
    Ui::StatisticsWindow *ui;
};

#endif // STATISTICSWINDOW_H
