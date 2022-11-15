#include "labelmanager.h"

LabelManager::LabelManager() :
    _resultLastOperation( false ),
    _tpLabelJump( TypeLabelJumpEnum::NONE ),
    _nrCurrentLabel(0){}

LabelManager& LabelManager::instance() {
    static LabelManager labelManger;
    return labelManger;
}

QString LabelManager::getDsNextLabel() {
    _nrCurrentLabel++;
    return QString::number( _nrCurrentLabel );
}

const QString &LabelManager::dsCurrentLabel() const {
    return _dsCurrentLabel;
}

void LabelManager::setDsCurrentLabel(const QString &newDsCurrentLabel) {
    _dsCurrentLabel = newDsCurrentLabel;
}

bool LabelManager::hasLabelActive() const {
    return _tpLabelJump != TypeLabelJumpEnum::NONE;
}

bool LabelManager::isLabelSkip() {
    return hasLabelActive();
}

LabelManager::TypeLabelJumpEnum LabelManager::tpLabelJump() const {
    return _tpLabelJump;
}

void LabelManager::setTpLabelJump( TypeLabelJumpEnum newTpLabelJump ) {
    _tpLabelJump = newTpLabelJump;
}

void LabelManager::reset() {
    _nrCurrentLabel = 0;
    _tpLabelJump = TypeLabelJumpEnum::NONE;
    _resultLastOperation = false;
}
