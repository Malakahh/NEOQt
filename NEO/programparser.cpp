#include "programparser.h"

#define META_DATA_SIZE 24

ProgramParser::ProgramParser(QObject *parent) : QObject(parent)
{

}

QVariant ProgramParser::getProgramName() const
{
    return QVariant(this->programName);
}

QVariant ProgramParser::getWordCount() const
{
    return QVariant(this->wordCount);
}

QVariant ProgramParser::getProgramData() const
{
    QVariant var;
    var.setValue(this->programData);

    return var;
}

void ProgramParser::parse(QString fileName)
{
    this->programData.clear();
    this->loadedBytes.clear();
    this->steps.clear();

    FileHelper& fileHelper = FileHelper::getInstance();
    fileHelper.loadProgram(fileName, this->loadedBytes);

    this->parseProgramName();
    this->parseProgramSteps();
    this->parseWordCount();
    this->convertProgram();
}

void ProgramParser::parseProgramName()
{    
    for (int i = 0; i < 8; i++)
    {
        this->programName[i] = this->loadedBytes[1 + i];
    }
}

void ProgramParser::parseProgramSteps()
{
    for (int i = META_DATA_SIZE; i < this->loadedBytes.size(); i += ProgramStep::stepSizeInBytes)
    {
        char bytes[ProgramStep::stepSizeInBytes];

        std::copy(this->loadedBytes.begin() + i,
                  this->loadedBytes.begin() + i + ProgramStep::stepSizeInBytes,
                  bytes);

        ProgramStep ps;
        if (ProgramStep::createProgramStep(bytes, ProgramStep::stepSizeInBytes, ps))
        {
            this->steps.push_back(ps);
        }
        else
        {
            break;
        }
    }
}

void ProgramParser::parseWordCount()
{
    short count = 0;

    for (int i = 0; i < steps.size(); i++)
    {
        count += this->steps[i].calcFinalWordCount();
    }

    this->wordCount = count;
}

void ProgramParser::convertProgram()
{
    for (int i = 0; i < steps.size(); i++)
    {
        short words[10];
        unsigned int len = 0;

        steps[i].convert(words, len);

        for (int k = 0; k < len; k++)
        {
            this->programData.push_back(words[k]);
            this->programData.push_back(words[k] >> 8);
        }
    }
}
