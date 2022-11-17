QT += quick quickcontrols2 gui concurrent core

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        controller/config/settingscontroller.cpp \
        controller/inputcodecontroller.cpp \
        controller/parser/parsercontroller.cpp \
        main.cpp \
        model/assembly/assemblyrowmodel.cpp \
        model/binary/binaryrowmodel.cpp \
        model/helper/instructionhelper.cpp \
        model/register/registermodel.cpp \
        model/result/parserresultmodel.cpp \
        model/resultmodel.cpp \
        model/ula/ulamodel.cpp \
        model/variable/conditionmodel.cpp \
        model/variable/variablemodel.cpp \
        service/assembly/assemblyservice.cpp \
        service/binary/binaryservice.cpp \
        service/exception/serviceexception.cpp \
        service/helper/utilshelper.cpp \
        service/inputcodeservice.cpp \
        service/label/labelmanager.cpp \
        service/log/logulamanager.cpp \
        service/memorymanager.cpp \
        service/parser/parserservice.cpp \
        service/register/registermanager.cpp \
        service/ula/ulaservice.cpp \
        service/variable/variablemanager.cpp \
        service/variable/variableservice.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    controller/config/settingscontroller.h \
    controller/inputcodecontroller.h \
    controller/parser/parsercontroller.h \
    model/assembly/assemblyrowmodel.h \
    model/binary/binaryrowmodel.h \
    model/helper/instructionhelper.h \
    model/register/registermodel.h \
    model/result/parserresultmodel.h \
    model/resultmodel.h \
    model/tipooperacaoassemblyenum.h \
    model/ula/ulamodel.h \
    model/variable/conditionmodel.h \
    model/variable/variablemodel.h \
    service/assembly/assemblyservice.h \
    service/binary/binaryservice.h \
    service/exception/serviceexception.h \
    service/helper/utilshelper.h \
    service/inputcodeservice.h \
    service/label/labelmanager.h \
    service/log/logulamanager.h \
    service/memorymanager.h \
    service/parser/parserservice.h \
    service/register/registermanager.h \
    service/ula/ulaservice.h \
    service/variable/variablemanager.h \
    service/variable/variableservice.h
