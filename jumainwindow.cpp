#include <QScreen>
#include <QLabel>
#include <QScrollArea>
#include <QFiledialog>
#include <QStandardPaths>
#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>
#include <QDebug>
#include "jumainwindow.h"
#include "jubookmodel.h"
#include "ui_jumainwindow.h"

JuMainWindow::JuMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JuMainWindow),
    _model(0),
    _imageLabel(new QLabel),
    _scrollArea(new QScrollArea),
    _scaleFactor(1),
    _openAct(0)
{
    ui->setupUi(this);

    _imageLabel->setBackgroundRole(QPalette::Base);
    _imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    _imageLabel->setScaledContents(true);

    _scrollArea->setBackgroundRole(QPalette::Dark);
    _scrollArea->setWidget(_imageLabel);
    _scrollArea->setVisible(false);
    setCentralWidget(_scrollArea);

    createActions();
    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

JuMainWindow::~JuMainWindow()
{
    delete ui;
}

bool JuMainWindow::loadFile(const QString &file) {
    qDebug()<<"load!---------------------------";//debug
    qDebug()<<"file = "<<file;//debug
    JuBookModel * newModel = new JuBookModel(file);
    if (newModel->isEmpty()) {
        qDebug()<<"error:empty book!";//debug
        return false;
    } else {
        delete _model;
        _model = NULL;
        setModel(newModel);

        const QImage newImage = _model->curPage();
        if (newImage.isNull()) {
            QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                                            tr("Cannot load"));
            return false;
        }
        setImage(newImage);
        updateActions();

        this->setWindowFilePath(file);

        const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
            .arg(QDir::toNativeSeparators(file)).arg(_image.width()).arg(_image.height()).arg(_image.depth());
        statusBar()->showMessage(message);

        return true;
    }
}

void JuMainWindow::setImage(const QImage &newImage) {
    _image = newImage;
    _imageLabel->setPixmap(QPixmap::fromImage(_image));
    _scrollArea->setVisible(true);
    scaleImage(1);
    //_imageLabel->resize(_scaleFactor*_imageLabel->pixmap()->size());
}

void JuMainWindow::scaleImage(double factor) {
    _scaleFactor *= factor;
    _imageLabel->resize(_scaleFactor*_imageLabel->pixmap()->size());
    _zoomInAct->setEnabled(_scaleFactor < 3);
    _zoomOutAct->setEnabled(_scaleFactor > 0.5);
}

void JuMainWindow::open() {
    qDebug()<<"open!";//debug
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}

}

void JuMainWindow::nextPage() {
    qDebug()<<"next page!";//debug
    const QImage newImage = _model->nextPage();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                tr("Cannot load"));
        return;
    }
    setImage(newImage);
}

void JuMainWindow::prevPage() {
    qDebug()<<"prev page!";//debug
    const QImage newImage = _model->prevPage();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                tr("Cannot load"));
        return;
    }
    setImage(newImage);
}

void JuMainWindow::zoomIn() {
    qDebug()<<"zoomIn";//debug
    scaleImage(1.25);

}

void JuMainWindow::zoomOut() {
    qDebug()<<"zoomOut";//debug
    scaleImage(0.8);

}

void JuMainWindow::normalSize() {
    qDebug()<<"normalSize";//debug
    _scaleFactor=1;
    scaleImage(1);
}

void JuMainWindow::createActions() {
    //for file Menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *_openAct = fileMenu->addAction(tr("&Open..."), this, &JuMainWindow::open);
    _openAct->setShortcut(QKeySequence::Open);

    //for go Menu
    QMenu *goMenu = menuBar()->addMenu(tr("&Go"));
    _nextPageAct = goMenu->addAction(tr("&NextPage"), this, &JuMainWindow::nextPage);
    _nextPageAct->setShortcut(QKeySequence::MoveToNextChar);
    _nextPageAct->setEnabled(false);
    _prevPageAct = goMenu->addAction(tr("&PrevPage"), this, &JuMainWindow::prevPage);
    _prevPageAct->setShortcut(QKeySequence::MoveToPreviousChar);
    _prevPageAct->setEnabled(false);

    //for zoom Menu
    QMenu *zoomMenu = menuBar()->addMenu(tr("&Zoom"));
    _zoomInAct = zoomMenu->addAction(tr("Zoom &In"), this, &JuMainWindow::zoomIn);
    _zoomInAct->setShortcut(QKeySequence::ZoomIn);
    _zoomInAct->setEnabled(false);
    _zoomOutAct = zoomMenu->addAction(tr("Zoom &Out"), this, &JuMainWindow::zoomOut);
    _zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    _zoomOutAct->setEnabled(false);
    _normalSizeAct = zoomMenu->addAction(tr("&Normal Size"),this,&JuMainWindow::normalSize);
    _normalSizeAct->setShortcut(QKeySequence("Ctrl+N"));
    _normalSizeAct->setEnabled(false);

}

void JuMainWindow::updateActions() {
   _nextPageAct->setEnabled(!_image.isNull());
   _prevPageAct->setEnabled(!_image.isNull());
   _zoomInAct->setEnabled(!_image.isNull());
   _zoomOutAct->setEnabled(!_image.isNull());
   _normalSizeAct->setEnabled(!_image.isNull());
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}
