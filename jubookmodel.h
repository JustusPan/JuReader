#ifndef JUBOOKMODEL_H
#define JUBOOKMODEL_H

#include <QString>
#include <QVector>
#include <QImageReader>
#include "jubookitem.h"

class JuBookModel
{
public:
    JuBookModel(const QString& fileName=QString(""));
    ~JuBookModel();

    QImage curPage();
    QImage prevPage();
    QImage nextPage();
    QImage pageOfIndex(int i);

private:
    void initBook(const QString& fileName);
    void genBookWithChildren(const QString& fileName);//depth 1
    void genBookWithSiblings(const QString& fileName);

    QVector<JuBookItem*> _pages;
    int _curPageNum;
    QImageReader _imageReader;

};

#endif // JUBOOKMODEL_H
