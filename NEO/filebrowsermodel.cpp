#include "filebrowsermodel.h"

FileBrowserModel::FileBrowserModel()
{

}

QVariant FileBrowserModel::data(const QModelIndex &index, int role) const
{
    return QString("test");
    //return QFileSystemModel::data(index, role);
}
