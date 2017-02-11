#ifndef PROGRAMSTEP_H
#define PROGRAMSTEP_H


class ProgramStep
{
public:
    ProgramStep();

    static const unsigned int stepSizeInBytes = 36;

    static bool createProgramStep(char* data, unsigned int len, ProgramStep& step);

    int calcFinalWordCount();
    void convert(short* words, unsigned int& len);

private:
    char data[ProgramStep::stepSizeInBytes];
    unsigned int len = 0;

    bool isSet(char index);
    short generateWord_VoltageSetPoint();
    short generateWord_CurrentSetPoint();
    int generateWords_TimeJump(short* arr, int begin, char step, char b0, char b1, char b2);
    int generateWords_AbsoluteJump(short* arr, int begin);
    int generateWords_RelativeJump(short* arr, int begin);
    short generateWord_BasicJump(char step, char high, char low);
    short generateWord_VoltageHighJump();
    short generateWord_VoltageLowJump();
    short generateWord_CurrentHighJump();
    short generateWord_CurrentLowJump();
};

#endif // PROGRAMSTEP_H
