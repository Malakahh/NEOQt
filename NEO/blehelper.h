#ifndef BLEHELPER_H
#define BLEHELPER_H

#include "blecontroller.h"

class BLEHelper
{
public:
    BLEHelper();

    BLEHelper(BLEHelper const&) = delete;
    void operator=(BLEHelper const&) = delete;

    static BLEHelper& getInstance();

    BLEController* bleController;
};

#endif // BLEHELPER_H
