#ifndef LABELMANAGER_H
#define LABELMANAGER_H

#include <QString>

#include <model/tipooperacaoassemblyenum.h>
#include <model/assembly/assemblyrowmodel.h>

class LabelManager {
public:

    enum class TypeLabelJumpEnum : int {
        NONE,
        JUMP,
        CONDICIONAL,
    };

    LabelManager();
    static LabelManager& instance();

    QString getDsNextLabel();

    const QString &dsCurrentLabel() const;
    void setDsCurrentLabel(const QString &newDsCurrentLabel);

    bool hasLabelActive() const;
    bool isLabelSkip();

    TypeLabelJumpEnum tpLabelJump() const;
    void setTpLabelJump(TypeLabelJumpEnum newTpLabelJump);

    void reset();

private:
    bool _resultLastOperation;
    TypeLabelJumpEnum _tpLabelJump;
    int _nrCurrentLabel;
    QString _dsCurrentLabel;
};

#endif // LABELMANAGER_H
