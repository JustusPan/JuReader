#ifndef JUBOOKMODEL_H
#define JUBOOKMODEL_H

#include <QString>
#include <QVector>
#include <QImageReader>
#include <QDir>
#include "jubookitem.h"

class JuBookModel
{
public:
    JuBookModel(const QString& fileName=QString(""));
    ~JuBookModel();

    bool isEmpty();
    QImage curPage();
    QImage prevPage();
    QImage nextPage();
    QImage pageOfIndex(int i);

private:
    void initBook(const QString& fileName);
    void genBookWithChildren(const QString& fileName);//depth 1
    void genBookWithSiblings(const QString& fileName);

    QVector<JuBookItem*> _pages;
    int _curPageIndex;
    QImageReader _imageReader;

//public:
//    static bool isValidFormat(const QString& fileName);
//private:
//    static QList<QByteArray> s_validFormat;
};

#endif // JUBOOKMODEL_H
