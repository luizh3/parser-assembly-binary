#ifndef TIPOOPERACAOASSEMBLYENUM_H
#define TIPOOPERACAOASSEMBLYENUM_H

enum class TipoOperacaoAssemblyEnum {
    UNDEFINED,
    SUB,
    ADD,
    LOAD,
    STORE,
    MOV,
    JUMP,
    LABEL,
    BEQ,
    BGE,
    BGT,
    BLE,
    BLT,
    BNE,
    BR
};

#endif // TIPOOPERACAOASSEMBLYENUM_H
