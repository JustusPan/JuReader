#include "jubookitem.h"

JuBookItem::JuBookItem(const QString &fileName):
    _dataPath(fileName)
{
}

const QString &JuBookItem::dataPath() {
    return _dataPath;
}
