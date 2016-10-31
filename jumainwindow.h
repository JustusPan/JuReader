#ifndef JUMAINWINDOW_H
#define JUMAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

class QLabel;
class QScrollArea;
class JuBookModel;
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
    void nextPage();
    void prevPage();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
private:
    Ui::JuMainWindow *ui;

    void setModel(JuBookModel *model) { _model = model;}
    void createActions();
    void initToolBar();
    void updateActions();
    //void createMenus();
    void setImage(const QImage &newImage);
    void scaleImage(double factor);

    JuBookModel *_model;

    QImage _image;
    QLabel *_imageLabel;
    QScrollArea *_scrollArea;
    double _scaleFactor;

    QAction *_openAct;

    QAction *_nextPageAct;
    QAction *_prevPageAct;

    QAction *_zoomInAct;
    QAction *_zoomOutAct;
    QAction *_normalSizeAct;
    QAction *_fitToWindowAct;

};

//static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);


#endif // JUMAINWINDOW_H
