#ifndef CHARGERMODEL_H
#define CHARGERMODEL_H

#include <QVariant>
#include <QObject>
#include <QFileDialog>

#include "messagehelper.h"
#include "programparser.h"
#include "logheader.h"
#include "logdatapoint.h"
#include "storagemodel.h"

#define LED_OFF 0
#define LED_ON 1
#define LED_SLOW_BLINK 500
#define LED_FAST_BLINK 250

class ChargerModel : public QObject
{
    Q_OBJECT

public:
    explicit ChargerModel(QObject* parent = 0);
    ChargerModel(ChargerModel const&) = delete;

    static ChargerModel& getInstance();

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
    unsigned int getLEDGreen() const;
    Q_PROPERTY(QVariant LEDYellow READ getLEDYellow NOTIFY LEDYellowChanged)
    unsigned int getLEDYellow() const;
    Q_PROPERTY(QVariant LEDRed READ getLEDRed NOTIFY LEDRedChanged)
    unsigned int getLEDRed() const;
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

    Q_INVOKABLE void updateProgramSize();

    //This is actually EEprom size, but to keep with conventions of the charger, it is named log size
    Q_INVOKABLE void updateLogSize();

    Q_PROPERTY(QVariant logHeaders READ getLogHeaders NOTIFY logHeadersChanged)
    QVariant getLogHeaders();
    void retrieveLogHeaderRecursively(int logStart);
    Q_INVOKABLE void updateLogHeaders();

    std::vector<char> parseLog() const;
    Q_INVOKABLE void updateLog(int logHeaderIndex);
    Q_INVOKABLE void cancelLog();

    Q_INVOKABLE void writeProgramName(QString name);
    Q_INVOKABLE void writeProgramSizeInWords(QVariant size);
    Q_INVOKABLE void writeProgram(QVariant p);
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
    void logHeadersChanged();
    void logHeadersFinished();

    void programByteWritten();
    void logByteRead();

public slots:
    void onConnectionEstablished();
    void timeoutResponse();

private:
    MessageHelper messageHelper;
    QTimer updateTimer;

    unsigned int chargeVoltage = 0;
    unsigned int chargeCurrent = 0;
    char chargeProgramStep = 0;
    unsigned int LEDGreen = 0;
    unsigned int LEDYellow = 0;
    unsigned int LEDRed = 0;
    QString programName = "";
    unsigned int logCounterCharges = 0;
    unsigned int logCounterErrors = 0;
    unsigned int logCounterDepthDischarges = 0;
    unsigned int programSize = 0;
    unsigned int logSize = 0;
    std::vector<LogHeader> logHeaders;
    std::vector<char> log;
};

#endif // CHARGERMODEL_H
