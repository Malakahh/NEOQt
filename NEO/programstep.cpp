#include "programstep.h"

#include <QDebug>

//Weird data encoding
#define VOLTAGE_BYTE_LOW 0
#define VOLTAGE_BYTE_HIGH 1
#define CURRENT_BYTE_LOW 2
#define CURRENT_BYTE_HIGH 3
#define VOLTAGE_LOW_JUMP_STEP 4
#define VOLTAGE_HIGH_JUMP_STEP 5
#define VOLTAGE_LOW_JUMP_BYTE_LOW 6
#define VOLTAGE_LOW_JUMP_BYTE_HIGH 7
#define VOLTAGE_HIGH_JUMP_BYTE_LOW 8
#define VOLTAGE_HIGH_JUMP_BYTE_HIGH 9
#define CURRENT_LOW_JUMP_STEP 10
#define CURRENT_HIGH_JUMP_STEP 11
#define CURRENT_LOW_JUMP_BYTE_LOW 12
#define CURRENT_LOW_JUMP_BYTE_HIGH 13
#define CURRENT_HIGH_JUMP_BYTE_LOW 14
#define CURRENT_HIGH_JUMP_BYTE_HIGH 15
#define RELATIVE_TIME_JUMP_STEP 16
#define ABSOLUTE_TIME_JUMP_STEP 17
#define RELATIVE_TIME_0 20
#define RELATIVE_TIME_1 21
#define RELATIVE_TIME_2 22
#define ABSOLUTE_TIME_0 24
#define ABSOLUTE_TIME_1 25
#define ABSOLUTE_TIME_2 26
#define C 28 //LED Charge
#define F 29 //Flash LEDs
#define E 30 //LED Error
#define T 31 //Timer
#define S 32 //Output switch

ProgramStep::ProgramStep()
{

}

bool ProgramStep::createProgramStep(char *data, unsigned int len, ProgramStep &step)
{
    if (data[VOLTAGE_BYTE_LOW] == static_cast<char>(0xFF) || data[CURRENT_BYTE_LOW] == static_cast<char>(0xFF))
        return false;

    std::copy(data,
              data + len,
              step.data);

    step.len = len;

    return true;
}

int ProgramStep::calcFinalWordCount()
{
    int cntWords = 2; // We have a defined minimum of two WORDS
    char toTest[6] = {
        CURRENT_LOW_JUMP_STEP,
        CURRENT_HIGH_JUMP_STEP,
        VOLTAGE_LOW_JUMP_STEP,
        VOLTAGE_HIGH_JUMP_STEP,
        RELATIVE_TIME_JUMP_STEP,
        ABSOLUTE_TIME_JUMP_STEP
    };

    for (int i = 0; i < 6; i++)
    {
        if (isSet(toTest[i]))
        {
            cntWords++;

            //These require two WORDS, as per the documentation
            if (toTest[i] == RELATIVE_TIME_JUMP_STEP || toTest[i] == ABSOLUTE_TIME_JUMP_STEP)
            {
                cntWords++;
            }
        }
    }

    return cntWords;
}

bool ProgramStep::isSet(char index)
{
    bool b = this->data[index] != (char)0xFF;

    return b;
}

void ProgramStep::convert(short* words, unsigned int& len)
{
    int itr = 0;

    words[itr++] = generateWord_VoltageSetPoint();
    words[itr++] = generateWord_CurrentSetPoint();

    if (isSet(ABSOLUTE_TIME_JUMP_STEP))
    {
        itr += generateWords_AbsoluteJump(words, itr);
    }

    if (isSet(RELATIVE_TIME_JUMP_STEP))
    {
        itr += generateWords_RelativeJump(words, itr);
    }

    if (isSet(VOLTAGE_HIGH_JUMP_STEP))
    {
        words[itr++] = generateWord_VoltageHighJump();
    }

    if (isSet(VOLTAGE_LOW_JUMP_STEP))
    {
        words[itr++] = generateWord_VoltageLowJump();
    }

    if (isSet(CURRENT_HIGH_JUMP_STEP))
    {
        words[itr++] = generateWord_CurrentHighJump();
    }

    if (isSet(CURRENT_LOW_JUMP_STEP))
    {
        words[itr++] = generateWord_CurrentLowJump();
    }

    len = itr;
}

short ProgramStep::generateWord_VoltageSetPoint()
{
    short word = 0;

    word |= this->data[VOLTAGE_BYTE_HIGH] & 0x03;
    word |= isSet(CURRENT_LOW_JUMP_STEP) << 2;
    word |= isSet(CURRENT_HIGH_JUMP_STEP) << 3;
    word |= isSet(VOLTAGE_LOW_JUMP_STEP) << 4;
    word |= isSet(VOLTAGE_HIGH_JUMP_STEP) << 5;
    word |= isSet(RELATIVE_TIME_JUMP_STEP) << 6;
    word |= isSet(ABSOLUTE_TIME_JUMP_STEP) << 7;

    word |= this->data[VOLTAGE_BYTE_LOW] << 8;

    return word;
}

short ProgramStep::generateWord_CurrentSetPoint()
{
    short word = 0;

    word |= this->data[CURRENT_BYTE_HIGH] & 0x03;
    word |= isSet(C) << 2;
    word |= isSet(F) << 3;
    word |= isSet(E) << 4;
    word |= isSet(S) << 5;
    word |= isSet(T) << 6;

    word |= this->data[CURRENT_BYTE_LOW] << 8;

    return word;
}

int ProgramStep::generateWords_TimeJump(short* arr, int begin, char step, char b0, char b1, char b2)
{
    arr[begin] = (this->data[step] & 0x3F) << 2; //Because... reason. Documentation states this needs to be the case
    arr[begin] |= this->data[b0] << 8;

    arr[begin + 1] = this->data[b2];
    arr[begin + 1] |= this->data[b1] << 8;

    return 2;
}

int ProgramStep::generateWords_AbsoluteJump(short* arr, int begin)
{
    return generateWords_TimeJump(arr,
                                  begin,
                                  ABSOLUTE_TIME_JUMP_STEP,
                                  ABSOLUTE_TIME_0,
                                  ABSOLUTE_TIME_1,
                                  ABSOLUTE_TIME_2);
}

int ProgramStep::generateWords_RelativeJump(short* arr, int begin)
{
    return generateWords_TimeJump(arr,
                                  begin,
                                  RELATIVE_TIME_JUMP_STEP,
                                  RELATIVE_TIME_0,
                                  RELATIVE_TIME_1,
                                  RELATIVE_TIME_2);
}

short ProgramStep::generateWord_BasicJump(char step, char high, char low)
{
    short word = 0;

    word |= (this->data[step] & 0x3F) << 2; //6 bit
    word |= this->data[high] & 0x03;

    word |= this->data[low] << 8;

    return word;
}

short ProgramStep::generateWord_VoltageHighJump()
{
    return generateWord_BasicJump(VOLTAGE_HIGH_JUMP_STEP,
                                  VOLTAGE_HIGH_JUMP_BYTE_HIGH,
                                  VOLTAGE_HIGH_JUMP_BYTE_LOW);
}

short ProgramStep::generateWord_VoltageLowJump()
{
    return generateWord_BasicJump(VOLTAGE_LOW_JUMP_STEP,
                                  VOLTAGE_LOW_JUMP_BYTE_HIGH,
                                  VOLTAGE_LOW_JUMP_BYTE_LOW);
}

short ProgramStep::generateWord_CurrentHighJump()
{
    return generateWord_BasicJump(CURRENT_HIGH_JUMP_STEP,
                                  CURRENT_HIGH_JUMP_BYTE_HIGH,
                                  CURRENT_HIGH_JUMP_BYTE_LOW);
}

short ProgramStep::generateWord_CurrentLowJump()
{
    return generateWord_BasicJump(CURRENT_LOW_JUMP_STEP,
                                  CURRENT_LOW_JUMP_BYTE_HIGH,
                                  CURRENT_LOW_JUMP_BYTE_LOW);
}

