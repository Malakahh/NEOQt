#include "messagehelper.h"

#define START_BYTE '|'
#define CHECKSUM_LENGTH_BYTES 4

MessageHelper::MessageHelper(QObject *parent) : QObject(parent)
{
    QObject::connect(BLEController::getInstance().service,
                     SIGNAL(characteristicWritten(const QLowEnergyCharacteristic&, const QByteArray&)),
                     this,
                     SLOT(onCharacteristicWritten(const QLowEnergyCharacteristic&, const QByteArray&)));

    QObject::connect(BLEController::getInstance().service,
                     SIGNAL(characteristicRead(const QLowEnergyCharacteristic&, const QByteArray&)),
                     this,
                     SLOT(onCharacteristicRead(const QLowEnergyCharacteristic&, const QByteArray&)));
}

void MessageHelper::writeMessage(std::vector<unsigned char>& cmd)
{
    unsigned char msg[cmd.size() + 2 + CHECKSUM_LENGTH_BYTES];

    msg[0] = START_BYTE;
    msg[1] = cmd.size();

    boost::crc_32_type crc;
    crc = std::for_each(cmd.begin(), cmd.end(), crc);
    int32_t checksum = crc();


}

void MessageHelper::onCharacteristicWritten(const QLowEnergyCharacteristic& characteristic, const QByteArray& data)
{
    qDebug() << "Data written: " << data;
}

void MessageHelper::onCharacteristicRead(const QLowEnergyCharacteristic& characteristic, const QByteArray& data)
{
    if (BLEController::getInstance().isUUIDReader(characteristic.uuid()))
    {
        for (auto itr = data.cbegin(); itr < data.cend(); itr++)
        {
            readBuffer.push(*itr);
        }
    }
}
