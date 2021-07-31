#include "Permission.h"

Permission::Permission()
{

}

Permission::Permission(int id_value, QString name_value, QString mail_value)
{
 id_data = id_value;
 name_data = name_value;
 mail_data = mail_value;
}

int Permission::id() const
{
 return id_data;
}

QString Permission::name() const
{
 return name_data;
}

QString Permission::mail() const
{
 return mail_data;
}

void Permission::set_id(int id)
{
 id_data = id;
}

void Permission::set_name(QString name)
{
 name_data = name;
}

void Permission::set_mail(QString mail)
{
 mail_data = mail;
}

QVector<int> Permission::holded_territories() const
{
 return holded_territories_data;
}
    
void Permission::add_territory(int id_value)
{
 holded_territories_data.append(id_value);
}
    
void Permission::remove_territory(int id_value)
{
 holded_territories_data.removeOne(id_value);
}

QString Permission::list_name()
{
 return QString(QString::number(id_data)+" - "+name_data);
}

QDataStream &operator << (QDataStream &out, const Permission &permission)
{
 out << permission.id_data
     << permission.name_data
     << permission.mail_data
     << permission.holded_territories_data;
 return out;
}

QDataStream &operator >> (QDataStream &in, Permission &permission)
{
 in >> permission.id_data;
 in >> permission.name_data;
 in >> permission.mail_data;
 in >> permission.holded_territories_data;
 return in;
}
