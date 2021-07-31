#ifndef TERRITORYEVENT_H
#define TERRITORYEVENT_H

#include <QVariant>
#include <QDataStream>
#include <QDateTime>
#include "Permission.h"

class TerritoryEvent
{
public:
    TerritoryEvent();
    TerritoryEvent(int type_value, QDateTime date_value, QString note_value, int permission_id_value);
    bool out_type();
    bool change_assignment_type();
    bool enter_type();
    int type() const;
    QDateTime date() const;
    QString note() const;
    int permission_id() const;
    QString date_name();
    QString type_name();
    QString list_name();
private:
    int type_data;
    QDateTime date_data;
    QString note_data;
    int permission_id_data;
    friend QDataStream &operator << (QDataStream &, const TerritoryEvent &);
    friend QDataStream &operator >> (QDataStream &, TerritoryEvent &);
};
bool operator == (TerritoryEvent const &a, TerritoryEvent const &b);
Q_DECLARE_METATYPE(TerritoryEvent)
QDataStream &operator << (QDataStream &out, const TerritoryEvent &territory_event);
QDataStream &operator >> (QDataStream &in, TerritoryEvent &territory_event);
#endif // TERRITORYEVENT_H
