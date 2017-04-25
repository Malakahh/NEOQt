#ifndef MESSAGEHELPER_H
#define MESSAGEHELPER_H

#include <QObject>
#include <queue>
#include <vector>
#include "boost/crc.hpp"
#include <algorithm>
#include <mutex>
#include <memory>
#include <QTimer>
#include <functional>
#include <iostream>

#include "blehelper.h"
#include "callbackitem.h"

class MessageHelper : public QObject
{
    Q_OBJECT

public:
    explicit MessageHelper(QObject *parent = 0);

    void writeMessage(std::vector<unsigned char>& cmd);
    void enqueueQuery(std::vector<unsigned char>& query, int bytesToWait, std::function<void (const std::vector<char>)>&);
    void enqueueQuery(std::vector<unsigned char>& query);
    void hookSignals();

    template<typename T> void clearQueue(std::queue<T>& q)
    {
        std::queue<T> empty;
        std::swap(q, empty);
    }

    mutable std::mutex queueGuard;
    std::queue<std::unique_ptr<CallbackItem>> callbacks;

    std::queue<unsigned char> readBuffer;
    bool running = false;

public slots:
    void onCharacteristicWritten(const QLowEnergyCharacteristic& characteristic, const QByteArray& data);
    void onCharacteristicRead(const QLowEnergyCharacteristic& characteristic, const QByteArray& data);
    void timeoutResponse();

private:
    void runNextCommand();

    void obtainResponse();
    bool validateResponse(std::vector<char>& msg, std::vector<char>& data);

    QTimer timeoutResponseTimer;
    void startTimeoutTimer();
};

#endif // MESSAGEHELPER_H
