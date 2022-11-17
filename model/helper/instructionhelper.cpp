#include "instructionhelper.h"

QRegularExpression InstructionHelper::regexNameVariable() {
    return QRegularExpression( "^[a-zA-Z_$][a-zA-Z_$0-9]*$" );
}

QList<QString> InstructionHelper::allTypes() {
    return { "int" };
}

QList<QString> InstructionHelper::allOperators() {
    return { "=", "+", "-", "==", ">", "<", ">=", "<=", "!=", "/", "*" };
}
