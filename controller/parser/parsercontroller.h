#ifndef PARSERCONTROLLER_H
#define PARSERCONTROLLER_H

#include <QObject>

class ParserController : public QObject {
    Q_OBJECT
    Q_PROPERTY( QString dsCodeInputC READ dsCodeInputC NOTIFY dsCodeInputCChanged )
    Q_PROPERTY( QString dsCodeResultUla READ dsCodeResultUla NOTIFY dsCodeResultUlaChanged )
    Q_PROPERTY( QString dsCodeResultBinary READ dsCodeResultBinary NOTIFY dsCodeResultBinaryChanged )
    Q_PROPERTY( QString dsCodeResultAssembly READ dsCodeResultAssembly NOTIFY dsCodeResultAssemblyChanged )
public:
    const QString& dsCodeResultUla() const;
    void setDsCodeResultUla( const QString &newDsCodeResultUla );

    const QString& dsCodeResultBinary() const;
    void setDsCodeResultBinary( const QString &newDsCodeResultBinary );

    const QString& dsCodeResultAssembly() const;
    void setDsCodeResultAssembly( const QString &newDsCodeResultAssembly );

    const QString& dsCodeInputC() const;
    void setDsCodeInputC( const QString &newDsCodeInputC );

public slots:
    void makeParser( QString dsCodeInC );
signals:
    void dsCodeResultUlaChanged();
    void dsCodeResultBinaryChanged();
    void dsCodeResultAssemblyChanged();
    void dsCodeInputCChanged();

    void parserFnished() const;

private:
    QString _dsCodeInputC;
    QString _dsCodeResultUla;
    QString _dsCodeResultBinary;
    QString _dsCodeResultAssembly;
};

#endif // PARSERCONTROLLER_H
