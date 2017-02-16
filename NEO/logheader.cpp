#include "logheader.h"

LogHeader::LogHeader(QObject *parent) : QObject(parent)
{

}

LogHeader::LogHeader(const LogHeader& header)
{
    this->address = header.address;
    this->size = header.size;
}

QVariant LogHeader::getSize() const
{
    return QVariant(this->size);
}
