#ifndef MESSAGEHELPER_H
#define MESSAGEHELPER_H

#include <QObject>
#include <queue>
#include <vector>
#include "blecontroller.h"
#include "boost/crc.hpp"
#include <algorithm>

class MessageHelper : public QObject
{
    Q_OBJECT

public:
    explicit MessageHelper(QObject *parent = 0);

    void writeMessage(std::vector<unsigned char>& cmd);

public slots:
    void onCharacteristicWritten(const QLowEnergyCharacteristic& characteristic, const QByteArray& data);
    void onCharacteristicRead(const QLowEnergyCharacteristic& characteristic, const QByteArray& data);

private:
    std::queue<unsigned char> readBuffer;
};

#endif // MESSAGEHELPER_H
