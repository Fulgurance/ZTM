#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDataStream>
#include <QString>

class Settings
{
public:
    Settings();
    Settings(QString language_name,QString congregation_name,int territory_duration_value,int historic_duration_value);
    QString version() const;
    QString language() const;
    QString congregation() const;
    int territory_duration() const;
    int historic_duration() const;
private:
    QString version_data;
    QString language_data;
    QString congregation_data;
    int territory_duration_data;
    int historic_duration_data;
    friend QDataStream &operator << (QDataStream &, const Settings &);
    friend QDataStream &operator >> (QDataStream &, Settings &);
};
Q_DECLARE_METATYPE(Settings)
QDataStream &operator << (QDataStream &out, const Settings &settings);
QDataStream &operator >> (QDataStream &in, Settings &settings);
#endif // SETTINGS_H
