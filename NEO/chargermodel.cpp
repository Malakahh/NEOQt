#include "chargermodel.h"

#define UPDATER_INTERVAL 10000

//Utility
#define WRITE_REG 0x80
#define READ_REG 0x00
#define WRITE_EE_PROM 0x40
//#define READ_EE_PROM 0x00

//Register Layout
#define M_GBC_OPERATION_MODE 0x04
#define C_CMD_EE_DATA_HIGH 0x05
#define C_CMD_EE_DATA_LOW 0x06
#define C_CMD_EE_ADDR_HIGH 0x07
#define C_CMD_EE_ADDR_LOW 0x08
#define C_CHARGE_VOLT_MEAS_LOW 0x12
#define C_CHARGE_VOLT_MEAS_HIGH 0x13
#define C_CHARGE_CURR_MEAS_LOW 0x14
#define C_CHARGE_CURR_MEAS_HIGH 0x15
#define C_CHARGE_PSTEP_NUMBER 0x18
#define C_LED_MODE 0x1E
//#define C_LOG_CLEAR_CONTROL 0x21

//eeprom layout
#define EE_LOG_CNT_CHARG 0x1A
#define EE_LOG_CNT_ERROR 0x1B
#define EE_LOG_CNT_DEPTH 0x1C
#define EE_LOG_EE_SIZE 0x1D
#define EE_PROGRAM_NAME_1_2 0x1E
#define EE_PROGRAM_NAME_3_4 0x1F
#define EE_PROGRAM_NAME_5_6 0x20
#define EE_PROGRAM_NAME_7_8 0x21
#define EE_PROGRAM_SIZE 0x22
#define EE_PROGRAM_AREA 0x23

ChargerModel::ChargerModel(QObject* parent) : QObject(parent)
{
    QObject::connect(&BLEController::getInstance(),
                     SIGNAL(connectionEstablished()),
                     this,
                     SLOT(onConnectionEstablished()));

    QObject::connect(&this->updateTimer,
                     SIGNAL(timeout()),
                     this,
                     SLOT(timeoutResponse()));
}

ChargerModel& ChargerModel::getInstance()
{
    static ChargerModel instance;

    return instance;
}


void ChargerModel::startUpdateTimer()
{
    if (!this->updateTimer.isActive())
    {
        this->updateTimer.start(UPDATER_INTERVAL);
    }
}

void ChargerModel::stopUpdateTimer()
{
    this->updateTimer.stop();
}

void ChargerModel::timeoutResponse()
{
    qDebug() << "Update data timeout";

    this->updateChargeCurrent();
    this->updateChargeProgramStep();
    this->updateChargeVoltage();
    this->updateLEDStatus();
}

void ChargerModel::onConnectionEstablished()
{
    this->messageHelper.hookSignals();
}

unsigned int ChargerModel::getChargeVoltage() const
{
    return chargeVoltage;
}

void ChargerModel::updateChargeVoltage()
{
    std::vector<unsigned char> msg_high = {
        C_CHARGE_VOLT_MEAS_HIGH | READ_REG
    };

    std::vector<unsigned char> msg_low = {
        C_CHARGE_VOLT_MEAS_LOW | READ_REG
    };

    std::function<void (const std::vector<char>)> f_high = [&](const std::vector<char> msg) {
        qDebug() << "ChargeVoltage - pre: " << this->chargeVoltage;
        this->chargeVoltage = 0 | (((unsigned int)msg[0] & 0xFF) << 8);

        qDebug() << "ChargeVoltage - high: " << (unsigned int)msg[0];
        qDebug() << "ChargeVoltage - post: " << this->chargeVoltage;
    };

    std::function<void (const std::vector<char>)> f_low = [&](const std::vector<char> msg) {
        this->chargeVoltage |= (unsigned int)msg[0] & 0xFF;

        emit this->chargeVoltageChanged();

        qDebug() << "ChargeVoltage - low: " << (unsigned int)msg[0];
        qDebug() << "ChargeVoltage: " << this->chargeVoltage;
    };

    messageHelper.enqueueQuery(msg_high, 1, f_high);
    messageHelper.enqueueQuery(msg_low, 1, f_low);
}

unsigned int ChargerModel::getChargeCurrent() const
{
    return chargeCurrent;
}

void ChargerModel::updateChargeCurrent()
{
    std::vector<unsigned char> msg_high = {
        C_CHARGE_CURR_MEAS_HIGH | READ_REG
    };

    std::vector<unsigned char> msg_low = {
        C_CHARGE_CURR_MEAS_LOW | READ_REG
    };

    std::function<void (const std::vector<char>)> f_high = [&](const std::vector<char> msg) {
        this->chargeCurrent = ((unsigned int)msg[0] & 0xFF) << 8;
    };

    std::function<void (const std::vector<char>)> f_low = [&](const std::vector<char> msg) {
        this->chargeCurrent |= (unsigned int)msg[0] & 0xFF;

        emit this->chargeCurrentChanged();

        qDebug() << "ChargeCurrent: " << this->chargeCurrent;
    };

    messageHelper.enqueueQuery(msg_high, 1, f_high);
    messageHelper.enqueueQuery(msg_low, 1, f_low);
}

char ChargerModel::getChargeProgramStep() const
{
    return chargeProgramStep;
}

void ChargerModel::updateChargeProgramStep()
{
    std::vector<unsigned char> msg = {
        C_CHARGE_PSTEP_NUMBER | READ_REG
    };

    std::function<void (const std::vector<char>)> f = [&](const std::vector<char> response) {
        this->chargeProgramStep = response[0] & 0xFF;

        emit this->chargeProgramStepChanged();

        qDebug() << "Program Step: " << (unsigned int)this->chargeProgramStep;
    };

    messageHelper.enqueueQuery(msg, 1, f);
}

unsigned int ChargerModel::getLEDGreen() const
{
    return LEDGreen;
}

unsigned int ChargerModel::getLEDYellow() const
{
    return LEDYellow;
}

unsigned int ChargerModel::getLEDRed() const
{
    return LEDRed;
}

void ChargerModel::updateLEDStatus()
{
    std::vector<unsigned char> msg = {
        C_LED_MODE | READ_REG
    };

    std::function<void (const std::vector<char>)> f = [&](const std::vector<char> response) {
        char bitmask = response[0];
        this->LEDGreen = LED_OFF;
        this->LEDYellow = LED_OFF;
        this->LEDRed = LED_OFF;

        if ((bitmask & 1) == 1) {
            this->LEDGreen = LED_ON;
        }
        else if (((bitmask >> 1) & 1) == 1) {
            this->LEDGreen = LED_SLOW_BLINK;
        }

        if (((bitmask >> 2) & 1) == 1) {
            this->LEDYellow = LED_ON;
        }
        else if (((bitmask >> 3) & 1) == 1) {
            this->LEDYellow = LED_SLOW_BLINK;
        }
        else if (((bitmask >> 4) & 1) == 1) {
            this->LEDYellow = LED_FAST_BLINK;
        }

        if (((bitmask >> 5) & 1) == 1) {
            this->LEDRed = LED_ON;
        }
        else if (((bitmask >> 6) & 1) == 1) {
            this->LEDRed = LED_SLOW_BLINK;
        }

        emit this->LEDGreenChanged();
        emit this->LEDYellowChanged();
        emit this->LEDRedChanged();

        qDebug() << "green: " << (int)this->LEDGreen;
        qDebug() << "yellow: " << (int)this->LEDYellow;
        qDebug() << "red: " << (int)this->LEDRed;
    };

    messageHelper.enqueueQuery(msg, 1, f);
}

QString ChargerModel::getProgramName() const
{
    return programName;
}

void ChargerModel::updateProgramName()
{
    //programName.clear();
    programName = "";

    //Read ee_program_name_1_2
    std::vector<unsigned char> msg_1_2a = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG,
        EE_PROGRAM_NAME_1_2
    };

    std::vector<unsigned char> msg_1_2b = {
        C_CMD_EE_DATA_HIGH | READ_REG,
        C_CMD_EE_DATA_LOW | READ_REG
    };

    //Read ee_program_name_3_4
    std::vector<unsigned char> msg_3_4a = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG,
        EE_PROGRAM_NAME_3_4
    };

    std::vector<unsigned char> msg_3_4b = {
        C_CMD_EE_DATA_HIGH | READ_REG,
        C_CMD_EE_DATA_LOW | READ_REG
    };

    //Read ee_program_name_5_6
    std::vector<unsigned char> msg_5_6a = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG,
        EE_PROGRAM_NAME_5_6
    };

    std::vector<unsigned char> msg_5_6b = {
        C_CMD_EE_DATA_HIGH | READ_REG,
        C_CMD_EE_DATA_LOW | READ_REG
    };

    //Read ee_program_name_7_8
    std::vector<unsigned char> msg_7_8a = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG,
        EE_PROGRAM_NAME_7_8
    };

    std::vector<unsigned char> msg_7_8b = {
        C_CMD_EE_DATA_HIGH | READ_REG,
        C_CMD_EE_DATA_LOW | READ_REG
    };

    std::function<void (const std::vector<char>)> f = [&](const std::vector<char> response) {
        this->programName.append(response[0]);
        this->programName.append(response[1]);
    };

    std::function<void (const std::vector<char>)> f_final = [&](const std::vector<char> response) {
        this->programName.append(response[0]);
        this->programName.append(response[1]);

        emit this->programNameChanged();

        qDebug() << "ProgramName: " << this->programName;
    };

    messageHelper.enqueueQuery(msg_1_2a);
    messageHelper.enqueueQuery(msg_1_2b, 2, f);

    messageHelper.enqueueQuery(msg_3_4a);
    messageHelper.enqueueQuery(msg_3_4b, 2, f);

    messageHelper.enqueueQuery(msg_5_6a);
    messageHelper.enqueueQuery(msg_5_6b, 2, f);

    messageHelper.enqueueQuery(msg_7_8a);
    messageHelper.enqueueQuery(msg_7_8b, 2, f_final);
}

unsigned int ChargerModel::getLogCounterCharges() const
{
    return logCounterCharges;
}

void ChargerModel::updateLogCounterCharges()
{
    std::vector<unsigned char> msg_a = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG,
        EE_LOG_CNT_CHARG
    };

    std::vector<unsigned char> msg_b = {
        C_CMD_EE_DATA_HIGH | READ_REG,
        C_CMD_EE_DATA_LOW | READ_REG
    };

    std::function<void (const std::vector<char>)> f = [&](const std::vector<char> response) {
        this->logCounterCharges = ((response[0] & 0xFF) << 8) | (response[1] & 0xFF);

        emit this->logCounterChargesChanged();
    };

    messageHelper.enqueueQuery(msg_a);
    messageHelper.enqueueQuery(msg_b, 2, f);
}

unsigned int ChargerModel::getLogCounterErrors() const
{
    return logCounterErrors;
}

void ChargerModel::updateLogCounterErrors()
{
    std::vector<unsigned char> msg_a = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG,
        EE_LOG_CNT_ERROR
    };

    std::vector<unsigned char> msg_b = {
        C_CMD_EE_DATA_HIGH | READ_REG,
        C_CMD_EE_DATA_LOW | READ_REG
    };

    std::function<void (const std::vector<char>)> f = [&](const std::vector<char> response) {
        this->logCounterErrors = ((response[0] & 0xFF) << 8) | (response[1] & 0xFF);

        emit this->logCounterErrorsChanged();
    };

    messageHelper.enqueueQuery(msg_a);
    messageHelper.enqueueQuery(msg_b, 2, f);
}

unsigned int ChargerModel::getLogCounterDepthDischarges() const
{
    return logCounterDepthDischarges;
}

void ChargerModel::updateLogCounterDepthDischarges()
{
    std::vector<unsigned char> msg_a = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG,
        EE_LOG_CNT_DEPTH
    };

    std::vector<unsigned char> msg_b = {
        C_CMD_EE_DATA_HIGH | READ_REG,
        C_CMD_EE_DATA_LOW | READ_REG
    };

    std::function<void (const std::vector<char>)> f = [&](const std::vector<char> response) {
        this->logCounterDepthDischarges = ((response[0] & 0xFF) << 8) | (response[1] & 0xFF);

        emit this->logCounterDepthDischargesChanged();
    };

    messageHelper.enqueueQuery(msg_a);
    messageHelper.enqueueQuery(msg_b, 2, f);
}

void ChargerModel::updateProgramSize()
{
    std::vector<unsigned char> msg_a = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG,
        EE_PROGRAM_SIZE
    };

    std::vector<unsigned char> msg_b = {
        C_CMD_EE_DATA_HIGH | READ_REG,
        C_CMD_EE_DATA_LOW | READ_REG
    };

    std::function<void (const std::vector<char>)> f = [&](const std::vector<char> response) {
        this->programSize = ((response[0] & 0xFF) << 8) | (response[1] & 0xFF);

        emit this->programSizeChanged();
    };

    messageHelper.enqueueQuery(msg_a);
    messageHelper.enqueueQuery(msg_b, 2, f);
}

void ChargerModel::updateLogSize()
{
    std::vector<unsigned char> msg_a = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG,
        EE_LOG_EE_SIZE
    };

    std::vector<unsigned char> msg_b = {
        C_CMD_EE_DATA_HIGH | READ_REG,
        C_CMD_EE_DATA_LOW | READ_REG
    };

    std::function<void (const std::vector<char>)> f = [&](const std::vector<char> response) {
        this->logSize = ((response[0] & 0xFF) << 8) | (response[1] & 0xFF);

        emit this->logSizeChanged();
    };

    messageHelper.enqueueQuery(msg_a);
    messageHelper.enqueueQuery(msg_b, 2, f);
}

QVariant ChargerModel::getLogHeaders()
{
    QList<QObject*> list;

    for (LogHeader& header : this->logHeaders)
    {
        list.append(&header);
    }

    return QVariant::fromValue(list);
}

void ChargerModel::retrieveLogHeaderRecursively(int logStart)
{
    qDebug() << "logStart: " << logStart;

    std::vector<unsigned char> msg_a = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        static_cast<unsigned char>((logStart >> 8) & 0xFF),
        C_CMD_EE_ADDR_LOW | WRITE_REG,
        static_cast<unsigned char>(logStart & 0xFF)
    };

    std::vector<unsigned char> msg_b = {
        C_CMD_EE_DATA_HIGH | READ_REG,
        C_CMD_EE_DATA_LOW | READ_REG
    };

    std::function<void (const std::vector<char>)> f = [this, logStart](const std::vector<char> response) {
        static int initialLogStart = -1;

        LogHeader header;
        header.size = (response[0] << 8) | response[1];
        header.address = logStart;

        if (header.size == 0 || initialLogStart == logStart)
        {
            qDebug() << "No logs found";
            initialLogStart = -1;
            return;
        }

        if (initialLogStart < 0)
        {
            initialLogStart = logStart;
        }

        this->logHeaders.push_back(header);
        emit this->logHeadersChanged();

        if (header.address + header.size >= this->logSize - 1)
        {
            int logFileStart = EE_PROGRAM_AREA + this->programSize + 2;
            int diff = header.address + header.size - this->logSize;
            retrieveLogHeaderRecursively(logFileStart + diff + 1);
        }
        else
        {
            retrieveLogHeaderRecursively(header.address + header.size + 1);
        }
    };

    messageHelper.enqueueQuery(msg_a);
    messageHelper.enqueueQuery(msg_b, 2, f);
}

void ChargerModel::updateLogHeaders()
{
    this->logHeaders.clear();

    int logFileStart = EE_PROGRAM_AREA + this->programSize;

    qDebug() << "logFileStart: " << logFileStart;

    std::vector<unsigned char> msg_initialOffset_a = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        static_cast<unsigned char>(((logFileStart + 1) >> 8) & 0xFF),
        C_CMD_EE_ADDR_LOW | WRITE_REG,
        static_cast<unsigned char>((logFileStart + 1) & 0xFF)
    };

    std::vector<unsigned char> msg_initialOffset_b = {
        C_CMD_EE_DATA_HIGH | READ_REG,
        C_CMD_EE_DATA_LOW | READ_REG
    };

    std::function<void (const std::vector<char>)> f = [this, logFileStart](const std::vector<char> response) {
        int offset = (static_cast<unsigned char>(response[0]) << 8) | static_cast<unsigned char>(response[1]);

        qDebug() << "Initial offset: " << offset;

        this->retrieveLogHeaderRecursively(logFileStart + offset);
    };

    messageHelper.enqueueQuery(msg_initialOffset_a);
    messageHelper.enqueueQuery(msg_initialOffset_b, 2, f);
}

std::vector<char> ChargerModel::parseLog() const
{
    std::vector<LogDataPoint> datapoints;

    QString dataStr = LogDataPoint::headerString() + "\n";

    for (int i = 0; i < this->log.size(); i += 6)
    {
        LogDataPoint dp;
        dp.voltage = (((static_cast<unsigned char>(this->log[i]) & 0x01) << 8) | static_cast<unsigned char>(this->log[i + 1])) * 100;
        dp.temp = static_cast<unsigned char>(this->log[i]) >> 1;
        dp.current = static_cast<unsigned char>(this->log[i + 3]) * 100;
        dp.step = static_cast<unsigned char>(this->log[i + 2]);
        dp.time = (static_cast<unsigned char>(this->log[i + 4]) << 8) | static_cast<unsigned char>(this->log[i + 5]);

        dataStr += dp.toString() + "\n";

        datapoints.push_back(dp);
    }

    double Ah = LogDataPoint::calcAh(datapoints);
    qDebug() << "Ah: " << Ah;
    StorageModel::getInstance().setAhPrev(Ah);

    std::vector<char> csv;
    for (auto itr = dataStr.begin(); itr < dataStr.end(); itr++)
    {
        csv.push_back((*itr).toLatin1());
    }

    return csv;
}

void ChargerModel::updateLog(int logHeaderIndex)
{
    this->log.clear();

    LogHeader& header = this->logHeaders.at(logHeaderIndex);
    int logEnd = header.address + header.size;
    int wrapOffset = 0;

    for (int i = header.address + 1; i <= logEnd; i++)
    {
        if (wrapOffset == 0 && i > this->logSize - 1)
        {
            wrapOffset = EE_PROGRAM_AREA + this->programSize + 2 - this->logSize;
        }

        std::vector<unsigned char> msg_a = {
            C_CMD_EE_ADDR_HIGH | WRITE_REG,
            static_cast<unsigned char>(((i + wrapOffset) >> 8) & 0xFF),
            C_CMD_EE_ADDR_LOW | WRITE_REG,
            static_cast<unsigned char>((i + wrapOffset) & 0xFF)
        };

        std::vector<unsigned char> msg_b = {
            C_CMD_EE_DATA_HIGH | READ_REG,
            C_CMD_EE_DATA_LOW | READ_REG
        };

        std::function<void (const std::vector<char>)> f = [this](const std::vector<char> response) {
            this->log.push_back(response[0]);
            this->log.push_back(response[1]);

            emit this->logByteRead();
            emit this->logByteRead();
        };

        messageHelper.enqueueQuery(msg_a);
        messageHelper.enqueueQuery(msg_b, 2, f);
    }
}

void ChargerModel::cancelLog()
{
    messageHelper.clearQueue(messageHelper.callbacks);
    this->log.clear();
}




void ChargerModel::writeProgramName(QString name)
{    
    std::vector<unsigned char> msg_1_2a = {
        C_CMD_EE_DATA_HIGH | WRITE_REG,
        static_cast<unsigned char>(name[0].toLatin1()),
        C_CMD_EE_DATA_LOW | WRITE_REG,
        static_cast<unsigned char>(name[1].toLatin1())
    };

    std::vector<unsigned char> msg_1_2b = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG | WRITE_EE_PROM,
        EE_PROGRAM_NAME_1_2
    };

    std::vector<unsigned char> msg_3_4a = {
        C_CMD_EE_DATA_HIGH | WRITE_REG,
        static_cast<unsigned char>(name[2].toLatin1()),
        C_CMD_EE_DATA_LOW | WRITE_REG,
        static_cast<unsigned char>(name[3].toLatin1())
    };

    std::vector<unsigned char> msg_3_4b = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG | WRITE_EE_PROM,
        EE_PROGRAM_NAME_3_4
    };

    std::vector<unsigned char> msg_5_6a = {
        C_CMD_EE_DATA_HIGH | WRITE_REG,
        static_cast<unsigned char>(name[4].toLatin1()),
        C_CMD_EE_DATA_LOW | WRITE_REG,
        static_cast<unsigned char>(name[5].toLatin1())
    };

    std::vector<unsigned char> msg_5_6b = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG | WRITE_EE_PROM,
        EE_PROGRAM_NAME_5_6
    };

    std::vector<unsigned char> msg_7_8a = {
        C_CMD_EE_DATA_HIGH | WRITE_REG,
        static_cast<unsigned char>(name[6].toLatin1()),
        C_CMD_EE_DATA_LOW | WRITE_REG,
        static_cast<unsigned char>(name[7].toLatin1())
    };

    std::vector<unsigned char> msg_7_8b = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG | WRITE_EE_PROM,
        EE_PROGRAM_NAME_7_8
    };

    messageHelper.enqueueQuery(msg_1_2a);
    messageHelper.enqueueQuery(msg_1_2b);
    messageHelper.enqueueQuery(msg_3_4a);
    messageHelper.enqueueQuery(msg_3_4b);
    messageHelper.enqueueQuery(msg_5_6a);
    messageHelper.enqueueQuery(msg_5_6b);
    messageHelper.enqueueQuery(msg_7_8a);
    messageHelper.enqueueQuery(msg_7_8b);
}

void ChargerModel::writeProgramSizeInWords(QVariant size)
{
    int s = size.toInt();

    std::vector<unsigned char> msg_a = {
        C_CMD_EE_DATA_HIGH | WRITE_REG,
        static_cast<unsigned char>((s >> 8) & 0xFF),
        C_CMD_EE_DATA_LOW | WRITE_REG,
        static_cast<unsigned char>(s & 0xFF)
    };

    std::vector<unsigned char> msg_b = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG | WRITE_EE_PROM,
        EE_PROGRAM_SIZE
    };

    messageHelper.enqueueQuery(msg_a);
    messageHelper.enqueueQuery(msg_b);
}

void ChargerModel::writeProgram(QVariant p)
{
    std::vector<char> program = p.value<std::vector<char>>();

    std::function<void (const std::vector<char>)> f = [&](const std::vector<char> response) {
        emit this->programByteWritten();
        emit this->programByteWritten();
    };

    for (int i = 0; i < program.size(); i += 2)
    {
        int fullAddr = EE_PROGRAM_AREA + i / 2;
        unsigned char addrHigh = (fullAddr & 0xFF00) >> 8;
        unsigned char addrLow = fullAddr & 0xFF;

        std::vector<unsigned char> msg_a = {
            C_CMD_EE_DATA_HIGH | WRITE_REG,
            static_cast<unsigned char>(program[i]),
            C_CMD_EE_DATA_LOW | WRITE_REG,
            static_cast<unsigned char>(program[i + 1])
        };

        std::vector<unsigned char> msg_b = {
            C_CMD_EE_ADDR_HIGH | WRITE_REG,
            addrHigh,
            C_CMD_EE_ADDR_LOW | WRITE_REG | WRITE_EE_PROM,
            addrLow
        };

        messageHelper.enqueueQuery(msg_a);
        messageHelper.enqueueQuery(msg_b, 0, f);
    }
}

void ChargerModel::clearLogCounters()
{
    std::vector<unsigned char> msg_zero = {
        C_CMD_EE_DATA_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_DATA_LOW | WRITE_REG,
        0x00
    };

    std::vector<unsigned char> msg_charge = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG | WRITE_EE_PROM,
        EE_LOG_CNT_CHARG
    };

    std::vector<unsigned char> msg_error = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG | WRITE_EE_PROM,
        EE_LOG_CNT_ERROR
    };

    std::vector<unsigned char> msg_depthDischarge = {
        C_CMD_EE_ADDR_HIGH | WRITE_REG,
        0x00,
        C_CMD_EE_ADDR_LOW | WRITE_REG | WRITE_EE_PROM,
        EE_LOG_CNT_DEPTH
    };

    messageHelper.enqueueQuery(msg_zero);
    messageHelper.enqueueQuery(msg_charge);
    messageHelper.enqueueQuery(msg_zero);
    messageHelper.enqueueQuery(msg_error);
    messageHelper.enqueueQuery(msg_zero);
    messageHelper.enqueueQuery(msg_depthDischarge);
}

void ChargerModel::enterProgMode()
{
    std::vector<unsigned char> msg = {
        M_GBC_OPERATION_MODE | WRITE_REG,
        0x20
    };

    messageHelper.enqueueQuery(msg);
}

void ChargerModel::enterNormalMode()
{
    std::vector<unsigned char> msg = {
        M_GBC_OPERATION_MODE | WRITE_REG,
        0x80
    };

    messageHelper.enqueueQuery(msg);
}
