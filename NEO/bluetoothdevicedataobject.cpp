#include "bluetoothdevicedataobject.h"

BluetoothDeviceDataObject::BluetoothDeviceDataObject(QObject *parent) : QObject(parent)
{

}

BluetoothDeviceDataObject::BluetoothDeviceDataObject(BluetoothDeviceDataObject& deviceObject) : QObject(deviceObject.parent())
{
    this->btDeviceInfo = deviceObject.btDeviceInfo;
}

BluetoothDeviceDataObject::BluetoothDeviceDataObject(QBluetoothDeviceInfo deviceInfo, QObject* parent) : QObject(parent)
{
    this->btDeviceInfo = deviceInfo;
}

QString BluetoothDeviceDataObject::deviceName() const
{
    return this->btDeviceInfo.name();
}
