#ifndef TERRITORY_H
#define TERRITORY_H

#include <QVariant>
#include <QDataStream>
#include <QString>
#include <QVector>
#include <QDateTime>
#include "Permission.h"
#include "TerritoryEvent.h"

class Territory
{
public:
    Territory();
    Territory(int id_value, QString name_value);
    int id() const;
    QString name();
    QVector<TerritoryEvent> events();
    void set_id(int id);
    void set_name(QString name);
    void add_event(TerritoryEvent event);
    void remove_event(TerritoryEvent event);
    QString list_name();
    TerritoryEvent last_out();
    TerritoryEvent last_change_assignment();
    TerritoryEvent last_enter();
    QDateTime last_out_date();
    QDateTime last_change_assignment_date();
    QDateTime last_enter_date();
    int holder_id();
    bool available();
private:
    int id_data;
    QString name_data;
    QVector<TerritoryEvent> events_data;
    friend QDataStream &operator << (QDataStream &, const Territory &);
    friend QDataStream &operator >> (QDataStream &, Territory &);
};
bool operator > (Territory const &a, Territory const &b);
bool operator < (Territory const &a, Territory const &b);
Q_DECLARE_METATYPE(Territory)
QDataStream &operator << (QDataStream &out, const Territory &territory);
QDataStream &operator >> (QDataStream &in, Territory &territory);
#endif // TERRITORY_H
