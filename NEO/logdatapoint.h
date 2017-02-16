#ifndef LOGDATAPOINT_H
#define LOGDATAPOINT_H

#include <qstring.h>

class LogDataPoint
{
public:
    LogDataPoint();
    LogDataPoint(const LogDataPoint& dataPoint);

    int voltage = 0; //mV
    int temp = 0; //C
    int current = 0; //mA
    int time = 0; //s
    int step = 0;

    QString toString();

    static double calcAh(std::vector<LogDataPoint> datapoints);
    static QString headerString();
};

#endif // LOGDATAPOINT_H
