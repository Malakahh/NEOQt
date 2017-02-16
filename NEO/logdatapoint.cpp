#include "logdatapoint.h"

#include <sstream>

#define SEC_TO_HOUR 1 / 3600
#define MILI_A_TO_A 0.001

//#define SEC_TO_HOUR 3600
//#define MILI_A_TO_A 000.1

LogDataPoint::LogDataPoint()
{

}

LogDataPoint::LogDataPoint(const LogDataPoint& dp)
{
    this->time = dp.time;
    this->step = dp.step;
    this->voltage = dp.voltage;
    this->current = dp.current;
    this->temp = dp.temp;
}

QString LogDataPoint::toString()
{
    std::ostringstream ss;
    ss << this->time << ";" <<
        this->step << ";" <<
        this->voltage << ";" <<
        this->current << ";" <<
        this->temp;

    return QString::fromStdString(ss.str());
}

int LogDataPoint::calcAh(std::vector<LogDataPoint> datapoints)
{
    int Ah = 0;

    for (auto itr = datapoints.begin(); itr < datapoints.end() - 1; itr++)
    {
        Ah += MILI_A_TO_A * (itr->current + (itr + 1)->current) / 2 * SEC_TO_HOUR * ((itr + 1)->time - itr->time);
    }

    return Ah;
}

QString LogDataPoint::headerString()
{
    return QString("TIME;STEP;VOLTAGE;CURRENT;TEMP");
}
