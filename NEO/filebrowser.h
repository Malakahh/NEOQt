#ifndef FILEBROWSERMODEL_H
#define FILEBROWSERMODEL_H

#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QAbstractItemModel>
#include "filebrowserdata.h"

class FileBrowser : public QObject
{
    Q_OBJECT

public:
    explicit FileBrowser(QObject* parent = 0);

    Q_INVOKABLE QVariant getData();

    void save(QString fileName, const char* data, const int size);
    void load(QString fileName);

private:
    QDir dir;
    QFileInfoList files;
};

#endif // FILEBROWSERMODEL_H
