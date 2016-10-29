#include "jumainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JuMainWindow w;
    w.show();

    return a.exec();
}
