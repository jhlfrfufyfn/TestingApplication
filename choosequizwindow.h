#ifndef CHOOSEQUIZWINDOW_H
#define CHOOSEQUIZWINDOW_H

#include <QWidget>

namespace Ui {
class ChooseQuizWindow;
}

class ChooseQuizWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseQuizWindow(QWidget *parent = nullptr);
    ~ChooseQuizWindow();

private:
    Ui::ChooseQuizWindow *ui;
};

#endif // CHOOSEQUIZWINDOW_H
