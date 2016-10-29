#include "jumainwindow.h"
#include "ui_jumainwindow.h"

JuMainWindow::JuMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JuMainWindow)
{
    ui->setupUi(this);
}

JuMainWindow::~JuMainWindow()
{
    delete ui;
}
