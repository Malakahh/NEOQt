#include "blecontroller.h"

#define NEO_SERVICE_UUID QBluetoothUuid((const QUuid) "f4f232be-5a53-11e6-8b77-86f30ca893d3")
#define READER_CHARACTERISTIC_UUID QBluetoothUuid((const QUuid) "1d4b745a-5a54-11e6-8b77-86f30ca893d3")
#define WRITER_CHARACTERISTIC_UUID QBluetoothUuid((const QUuid) "e25328b0-5a54-11e6-8b77-86f30ca893d3")

BLEController::BLEController(QObject *parent) : QObject(parent) {}

BLEController::~BLEController()
{
    delete this->deviceDiscoveryAgent;
    delete this->leController;

    for (auto itr = this->devices.begin(); itr < this->devices.end(); itr++)
    {
        delete *itr;
    }
}

void BLEController::setupBLE()
{
    if (this->deviceDiscoveryAgent != nullptr)
    {
        delete this->deviceDiscoveryAgent;
    }

    this->deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    QObject::connect(this->deviceDiscoveryAgent,
                     SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo&)),
                     this,
                     SLOT(addDevice(const QBluetoothDeviceInfo&)));

    this->deviceDiscoveryAgent->start();
}

void BLEController::addDevice(const QBluetoothDeviceInfo &device)
{
    if (device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) //Filter for BLE devices
    {
        qDebug() << "Discovered BLE device - name: " << device.name() << " Address: " << device.address().toString();
        this->devices.push_back(new BluetoothDeviceDataObject(device, this));
        emit this->onDevicesChanged();
    }
}

void BLEController::connect(int index)
{
    QBluetoothDeviceInfo device = this->devices.at(index)->btDeviceInfo;

    if (this->leController != nullptr)
    {
        delete this->leController;
    }

    this->leController = new QLowEnergyController(device.address(), this);

    QObject::connect(this->leController,
                     SIGNAL(connected()),
                     this,
                     SLOT(onConnected()));

    QObject::connect(this->leController,
                     SIGNAL(serviceDiscovered(const QBluetoothUuid)),
                     this,
                     SLOT(onServiceDiscovered(QBluetoothUuid)));

    this->leController->connectToDevice();
}

void BLEController::writeCharacteristic(QByteArray msg)
{
    this->service->writeCharacteristic(this->writer, msg, QLowEnergyService::WriteWithResponse);
}

QVariant BLEController::getDevices() const
{
    QList<QObject*> list;

    for (auto itr = this->devices.begin(); itr < this->devices.end(); itr++)
    {
        list.append(*itr);
    }

    return QVariant::fromValue(list);
}

void BLEController::onConnected()
{
    qDebug() << "Device connected!";
    this->leController->discoverServices();
}

void BLEController::onServiceDiscovered(const QBluetoothUuid &gatt)
{
    if (gatt == NEO_SERVICE_UUID)
    {
        qDebug() << "NEO service discovered";

        this->service = this->leController->createServiceObject(gatt);

        QObject::connect(this->service,
                         SIGNAL(stateChanged(QLowEnergyService::ServiceState)),
                         this,
                         SLOT(onStateChanged(QLowEnergyService::ServiceState)));

        QObject::connect(this->service,
                         SIGNAL(characteristicWritten(const QLowEnergyCharacteristic&, const QByteArray&)),
                         this,
                         SLOT(onCharacteristicWritten(const QLowEnergyCharacteristic&, const QByteArray&)));

        QObject::connect(this->service,
                         SIGNAL(characteristicRead(const QLowEnergyCharacteristic&, const QByteArray&)),
                         this,
                         SLOT(onCharacteristicRead(const QLowEnergyCharacteristic&, const QByteArray&)));

        this->service->discoverDetails();
    }
}

void BLEController::onStateChanged(QLowEnergyService::ServiceState newState)
{
    if (newState == QLowEnergyService::ServiceDiscovered)
    {
        this->writer = this->service->characteristic(WRITER_CHARACTERISTIC_UUID);
        this->reader = this->service->characteristic(READER_CHARACTERISTIC_UUID);

        QLowEnergyDescriptor notification = this->reader.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);

        if (!this->writer.isValid())
        {
            qWarning() << "Writer not valid.";
        }

        if (!this->reader.isValid())
        {
            qWarning() << "Reader not valid.";
        }

        if (!notification.isValid())
        {
            qWarning() << "QLowEnergyDescriptor not valid.";
        }

        this->service->writeDescriptor(notification, QByteArray::fromHex("0100"));
    }
}

void BLEController::onCharacteristicWritten(const QLowEnergyCharacteristic& characteristic, const QByteArray& data)
{
    qDebug() << "Data written: " << data;
}

void BLEController::onCharacteristicRead(const QLowEnergyCharacteristic& characteristic, const QByteArray& data)
{
    if (characteristic.uuid() == this->reader.uuid())
    {
        qDebug() << "Charger reply: " << QString(data);
    }
}
