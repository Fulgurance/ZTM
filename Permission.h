#ifndef PERMISSION_H
#define PERMISSION_H

#include <QVariant>
#include <QDataStream>
#include <QString>
#include <QVector>

class Permission
{
public:
    Permission();
    Permission(int id_value, QString name_value, QString mail_value);
    int id() const;
    QString name() const;
    QString mail() const;
    void set_id(int id);
    void set_name(QString name);
    void set_mail(QString mail);
    QVector<int> holded_territories() const;
    void add_territory(int id_value);
    void remove_territory(int id_value);
    QString list_name();
private:
    int id_data;
    QString name_data;
    QString mail_data;
    QVector<int> holded_territories_data;
    friend QDataStream &operator << (QDataStream &, const Permission &);
    friend QDataStream &operator >> (QDataStream &, Permission &);
};
bool operator == (Permission const &a, Permission const &b);
bool operator > (Permission const &a, Permission const &b);
bool operator < (Permission const &a, Permission const &b);
Q_DECLARE_METATYPE(Permission)
QDataStream &operator << (QDataStream &out, const Permission &permission);
QDataStream &operator >> (QDataStream &in, Permission &permission);
#endif // PERMISSION_H
