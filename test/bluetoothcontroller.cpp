#include "bluetoothcontroller.h"

BluetoothController::BluetoothController(QObject *parent) : QObject(parent)
{ }

BluetoothController::~BluetoothController()
{
    delete this->deviceDiscoveryAgent;
}

void BluetoothController::setupBluetooth()
{
    this->deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    QObject::connect(this->deviceDiscoveryAgent, SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo&)),
        this, SLOT(addDevice(const QBluetoothDeviceInfo&)));

    this->deviceDiscoveryAgent->start();
}

void BluetoothController::writeCharacteristic(QByteArray msg)
{
    this->service->writeCharacteristic(this->writer, msg, QLowEnergyService::WriteWithResponse);

	qDebug() << "Written: ";
}

void BluetoothController::addDevice(const QBluetoothDeviceInfo & device)
{
    if (device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
    {
        qWarning() << "Discovered LE Device name: " << device.name() << " Address: " << device.address().toString();
        this->connect(device);
    }
}

void BluetoothController::connect(const QBluetoothDeviceInfo& device)
{
    this->leController = QLowEnergyController::createCentral(device, this);
    QObject::connect(this->leController, SIGNAL(connected()),
        this, SLOT(onConnected()));
    QObject::connect(this->leController, SIGNAL(serviceDiscovered(const QBluetoothUuid)),
        this, SLOT(serviceDiscovered(const QBluetoothUuid)));

    this->leController->connectToDevice();
}

void BluetoothController::onConnected()
{
    qDebug() << "Device connected!";
    this->leController->discoverServices();
}

void BluetoothController::serviceDiscovered(const QBluetoothUuid &gatt)
{
    if (gatt == NEO_SERVICE_UUID)
    {
        qDebug() << "NEO service discovered";

        this->service = this->leController->createServiceObject(gatt);

        QObject::connect(this->service, SIGNAL(stateChanged(QLowEnergyService::ServiceState)),
            this, SLOT(onStateChanged(QLowEnergyService::ServiceState)));

		QObject::connect(this->service, SIGNAL(characteristicWritten(const QLowEnergyCharacteristic&, const QByteArray&)),
			this, SLOT(characteristicWritten(const QLowEnergyCharacteristic&, const QByteArray&)));

        this->service->discoverDetails();        
    }
}



void BluetoothController::onChargerReply(const QLowEnergyCharacteristic & characteristic, const QByteArray & newValue)
{
    if (characteristic.uuid() == this->reader.uuid())
    {
        qDebug() << "ChargerReply: " << newValue.length();

        for (int i = 0; i < newValue.length(); i++)
        {
            qDebug() << "val: " << (int)newValue[i];
        }

        if (newValue.length() == 5) {
            qDebug() << "Reply: " << (int)newValue[4];
        }
    }
    else
    {
        qDebug() << "Wrong characteristic changed";
    }
}

void BluetoothController::onStateChanged(QLowEnergyService::ServiceState newState)
{
    if (newState == QLowEnergyService::ServiceDiscovered)
    {
        this->writer = this->service->characteristic(WRITER_CHARACTERISTIC_UUID);
        this->reader = this->service->characteristic(READER_CHARACTERISTIC_UUID);

        QLowEnergyDescriptor notification = this->reader.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);

        if (!this->writer.isValid()) {
            qWarning() << "writer not valid";
        }

        if (!this->reader.isValid()) {
            qWarning() << "reader not valid";
        }

        if (!notification.isValid()) {
            qWarning() << "QLowEnergyDescriptor not valid";
        }

        QObject::connect(this->service, SIGNAL(characteristicChanged(const QLowEnergyCharacteristic&, const QByteArray&)),
            this, SLOT(onChargerReply(const QLowEnergyCharacteristic&, const QByteArray&)));

        this->service->writeDescriptor(notification, QByteArray::fromHex("0100"));

        const char msg[] = {
            0x7C,
            0x01,
            (char)0xC1,
            0x6E,
            0x77,
            (char)0xDB,
            0x18 //Step
        };

        this->writeCharacteristic(QByteArray::fromRawData(msg, 7));
    }
}

void BluetoothController::characteristicWritten(const QLowEnergyCharacteristic& characteristic, const QByteArray& data)
{
	qDebug() << "Data written: " << data;
}
