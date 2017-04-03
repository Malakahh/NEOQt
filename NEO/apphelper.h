#ifndef APPHELPER_H
#define APPHELPER_H

#include <QObject>

class AppHelper : public QObject
{
    Q_OBJECT
public:
    explicit AppHelper(QObject *parent = 0);

    Q_INVOKABLE void exit();

signals:

public slots:
};

#endif // APPHELPER_H
