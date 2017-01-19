#ifndef BLUETOOTHCONTROLLER_H
#define BLUETOOTHCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QLowEnergyController>

#define NEO_SERVICE_UUID QBluetoothUuid((const QUuid) "f4f232be-5a53-11e6-8b77-86f30ca893d3")
#define READER_CHARACTERISTIC_UUID QBluetoothUuid((const QUuid) "1d4b745a-5a54-11e6-8b77-86f30ca893d3")
#define WRITER_CHARACTERISTIC_UUID QBluetoothUuid((const QUuid) "e25328b0-5a54-11e6-8b77-86f30ca893d3")

class BluetoothController : public QObject
{
    Q_OBJECT

public:
     explicit BluetoothController(QObject *parent = 0);
     ~BluetoothController();

     Q_INVOKABLE void setupBluetooth();

     void writeCharacteristic(QByteArray msg);

signals:

public slots:
    void addDevice(const QBluetoothDeviceInfo &device);
    void onConnected();
    void serviceDiscovered(const QBluetoothUuid &gatt);
    void onChargerReply(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
	void onStateChanged(QLowEnergyService::ServiceState newState);
	void characteristicWritten(const QLowEnergyCharacteristic&, const QByteArray&);

private:
    QBluetoothDeviceDiscoveryAgent* deviceDiscoveryAgent;
    QLowEnergyController* leController;

    QLowEnergyService* service;
    QLowEnergyCharacteristic writer, reader;

    void connect(const QBluetoothDeviceInfo& device);
};

#endif // BLUETOOTHCONTROLLER_H
