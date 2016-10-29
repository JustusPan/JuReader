#ifndef JUMAINWINDOW_H
#define JUMAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

class QLabel;
class QScrollArea;
namespace Ui {
class JuMainWindow;
}

class JuMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JuMainWindow(QWidget *parent = 0);
    ~JuMainWindow();

    bool loadFile(const QString &file);

private slots:
    void open();
private:
    Ui::JuMainWindow *ui;

    void createActions();
    //void createMenus();

    QLabel *_imageLabel;
    QScrollArea *_scrollArea;

    QAction *_openAct;

};

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);


#endif // JUMAINWINDOW_H
