#include "bluetoothdevicedataobject.h"

BluetoothDeviceDataObject::BluetoothDeviceDataObject(QObject *parent) : QObject(parent)
{

}

BluetoothDeviceDataObject::BluetoothDeviceDataObject(const QBluetoothDeviceInfo& deviceInfo, QObject* parent) : QObject(parent)
{
    this->btDeviceInfo = &deviceInfo;
}

QString BluetoothDeviceDataObject::deviceName() const
{
    if (this->btDeviceInfo == nullptr)
        return "";

    return this->btDeviceInfo->name();
}
