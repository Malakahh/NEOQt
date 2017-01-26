#ifndef FILEBROWSERMODEL_H
#define FILEBROWSERMODEL_H

#include <QFileSystemModel>
#include <QDebug>

class FileBrowserModel : public QFileSystemModel
{
public:
    FileBrowserModel();
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // FILEBROWSERMODEL_H
