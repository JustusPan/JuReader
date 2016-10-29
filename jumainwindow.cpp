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
    qDebug()<<"load!";//debug
    JuBookModel * newModel = new JuBookModel(file);
    if (newModel->isEmpty()) {
        qDebug()<<"error:empty book!";//debug
        return false;
    } else {
        setModel(newModel);

        const QImage newImage = _model->curPage();
        if (newImage.isNull()) {
            QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                                            tr("Cannot load"));
            return false;
        }
        setImage(newImage);

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
    _imageLabel->resize(_imageLabel->pixmap()->size());
}

void JuMainWindow::open() {
    qDebug()<<"open!";//debug
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}

}

void JuMainWindow::createActions() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *_openAct = fileMenu->addAction(tr("&Open..."), this, &JuMainWindow::open);
    _openAct->setShortcut(QKeySequence::Open);
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
