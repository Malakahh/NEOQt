#include "filebrowserdata.h"

FileBrowserData::FileBrowserData(QString fname, QObject *parent) : QObject(parent)
{
    this->fileName = fname;
}
