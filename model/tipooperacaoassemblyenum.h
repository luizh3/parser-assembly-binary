#ifndef TIPOOPERACAOASSEMBLYENUM_H
#define TIPOOPERACAOASSEMBLYENUM_H

#include <QObject>

class TipoOperacaoAssembly: public QObject {
    Q_OBJECT
public:
    enum class TipoOperacaoAssemblyEnum {
        UNDEFINED,
        LOAD,
        ADD,
        SUB,
        BGE,
        BLE,
        BEQ,
        BGT,
        BLT,
        BNE,
        JUMP,
        LABEL,
        MOV,
        MUL,
        DIV,
        STORE,
        BR
    };

    Q_ENUM( TipoOperacaoAssemblyEnum );

};

using TipoOperacaoAssemblyEnum = TipoOperacaoAssembly::TipoOperacaoAssemblyEnum;


#endif // TIPOOPERACAOASSEMBLYENUM_H
