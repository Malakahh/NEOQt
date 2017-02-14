#include "storagemodel.h"

#define SEPARATOR '|'

StorageModel::StorageModel(QObject *parent) : QObject(parent)
{
    this->loadData();
}

StorageModel& StorageModel::getInstance()
{
    static StorageModel instance;

    return instance;
}

QString StorageModel::getBLEDeviceName()
{
    return this->bleDeviceName;
}

void StorageModel::setBLEDeviceName(QString name)
{
    this->bleDeviceName = name;
    emit this->bleDeviceNameChanged();
    this->saveData();
}

QString StorageModel::getDealershipName()
{
    return this->dealershipName;
}

void StorageModel::setDealershipName(QString name)
{
    this->dealershipName = name;
    emit this->dealershipNameChanged();
    this->saveData();
}

QString StorageModel::getDealershipPhone()
{
    return this->dealershipPhone;
}

void StorageModel::setDealershipPhone(QString phone)
{
    this->dealershipPhone = phone;
    emit this->dealershipPhoneChanged();
    this->saveData();
}

QString StorageModel::getDealershipWebsite()
{
    return this->dealershipWebsite;
}

void StorageModel::setDealershipWebsite(QString website)
{
    this->dealershipWebsite = website;
    emit this->dealershipWebsiteChanged();
    this->saveData();
}

QVariant StorageModel::getAhPrev()
{
    return QVariant(this->AhPrev);
}

void StorageModel::setAhPrev(int Ah)
{
    this->AhPrev = Ah;
    emit this->AhPrevChanged();
    this->saveData();
}

void StorageModel::saveData()
{
    QString str(this->bleDeviceName + SEPARATOR +
                this->dealershipName + SEPARATOR +
                this->dealershipPhone + SEPARATOR +
                this->dealershipWebsite + SEPARATOR +
                this->AhPrev);

    std::vector<char> data;

    for (int i = 0; i < str.size(); i++)
    {
        data.push_back(str[i].toLatin1());
    }

    FileHelper& fh = FileHelper::getInstance();
    fh.saveDataFile(data);
}

void StorageModel::loadData()
{
    std::vector<char> data;

    FileHelper& fh = FileHelper::getInstance();
    fh.loadDataFile(data);

    QString str = QString::fromLocal8Bit(data.data(), data.size());

    QStringList list = str.split(SEPARATOR);

    qDebug() << "listSize: " << list.size();

    if (list.size() > 4)
    {
        this->bleDeviceName = list[0];
        this->dealershipName = list[1];
        this->dealershipPhone = list[2];
        this->dealershipWebsite = list[3];
        this->AhPrev = list[4].toInt();
    }
}
