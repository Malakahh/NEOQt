#ifndef BLECONTROLLER_H
#define BLECONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QLowEnergyController>
#include "bluetoothdevicedataobject.h"
#include <vector>

class BLEController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant devices READ getDevices NOTIFY onDevicesChanged)

public:
    explicit BLEController(QObject *parent = 0);
    ~BLEController();



    Q_INVOKABLE void setupBLE();
    Q_INVOKABLE void connect(int index);

    QVariant getDevices() const;
    void writeCharacteristic(QByteArray msg);

signals:
    void onDevicesChanged();

public slots:
    void addDevice(const QBluetoothDeviceInfo& device);
    void onConnected();
    void onServiceDiscovered(const QBluetoothUuid& gatt);
    void onStateChanged(QLowEnergyService::ServiceState newState);
    void onCharacteristicWritten(const QLowEnergyCharacteristic& characteristic, const QByteArray& data);
    void onCharacteristicRead(const QLowEnergyCharacteristic& characteristic, const QByteArray& data);

private:
    QBluetoothDeviceDiscoveryAgent* deviceDiscoveryAgent;
    QLowEnergyController* leController;

    QLowEnergyService* service;
    QLowEnergyCharacteristic writer, reader;

    std::vector<BluetoothDeviceDataObject*> devices;

};

#endif // BLECONTROLLER_H
