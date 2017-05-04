#include "filehelper.h"

FileHelper::FileHelper(QObject* parent) : QObject(parent)
{
    #ifdef Q_OS_ANDROID
        this->userStorageDir.setPath(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).last());
    #endif
    
    #ifdef Q_OS_IOS
        this->userStorageDir.setPath(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).last());
    #endif

    qDebug() << "USER STORAGE DIR: " << this->userStorageDir.absolutePath();

    QString dataPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).last() + "/powercharge";
    this->dataStorageDir.mkpath(dataPath);
    this->dataStorageDir.setPath(dataPath);
}

FileHelper& FileHelper::getInstance()
{
    static FileHelper instance;

    return instance;
}

QVariant FileHelper::getFiles(QString extensionFilter)
{
    QList<QObject*> list;

    this->files = this->userStorageDir.entryInfoList(QDir::Files);

    for (QFileInfo& info : this->files)
    {
        qDebug() << info.fileName();
        if (extensionFilter == "" || info.suffix().toLower() == extensionFilter.toLower())
        {
            list.append(new FileBrowserData(info.fileName()));
        }
    }

    return QVariant::fromValue(list);
}


void FileHelper::save(QString path, std::vector<char> data)
{
    QFile f(path);
    f.open(QIODevice::WriteOnly);

    QDataStream ds(&f);
    ds.writeRawData(data.data(), data.size());

    f.flush();
    f.close();
}

void FileHelper::load(QString path, std::vector<char>& data)
{
    QFile f(path);
    f.open(QIODevice::ReadOnly);

    char d[f.size()];

    QDataStream ds(&f);
    ds.readRawData(d, f.size());
    f.close();

    data.assign(d, d + f.size());
}

void FileHelper::saveLog(QString fileName)
{
    if (fileName == "")
    {
        return;
    }

    std::vector<char> log = ChargerModel::getInstance().parseLog();

    QStringList fileNameSplit = fileName.split('.');
    if (fileNameSplit.size() < 2 || fileNameSplit.last() == "")
    {
        fileName.append(".csv");
    }

    QString path = this->userStorageDir.absolutePath() + "/" + fileName;

    this->save(path, log);
}

void FileHelper::loadProgram(QString fileName, std::vector<char>& data)
{
    QString path = this->userStorageDir.absolutePath() + "/" + fileName;

    this->load(path, data);
}

void FileHelper::saveDataFile(std::vector<char> data)
{
    QString path = this->dataStorageDir.absolutePath() + "/data.dat";

    this->save(path, data);
}

void FileHelper::loadDataFile(std::vector<char>& data)
{
    QString path = this->dataStorageDir.absolutePath() + "/data.dat";

    this->load(path, data);
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
