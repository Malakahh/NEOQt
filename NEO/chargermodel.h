#ifndef CHARGERMODEL_H
#define CHARGERMODEL_H

#include <QVariant>
#include <QObject>
#include <QFileDialog>

#include "messagehelper.h"

/*
 * To update at interval:
 *  LED status
 *  Voltage
 *  Current
 *  Program Step
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

signals:
    void chargeVoltageChanged();
    void chargeCurrentChanged();
    void chargeProgramStepChanged();

public slots:
    void onConnectionEstablished();
    void timeoutResponse();

private:
    MessageHelper messageHelper;
    QTimer updateTimer;

    unsigned int chargeVoltage;
    unsigned int chargeCurrent;
    char chargeProgramStep;
};

#endif // CHARGERMODEL_H
