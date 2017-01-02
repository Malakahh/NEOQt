#ifndef BLUETOOTHDEVICEDATAOBJECT_H
#define BLUETOOTHDEVICEDATAOBJECT_H

#include <QObject>
#include <QtBluetooth/QBluetoothDeviceInfo>
#include <QDebug>
#include <QtBluetooth/QBluetoothAddress>

class BluetoothDeviceDataObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceName READ deviceName CONSTANT)

public:
    explicit BluetoothDeviceDataObject(QObject *parent = 0);
    BluetoothDeviceDataObject(BluetoothDeviceDataObject& deviceObject);
    BluetoothDeviceDataObject(QBluetoothDeviceInfo deviceInfo, QObject *parent = 0);

    QBluetoothDeviceInfo btDeviceInfo;

    QString deviceName() const;

signals:

public slots:
};

#endif // BLUETOOTHDEVICEDATAOBJECT_H
