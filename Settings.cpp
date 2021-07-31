#include "Settings.h"

Settings::Settings()
{

}

Settings::Settings(QString language_name,QString congregation_name,int territory_duration_value,int historic_duration_value)
{
 version_data="0.9.7";
 language_data=language_name;
 congregation_data=congregation_name;
 territory_duration_data=territory_duration_value;
 historic_duration_data=historic_duration_value;
}

QString Settings::version() const
{
 return version_data;
}

QString Settings::language() const
{
 return language_data;
}

QString Settings::congregation() const
{
 return congregation_data;
}

int Settings::territory_duration() const
{
 return territory_duration_data;
}

int Settings::historic_duration() const
{
 return historic_duration_data;
}

QDataStream &operator << (QDataStream &out, const Settings &settings)
{
 out << settings.version_data
     << settings.language_data
     << settings.congregation_data
     << settings.territory_duration_data
     << settings.historic_duration_data;
 return out;
}

QDataStream &operator >> (QDataStream &in, Settings &settings)
{
 in >> settings.version_data;
 in >> settings.language_data;
 in >> settings.congregation_data;
 in >> settings.territory_duration_data;
 in >> settings.historic_duration_data;
 return in;
}
