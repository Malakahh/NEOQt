#ifndef CHARGERMODEL_H
#define CHARGERMODEL_H

#include <QVariant>
#include <QObject>
#include <QFileDialog>

#include "messagehelper.h"

class ChargerModel : public QObject
{
    Q_OBJECT

public:
    explicit ChargerModel(QObject* parent = 0);

    Q_PROPERTY(QVariant chargeVoltage READ getChargeVoltage NOTIFY chargeVoltageChanged)

    int getChargeVoltage() const;

    Q_INVOKABLE void updateChargeVoltage();
    Q_INVOKABLE void fileDialogTest();

signals:
    void chargeVoltageChanged();

public slots:
    void onConnectionEstablished();

private:
    MessageHelper messageHelper;

    unsigned int chargeVoltage;

};

#endif // CHARGERMODEL_H
