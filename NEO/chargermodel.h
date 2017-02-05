#ifndef CHARGERMODEL_H
#define CHARGERMODEL_H

#include <QVariant>
#include <QObject>
#include <QFileDialog>

#include "messagehelper.h"

#define LED_OFF 0
#define LED_ON 1
#define LED_SLOW_BLINK 2
#define LED_FAST_BLINK 3

/*
 * To update at interval:
 *  [ ] LED status
 *  [x] Voltage
 *  [x] Current
 *  [x] Program Step
 */


class ChargerModel : public QObject
{
    Q_OBJECT

public:
    explicit ChargerModel(QObject* parent = 0);

    Q_INVOKABLE void startUpdateTimer();
    Q_INVOKABLE void stopUpdateTimer();

    Q_PROPERTY(QVariant chargeVoltage READ getChargeVoltage NOTIFY chargeVoltageChanged)
    unsigned int getChargeVoltage() const;
    Q_INVOKABLE void updateChargeVoltage();

    Q_PROPERTY(QVariant chargeCurrent READ getChargeCurrent NOTIFY chargeCurrentChanged)
    unsigned int getChargeCurrent() const;
    Q_INVOKABLE void updateChargeCurrent();

    Q_PROPERTY(QVariant chargeProgramStep READ getChargeProgramStep NOTIFY chargeProgramStepChanged)
    char getChargeProgramStep() const;
    Q_INVOKABLE void updateChargeProgramStep();

    Q_PROPERTY(QVariant LEDGreen READ getLEDGreen NOTIFY LEDGreenChanged)
    char getLEDGreen() const;
    Q_PROPERTY(QVariant LEDYellow READ getLEDYellow NOTIFY LEDYellowChanged)
    char getLEDYellow() const;
    Q_PROPERTY(QVariant LEDRed READ getLEDRed NOTIFY LEDRedChanged)
    char getLEDRed() const;
    Q_INVOKABLE void updateLEDStatus();

signals:
    void chargeVoltageChanged();
    void chargeCurrentChanged();
    void chargeProgramStepChanged();
    void LEDGreenChanged();
    void LEDYellowChanged();
    void LEDRedChanged();

public slots:
    void onConnectionEstablished();
    void timeoutResponse();

private:
    MessageHelper messageHelper;
    QTimer updateTimer;

    unsigned int chargeVoltage;
    unsigned int chargeCurrent;
    char chargeProgramStep;
    char LEDGreen;
    char LEDYellow;
    char LEDRed;
};

#endif // CHARGERMODEL_H
