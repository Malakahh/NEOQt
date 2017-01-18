#include "messagehelper.h"

#define START_BYTE '|'
#define CHECKSUM_LENGTH_BYTES 4
#define TIMEOUT 2000

MessageHelper::MessageHelper(QObject *parent) : QObject(parent)
{
    QObject::connect(&timeoutResponseTimer,
                     SIGNAL(timeout()),
                     this,
                     SLOT(timeoutResponse()));
}

void MessageHelper::hookSignals()
{
    QObject::connect(BLEController::getInstance().service,
                     SIGNAL(characteristicWritten(const QLowEnergyCharacteristic&, const QByteArray&)),
                     this,
                     SLOT(onCharacteristicWritten(const QLowEnergyCharacteristic&, const QByteArray&)));

    QObject::connect(BLEController::getInstance().service,
                     SIGNAL(characteristicChanged(const QLowEnergyCharacteristic&, const QByteArray&)),
                     this,
                     SLOT(onCharacteristicRead(const QLowEnergyCharacteristic&, const QByteArray&)));
}

void MessageHelper::writeMessage(std::vector<unsigned char>& cmd)
{
    char msg[cmd.size() + 2 + CHECKSUM_LENGTH_BYTES];

    msg[0] = START_BYTE;
    msg[1] = cmd.size();

    boost::crc_32_type crc;
    crc = std::for_each(cmd.begin(), cmd.end(), crc);
    int32_t checksum = crc();

    for (int i = 0; i < CHECKSUM_LENGTH_BYTES; i++)
    {
        msg[2 + i] = (unsigned char)(checksum >> (CHECKSUM_LENGTH_BYTES - 1 - i) * 8);
    }

    for (int i = 0; i < cmd.size(); i++)
    {
        msg[2 + CHECKSUM_LENGTH_BYTES + i] = cmd[i];
    }

    BLEController::getInstance().writeCharacteristic(QByteArray::fromRawData(msg, cmd.size() + 2 + CHECKSUM_LENGTH_BYTES));
}

void MessageHelper::onCharacteristicWritten(const QLowEnergyCharacteristic& characteristic, const QByteArray& data)
{
    qDebug() << "Data written: " << data;
}

void MessageHelper::onCharacteristicRead(const QLowEnergyCharacteristic& characteristic, const QByteArray& data)
{
    std::lock_guard<std::mutex>(this->queueGuard);
    if (BLEController::getInstance().isUUIDReader(characteristic.uuid()) && !callbacks.empty())
    {
        for (const char& byte : data)
        {
            readBuffer.push(byte);

            qDebug() << std::hex << (int)byte;
        }

        obtainResponse();
    }
}

void MessageHelper::enqueueQuery(std::vector<unsigned char>& query, int bytesToWait, std::function<void (const std::vector<char>)>& callback)
{
    //We expect a checksum
    if (bytesToWait > 0)
    {
        bytesToWait += CHECKSUM_LENGTH_BYTES * bytesToWait;
    }

    //We always expect at least an OK from the PIC checksum comparison
    bytesToWait++;

    std::lock_guard<std::mutex>(this->queueGuard);
    callbacks.push(std::unique_ptr<CallbackItem>(new CallbackItem(query, bytesToWait, callback)));

    runNextCommand();
}

void MessageHelper::enqueueQuery(std::vector<unsigned char>& query)
{
    std::function<void (const std::vector<char>)> tmp;
    this->enqueueQuery(query, 0, tmp);
}

void MessageHelper::runNextCommand()
{
    std::lock_guard<std::mutex>(this->queueGuard);
    qDebug() << (callbacks.empty() ? "callbacks is empty" : "callbacks is NOT empty");

    if (!running && !callbacks.empty())
    {
        running = true;

        if (callbacks.front()->bytesToRead > 0)
        {
            writeMessage(callbacks.front()->query);

            startTimeoutTimer();
        }
    }
}

void MessageHelper::startTimeoutTimer()
{
    timeoutResponseTimer.stop();
    timeoutResponseTimer.setSingleShot(true);

    std::lock_guard<std::mutex>(this->queueGuard);
    if (!callbacks.empty())
    {
        timeoutResponseTimer.start(TIMEOUT);
    }
}

void MessageHelper::timeoutResponse()
{
    running = false;

    qDebug() << "Timeout!";

    clearQueue(readBuffer);
    runNextCommand();
}

void MessageHelper::obtainResponse()
{
    std::lock_guard<std::mutex>(this->queueGuard);
    if (running && !callbacks.empty() && readBuffer.size() >= callbacks.front()->bytesToRead)
    {
        timeoutResponseTimer.stop();

        CallbackItem callbackItem = *callbacks.front();
        std::vector<char> msg;

        for (int i = 0; i < callbackItem.bytesToRead; i++)
        {
            msg.push_back(readBuffer.front());
            readBuffer.pop();
        }

        std::vector<char> data;

        if (validateResponse(msg, data))
        {
            if (callbackItem.callback != nullptr)
            {
                callbackItem.callback(data);
            }

            callbacks.pop();
            qDebug() << "Validated successfully";
        }
        else
        {
            clearQueue(readBuffer);
            qDebug() << "Validate FALSE!";
        }

        running = false;
        runNextCommand();
    }
}

bool MessageHelper::validateResponse(std::vector<char>& msg, std::vector<char>& data)
{
    //Validate PIC checksum response byte
    if (msg[0] != START_BYTE)
    {
        return false;
    }

    //Validate checksums
    for (int i = 1; i < msg.size(); i += 5)
    {
        int32_t checksum = 0;

        for (int k = 0; k < CHECKSUM_LENGTH_BYTES; k++)
        {
            checksum |= ((int32_t)msg[i + k] & 0xFF) << (8 * (CHECKSUM_LENGTH_BYTES - 1 - k));
        }

        boost::crc_32_type crc;
        crc.process_byte(msg[i + 4]);

        if (crc() != checksum)
        {
            return false;
        }

        data.push_back(msg[i + 4]);
    }

    return true;
}
