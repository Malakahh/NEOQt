#ifndef BLUETOOTHDEVICEDATAOBJECT_H
#define BLUETOOTHDEVICEDATAOBJECT_H

#include <QObject>
#include <QtBluetooth/QBluetoothDeviceInfo>

class BluetoothDeviceDataObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceName READ deviceName CONSTANT)

public:
    explicit BluetoothDeviceDataObject(QObject *parent = 0);
    BluetoothDeviceDataObject(const QBluetoothDeviceInfo& deviceInfo, QObject *parent = 0);

    const QBluetoothDeviceInfo* btDeviceInfo;

    QString deviceName() const;

signals:

public slots:
};

#endif // BLUETOOTHDEVICEDATAOBJECT_H
