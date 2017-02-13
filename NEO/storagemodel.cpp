#include "storagemodel.h"

#define SEPARATOR '|'

StorageModel::StorageModel(QObject *parent) : QObject(parent)
{
    this->loadData();
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

void StorageModel::setAhPrev(QVariant Ah)
{
    this->AhPrev = Ah.toInt();
    emit this->AhPrevChanged();
    this->saveData();
}

void StorageModel::saveData()
{
    QString str(this->dealershipName + SEPARATOR +
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

    QStringList list = str.split(SEPARATOR, QString::SkipEmptyParts);

    if (list.size() > 0)
    {
        this->dealershipName = list[0];
        this->dealershipPhone = list[1];
        this->dealershipWebsite = list[2];
        this->AhPrev = list[3].toInt();
    }
}
