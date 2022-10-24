#ifndef INSTRUCTIONHELPER_H
#define INSTRUCTIONHELPER_H

#include <QString>
#include <QRegularExpression>

class InstructionHelper {
public:
    static QRegularExpression regexNameVariable();

    static QList<QString> allTypes();
    static QList<QString> allOperators();
};
#endif // INSTRUCTIONHELPER_H
