#ifndef LOGHEADER_H
#define LOGHEADER_H

#include <QObject>
#include <QVariant>

class LogHeader : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant size READ getSize)

public:
    explicit LogHeader(QObject *parent = 0);
    LogHeader(const LogHeader& header);

    QVariant getSize() const;

    int size = 0;
    int address = 0;

signals:

public slots:
};

#endif // LOGHEADER_H
