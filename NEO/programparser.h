#ifndef PROGRAMPARSER_H
#define PROGRAMPARSER_H

#include <QObject>
#include "filehelper.h"
#include "programstep.h"

class ProgramParser : public QObject
{
    Q_OBJECT
public:
    explicit ProgramParser(QObject *parent = 0);

    Q_PROPERTY(QVariant programName READ getProgramName)
    QVariant getProgramName() const;

    Q_PROPERTY(QVariant wordCount READ getWordCount)
    QVariant getWordCount() const;

    Q_PROPERTY(QVariant programData READ getProgramData)
    QVariant getProgramData() const;

    Q_INVOKABLE void parse(QString fileName);

signals:

public slots:

private:
    char programName[8];
    short wordCount;
    std::vector<char> programData;

    std::vector<char> loadedBytes;
    std::vector<ProgramStep> steps;

    void parseProgramName();
    void parseProgramSteps();
    void parseWordCount();
    void convertProgram();
};

#endif // PROGRAMPARSER_H
