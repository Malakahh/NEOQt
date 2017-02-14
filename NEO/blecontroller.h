#ifndef BLECONTROLLER_H
#define BLECONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QLowEnergyController>
#include <vector>

#include "bluetoothdevicedataobject.h"


class BLEController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant devices READ getDevices NOTIFY onDevicesChanged)

public:
    explicit BLEController(QObject *parent = 0);
    BLEController(BLEController const&) = delete;
    ~BLEController();

    static BLEController& getInstance();

    QLowEnergyService* service;

    Q_INVOKABLE void setupBLE();
    Q_INVOKABLE void connect(int index);
    void connect(const QBluetoothDeviceInfo& device);

    QVariant getDevices() const;
    void writeCharacteristic(QByteArray msg);
    bool isUUIDReader(QBluetoothUuid uuid);

    void operator=(BLEController const&) = delete;

signals:
    void onDevicesChanged();
    void connectionEstablished();

public slots:
    void addDevice(const QBluetoothDeviceInfo& device);
    void onConnected();
    void onServiceDiscovered(const QBluetoothUuid& gatt);
    void onStateChanged(QLowEnergyService::ServiceState newState);

private:
    QBluetoothDeviceDiscoveryAgent* deviceDiscoveryAgent;
    QLowEnergyController* leController;

    QLowEnergyCharacteristic writer, reader;

    std::vector<BluetoothDeviceDataObject*> devices;

};

#endif // BLECONTROLLER_H
