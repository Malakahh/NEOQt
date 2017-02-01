#ifndef FILEPICKERDATA_H
#define FILEPICKERDATA_H

#include <QObject>

class FilePickerData : public QObject
{
    Q_OBJECT
public:
    explicit FilePickerData(QObject *parent = 0);

signals:

public slots:
};

#endif // FILEPICKERDATA_H