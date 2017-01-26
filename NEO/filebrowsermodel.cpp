#include "filebrowsermodel.h"
#include <QStandardPaths>

FileBrowserModel::FileBrowserModel()
{
    setRootPath(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).last());

    for (int i = 0; i < rowCount(); i++)
    {
        const int k = i;

        qDebug() << "eh" << this->fileName(k);
    }
}

QVariant FileBrowserModel::data(const QModelIndex &index, int role) const
{
    return QFileSystemModel::data(index, role);
}
