#include "filehelper.h"

FileHelper::FileHelper(QObject* parent) : QObject(parent)
{
    #ifdef Q_OS_ANDROID
        this->dir.setCurrent(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).last());
    #endif
    
    #ifdef Q_OS_IOS
        this->dir.setCurrent(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).last());
    #endif
}

FileHelper& FileHelper::getInstance()
{
    static FileHelper instance;

    return instance;
}

QVariant FileHelper::getFiles()
{
    QList<QObject*> list;

    this->files = this->dir.entryInfoList(QDir::Files);

    for (QFileInfo& info : this->files)
    {
        qDebug() << info.fileName();
        list.append(new FileBrowserData(info.fileName()));
    }

    return QVariant::fromValue(list);
}

void FileHelper::save(QString fileName, const char* data, const unsigned int len)
{
    if (fileName == "")
    {
        return;
    }

    QStringList fileNameSplit = fileName.split('.');
    if (fileNameSplit.size() < 2 || fileNameSplit.last() != "")
    {
        fileName.append(".txt");
    }

    QString path = this->dir.absolutePath() + "/" + fileName;

    QFile f(path);
    f.open(QIODevice::WriteOnly);

    QDataStream ds(&f);
    //ds << data;

    ds.writeRawData(data, len);

    f.close();
}

void FileHelper::load(QString fileName, std::vector<char>& data)
{
    QFile f(this->dir.absolutePath() + "/" + fileName);
    f.open(QIODevice::ReadOnly);

    QDataStream ds(&f);

    char d[f.size()];

    ds.readRawData(d, f.size());
    f.close();

    data.assign(d, d + f.size());
}

/*
void FileHelper::test(QString fileName)
{
    const char data[] = {
        0x41, 0x42, 0x43,
        0x31, 0x32, 0x33
    };

    //Save Test
    //this->save(fileName, data, 6);


    //Load test
    char* data2;
    unsigned int len;
    this->load(fileName, data2, len);

    bool correct = true;

    for (int i = 0; i < len; i++)
    {
        if (data[i] != data2[1])
            correct = false;
    }

    qDebug() << "Arrays are equal: " << correct;
}
*/
