#ifndef FILEBROWSERMODEL_H
#define FILEBROWSERMODEL_H

#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QAbstractItemModel>
#include <QDataStream>

#include "filebrowserdata.h"
#include "chargermodel.h"

class FileHelper : public QObject
{
    Q_OBJECT

public:
    explicit FileHelper(QObject* parent = 0);
    FileHelper(FileHelper const&) = delete;

    static FileHelper& getInstance();

    Q_INVOKABLE QVariant getFiles(QString extensionFilter);

    void save(QString path, std::vector<char> data);
    void load(QString path, std::vector<char>& data);

    Q_INVOKABLE void saveLog(QString fileName);
    void loadProgram(QString fileName, std::vector<char>& data);

    void saveDataFile(std::vector<char> data);
    void loadDataFile(std::vector<char>& data);


    //Q_INVOKABLE void test(QString fileName);

    void operator=(FileHelper const&) = delete;

private:
    QDir userStorageDir;
    QDir dataStorageDir;
    QFileInfoList files;
};

#endif // FILEBROWSERMODEL_H
