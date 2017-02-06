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

    Q_PROPERTY(QString programName READ getProgramName NOTIFY programNameChanged)
    QString getProgramName() const;
    Q_INVOKABLE void updateProgramName();

    Q_PROPERTY(QVariant logCounterCharges READ getLogCounterCharges NOTIFY logCounterChargesChanged)
    unsigned int getLogCounterCharges() const;
    Q_INVOKABLE void updateLogCounterCharges();

    Q_PROPERTY(QVariant logCounterErrors READ getLogCounterErrors NOTIFY logCounterErrorsChanged)
    unsigned int getLogCounterErrors() const;
    Q_INVOKABLE void updateLogCounterErrors();

    Q_PROPERTY(QVariant logCounterDepthDischarges READ getLogCounterDepthDischarges NOTIFY logCounterDepthDischargesChanged)
    unsigned int getLogCounterDepthDischarges() const;
    Q_INVOKABLE void updateLogCounterDepthDischarges();

    void updateProgramSize();

    //This is actually EEprom size, but to keep with conventions of the charger, it is named log size
    void updateLogSize();



    Q_INVOKABLE void writeProgramName(QString name);
    Q_INVOKABLE void writeProgramSizeInWords(std::vector<unsigned char> size);
    Q_INVOKABLE void writeProgram(std::vector<unsigned char> program);
    Q_INVOKABLE void clearLogCounters();

    Q_INVOKABLE void enterProgMode();
    Q_INVOKABLE void enterNormalMode();

signals:
    void chargeVoltageChanged();
    void chargeCurrentChanged();
    void chargeProgramStepChanged();
    void LEDGreenChanged();
    void LEDYellowChanged();
    void LEDRedChanged();
    void programNameChanged();
    void logCounterChargesChanged();
    void logCounterErrorsChanged();
    void logCounterDepthDischargesChanged();
    void programSizeChanged();
    void logSizeChanged();

    void programByteWritten(char byteWritten);

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
    QString programName;
    unsigned int logCounterCharges;
    unsigned int logCounterErrors;
    unsigned int logCounterDepthDischarges;
    unsigned int programSize;
    unsigned int logSize;
};

#endif // CHARGERMODEL_H
