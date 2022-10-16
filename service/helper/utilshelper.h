#ifndef UTILSHELPER_H
#define UTILSHELPER_H

#include <QVariant>
#include <QString>

class UtilsHelper {
public:
  static QString absolutePathApplication();
  static QString toAbsolutePath( const QList<QString>& directorys, const QString& path = absolutePathApplication() );
  static QVariant readValue( const QString pathValue );
  static QString pathConfigFile();

  static constexpr const char* DS_CONFIGS = "CONFIGS";
  static constexpr const char* FG_RUN_CODE = "FG_RUN_CODE";

};

#endif // UTILSHELPER_H
