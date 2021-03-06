#ifndef STORAGEMODEL_H
#define STORAGEMODEL_H

#include <QObject>
#include "filehelper.h"

class StorageModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString bleDeviceName READ getBLEDeviceName WRITE setBLEDeviceName NOTIFY bleDeviceNameChanged)
    Q_PROPERTY(QString dealershipName READ getDealershipName WRITE setDealershipName NOTIFY dealershipNameChanged)
    Q_PROPERTY(QString dealershipPhone READ getDealershipPhone WRITE setDealershipPhone NOTIFY dealershipPhoneChanged)
    Q_PROPERTY(QString dealershipWebsite READ getDealershipWebsite WRITE setDealershipWebsite NOTIFY dealershipWebsiteChanged)
    Q_PROPERTY(QVariant AhPrev READ getAhPrev NOTIFY AhPrevChanged)
    
public:
    explicit StorageModel(QObject *parent = 0);
    StorageModel(StorageModel const&) = delete;

    static StorageModel& getInstance();

    Q_INVOKABLE QString getBLEDeviceName();
    Q_INVOKABLE void setBLEDeviceName(QString name);

    Q_INVOKABLE QString getDealershipName();
    Q_INVOKABLE void setDealershipName(QString name);

    Q_INVOKABLE QString getDealershipPhone();
    Q_INVOKABLE void setDealershipPhone(QString phone);

    Q_INVOKABLE QString getDealershipWebsite();
    Q_INVOKABLE void setDealershipWebsite(QString website);

    Q_INVOKABLE QVariant getAhPrev();
    void setAhPrev(double Ah);

signals:
    void bleDeviceNameChanged();
    void dealershipNameChanged();
    void dealershipPhoneChanged();
    void dealershipWebsiteChanged();
    void AhPrevChanged();

public slots:

private:
    QString bleDeviceName;
    QString dealershipName;
    QString dealershipPhone;
    QString dealershipWebsite;
    double AhPrev = 0;

    void saveData();
    void loadData();
};

#endif // STORAGEMODEL_H
