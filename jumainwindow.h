#ifndef JUMAINWINDOW_H
#define JUMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class JuMainWindow;
}

class JuMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JuMainWindow(QWidget *parent = 0);
    ~JuMainWindow();

private:
    Ui::JuMainWindow *ui;
};

#endif // JUMAINWINDOW_H
