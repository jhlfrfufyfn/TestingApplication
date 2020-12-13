#pragma once

#include <QWidget>

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

signals:
    void changeUserButtonPressed();
    void quitButtonPressed();
    void testButtonPressed();
    void statButtonPressed();

private:
    Ui::MenuWindow *ui;
};
