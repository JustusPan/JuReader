#ifndef JUBOOKITEM_H
#define JUBOOKITEM_H

#include <QString>

class JuBookItem
{
public:
    JuBookItem(const QString &fileName);

    const QString &dataPath();

private:
    QString _dataPath;
};

#endif // JUBOOKITEM_H
