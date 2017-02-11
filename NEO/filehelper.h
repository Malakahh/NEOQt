#ifndef FILEBROWSERMODEL_H
#define FILEBROWSERMODEL_H

#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QAbstractItemModel>
#include <QDataStream>

#include "filebrowserdata.h"

class FileHelper : public QObject
{
    Q_OBJECT

public:
    explicit FileHelper(QObject* parent = 0);
    FileHelper(FileHelper const&) = delete;

    static FileHelper& getInstance();

    Q_INVOKABLE QVariant getFiles();

    void save(QString fileName, const char* data, const unsigned int len);
    void load(QString fileName, std::vector<char>& data);

    //Q_INVOKABLE void test(QString fileName);

    void operator=(FileHelper const&) = delete;

private:
    QDir dir;
    QFileInfoList files;
};

#endif // FILEBROWSERMODEL_H
