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

void ChargerModel::startUpdateTimer()
{
    this->updateTimer.start(UPDATER_INTERVAL);
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

char ChargerModel::getLEDGreen() const
{
    return LEDGreen;
}

char ChargerModel::getLEDYellow() const
{
    return LEDYellow;
}

char ChargerModel::getLEDRed() const
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
    programName.clear();

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
