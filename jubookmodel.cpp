#include "jubookmodel.h"

JuBookModel::JuBookModel(const QString& fileName) :
    _curPageNum(-1)
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

void JuBookModel::initBook(const QString& fileName) {
    if (fileName.isEmpty()) return;




}
