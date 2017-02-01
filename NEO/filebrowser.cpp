#include "filebrowser.h"

FileBrowser::FileBrowser(QObject* parent) : QObject(parent)
{    

    #ifdef Q_OS_ANDROID
        this->dir.setCurrent(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).last());
    #endif
    
    #ifdef Q_OS_IOS
        this->dir.setCurrent(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).last());
    #endif

    qDebug() << "path set: " << this->dir.absolutePath();
}

QVariant FileBrowser::getData()
{
    QList<QObject*> list;

    this->files = this->dir.entryInfoList(QDir::Files);

    for (QFileInfo& info : this->files)
    {
        qDebug() << info.baseName();
        list.append(new FileBrowserData(info.baseName()));
    }

    return QVariant::fromValue(list);
}

void FileBrowser::save(QString fileName, const char* data, const int size)
{

}

void FileBrowser::load(QString fileName)
{

}
