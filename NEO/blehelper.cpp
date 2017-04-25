#include "blehelper.h"

BLEHelper::BLEHelper()
{

}

BLEHelper& BLEHelper::getInstance()
{
    static BLEHelper instance;

    return instance;
}
