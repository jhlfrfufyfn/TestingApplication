#ifndef ENDQUIZWINDOW_H
#define ENDQUIZWINDOW_H

#include <QWidget>

namespace Ui {
class EndQuizWindow;
}

class EndQuizWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EndQuizWindow(QWidget *parent = nullptr);
    ~EndQuizWindow();

signals:
    void returnToMenuButtonPressed();

private:
    Ui::EndQuizWindow *ui;
};

#endif // ENDQUIZWINDOW_H
