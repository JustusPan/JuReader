#include <QFileInfo>
#include "jubookmodel.h"

//QList<QByteArray> JuBookModel::s_validFormat=QImageReader::supportedImageFormats();
//
//bool JuBookModel::isValidFormat(const QString& fileName) {
//}

JuBookModel::JuBookModel(const QString& fileName) :
    _curPageIndex(-1)
{
    initBook(fileName);
}

JuBookModel::~JuBookModel() {
    QVector<JuBookItem*>::iterator it;
    for (it=_pages.begin();it!=_pages.end();++it) {
        delete *it;
    }
    _pages.clear();//do not need swap with empty vector, which is different with std::vector,?
}

bool JuBookModel::isEmpty() {
    return _pages.isEmpty();
}

QImage JuBookModel::curPage() {
    if (this->isEmpty()) return QImage();
    if (_curPageIndex == -1) ++_curPageIndex;
    return pageOfIndex(_curPageIndex);
}

QImage JuBookModel::prevPage() {
    if (_curPageIndex>0) {
        --_curPageIndex;
        return curPage();
    } else {
        return QImage();
    }
}

QImage JuBookModel::nextPage() {
    if (_curPageIndex<_pages.size()-1) {
        ++_curPageIndex;
        return curPage();
    } else {
        return QImage();
    }
}

QImage JuBookModel::pageOfIndex(int i) {
    if (i>=0 && i<=_pages.size()-1) {
        _imageReader.setFileName(_pages[i]->dataPath());
        return _imageReader.read();
    } else {
        return QImage();
    }
}

void JuBookModel::initBook(const QString& fileName) {
    if (fileName.isEmpty()) return;

    QFileInfo fInfo(fileName);
    if (fInfo.isDir()) {
        genBookWithChildren(fileName);
    } else {
        genBookWithSiblings(fileName);
    }
}

void JuBookModel::genBookWithChildren(const QString& fileName) {
    QDir dir(fileName);
    QFileInfoList entryList = dir.entryInfoList();
    for (int i=0;i<entryList.size();++i) {
        _imageReader.setFileName(entryList[i].absoluteFilePath());
        if (_imageReader.canRead()) {
            JuBookItem *curItem = new JuBookItem(entryList[i].absoluteFilePath());
            _pages.push_back(curItem);
        }
    }
}

void JuBookModel::genBookWithSiblings(const QString& fileName) {
    QStringList pathList = fileName.split(QDir::separator());
    pathList.removeLast();
    QString parentPath = pathList.join(QString(QDir::separator()));
    this->genBookWithChildren(parentPath);
}
