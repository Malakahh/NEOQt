#include "blecontroller.h"

#include "messagehelper.h"
#include "storagemodel.h"

#define NEO_SERVICE_UUID QBluetoothUuid(QUuid("f4f232be-5a53-11e6-8b77-86f30ca893d3"))
#define READER_CHARACTERISTIC_UUID QBluetoothUuid(QUuid("1d4b745a-5a54-11e6-8b77-86f30ca893d3"))
#define WRITER_CHARACTERISTIC_UUID QBluetoothUuid(QUuid("e25328b0-5a54-11e6-8b77-86f30ca893d3"))

BLEController::BLEController(QObject *parent) : QObject(parent)
{
    BLEController::instance = this;
}

//BLEController& BLEController::getInstance()
//{
//    return *instance;
//}

BLEController* BLEController::instance = 0;

BLEController::~BLEController()
{
//    delete this->deviceDiscoveryAgent;

//    this->leController->disconnectFromDevice();
//    delete this->leController;

    for (auto itr = this->devices.begin(); itr < this->devices.end(); ++itr)
    {
        delete *itr;
    }
}

void BLEController::setupBLE()
{
    this->deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    QObject::connect(this->deviceDiscoveryAgent,
                     SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo&)),
                     this,
                     SLOT(addDevice(const QBluetoothDeviceInfo&)));

    this->deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BLEController::addDevice(const QBluetoothDeviceInfo &device)
{
    if (device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) //Filter for BLE devices
    {
        StorageModel& sm = StorageModel::getInstance();
        qDebug() << "found device: " << device.name() << " stored: " << sm.getBLEDeviceName();

        if (device.name() == sm.getBLEDeviceName())
        {
            this->connect(device);
            return;
        }

        this->devices.push_back(new BluetoothDeviceDataObject(device, this));
        emit this->onDevicesChanged();
    }
}

void BLEController::connect(int index)
{
    QBluetoothDeviceInfo device = this->devices.at(index)->btDeviceInfo;

    this->connect(device);
}

void BLEController::connect(const QBluetoothDeviceInfo& device)
{
    StorageModel::getInstance().setBLEDeviceName(device.name());

    //this->leController = new QLowEnergyController(device.address(), this);
    this->leController = QLowEnergyController::createCentral(device, this);

    QObject::connect(this->leController,
                     SIGNAL(connected()),
                     this,
                     SLOT(onConnected()));

    QObject::connect(this->leController,
                     SIGNAL(serviceDiscovered(const QBluetoothUuid)),
                     this,
                     SLOT(onServiceDiscovered(QBluetoothUuid)));

    QObject::connect(this->leController,
                     SIGNAL(disconnected()),
                     this,
                     SLOT(onDisconnected()));

    this->leController->connectToDevice();
}

void BLEController::onDisconnected()
{
    qDebug() << "Connection lost";
    emit this->connectionLost();
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

void BLEController::onServiceDiscovered(QBluetoothUuid gatt)
{
    qDebug() << "Whaaat" << gatt.toString();

    if (gatt == NEO_SERVICE_UUID)
    {
        qDebug() << "NEO service discovered";

        this->service = this->leController->createServiceObject(gatt, this);

        QObject::connect(this->service,
                         SIGNAL(stateChanged(QLowEnergyService::ServiceState)),
                         this,
                         SLOT(onStateChanged(QLowEnergyService::ServiceState)));

        this->service->discoverDetails();
    }
}

bool BLEController::isUUIDReader(QBluetoothUuid uuid)
{
    return uuid == this->reader.uuid();
}

void BLEController::onStateChanged(QLowEnergyService::ServiceState newState)
{
    qDebug() << "test";
    qDebug() << "newState: " << newState;

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

        qDebug() << "Connection Established";
        emit this->connectionEstablished();
    }
}
