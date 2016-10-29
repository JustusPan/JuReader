#include "jumainwindow.h"
#include "imageviewer.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JuMainWindow w;
    w.show();
    //ImageViewer* view = new ImageViewer;
    //view->show();
    qDebug()<<"main!";//debug


    return a.exec();
}
