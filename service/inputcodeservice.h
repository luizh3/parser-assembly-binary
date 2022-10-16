#ifndef INPUTCODESERVICE_H
#define INPUTCODESERVICE_H

#include <QString>

class InputCodeService {
public:
    void writeText( const QString& text ) const;
     QString readText() const;

     static constexpr const char* DS_DIRECTORY_FILE = "inputCode";
     static constexpr const char* DS_EXEC_FILE = "inputCodeExec.exe";
     static constexpr const char* DS_FILE_C = "init.c";
};

#endif // INPUTCODESERVICE_H
