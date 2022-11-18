#ifndef PARSERCONTROLLER_H
#define PARSERCONTROLLER_H

#include <QObject>

class ParserController : public QObject {
    Q_OBJECT
    Q_PROPERTY( QString dsCodeInputC READ dsCodeInputC NOTIFY dsCodeInputCChanged )
    Q_PROPERTY( QString dsCodeResultUla READ dsCodeResultUla NOTIFY dsCodeResultUlaChanged )
    Q_PROPERTY( QString dsCodeResultBinary READ dsCodeResultBinary NOTIFY dsCodeResultBinaryChanged )
    Q_PROPERTY( QString dsCodeResultAssembly READ dsCodeResultAssembly NOTIFY dsCodeResultAssemblyChanged )
    Q_PROPERTY( QString dsSubtitle READ dsSubtitle NOTIFY dsSubtitleChanged )
    Q_PROPERTY( QString dsDetailsUla READ dsDetailsUla NOTIFY dsDetailsUlaChanged )
public:
    const QString& dsCodeResultUla() const;
    void setDsCodeResultUla( const QString &newDsCodeResultUla );

    const QString& dsCodeResultBinary() const;
    void setDsCodeResultBinary( const QString &newDsCodeResultBinary );

    const QString& dsCodeResultAssembly() const;
    void setDsCodeResultAssembly( const QString &newDsCodeResultAssembly );

    const QString& dsCodeInputC() const;
    void setDsCodeInputC( const QString &newDsCodeInputC );

    const QString &dsSubtitle() const;
    void setDsSubtitle(const QString &newDsSubtitle);

    const QString &dsDetailsUla() const;
    void setDsDetailsUla(const QString &newDsDetailsUla);

public slots:
    void makeParser( QString dsCodeInC );
signals:
    void dsCodeResultUlaChanged();
    void dsCodeResultBinaryChanged();
    void dsCodeResultAssemblyChanged();
    void dsCodeInputCChanged();
    void dsSubtitleChanged();
    void dsDetailsUlaChanged();

    void parserFnished() const;

private:
    QString _dsCodeInputC;
    QString _dsCodeResultUla;
    QString _dsCodeResultBinary;
    QString _dsCodeResultAssembly;
    QString _dsSubtitle;
    QString _dsDetailsUla;

    QString subtitleUpCode() const;

};

#endif // PARSERCONTROLLER_H
