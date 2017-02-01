#ifndef FILEBROWSERDATA_H
#define FILEBROWSERDATA_H

#include <QObject>

class FileBrowserData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString fileName MEMBER fileName)

public:
    explicit FileBrowserData(QString fname, QObject *parent = 0);

private:
    QString fileName;
};

#endif // FILEBROWSERDATA_H
