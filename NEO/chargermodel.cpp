#include "chargermodel.h"

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
}

void ChargerModel::onConnectionEstablished()
{
    this->messageHelper.hookSignals();
}

int ChargerModel::getChargeVoltage() const
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

        qDebug() << "ChargeVoltage - low: " << (unsigned int)msg[0];
        qDebug() << "ChargeVoltage: " << this->chargeVoltage;
    };

    messageHelper.enqueueQuery(msg_high, 1, f_high);
    messageHelper.enqueueQuery(msg_low, 1, f_low);
}
