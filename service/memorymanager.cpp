#include "memorymanager.h"

#include <service/binary/binaryservice.h>

namespace {
constexpr const int SIZE_MEMORY = 4;
constexpr const int MAX_LENGTH_MEMORY = 5;
constexpr const int MAX_LENGTH_MEMORY_DATA = 10;
}

MemoryManager::MemoryManager() :
    _currentMemoryAssembly("0"),
    _valuesByAddress( {} ){}

MemoryManager &MemoryManager::instance() {
    static MemoryManager memoryController;
    return memoryController;
}

QString MemoryManager::alloc() {
    const int nrAddressMemory = _currentMemoryAssembly.toInt() + SIZE_MEMORY;
    _currentMemoryAssembly = QString::number( nrAddressMemory );
    return _currentMemoryAssembly.rightJustified( MAX_LENGTH_MEMORY, '0' );
}

QString MemoryManager::allocValues( const QList<QString>& values) {

    QString valuesAlloc = "";

    for( const QString& currentValue : values ){
        valuesAlloc.append( currentValue.rightJustified( MAX_LENGTH_MEMORY_DATA, '0' ) );
    }

    const QString address = allocBinaryMemory();

    _valuesByAddress.insert( address, valuesAlloc );

    return address;
}

QString MemoryManager::getValuesByAddressMemory( const QString& address ) const {
    return _valuesByAddress.value( address, "" );
}

void MemoryManager::reset() {
    _currentMemoryAssembly = "0";
    _currentMemoryBinary = 0;
    _valuesByAddress.clear();
}

QString MemoryManager::allocBinaryMemory(){
    _currentMemoryBinary++;
    return BinaryService().toBinary( _currentMemoryBinary ).rightJustified( 5, '0' );
}
