#include "Territory.h"

Territory::Territory()
{

}

Territory::Territory(int id_value, QString name_value)
{
 id_data=id_value;
 name_data=name_value;
}

int Territory::id() const
{
 return id_data;
}

QString Territory::name()
{
 return name_data;
}

QVector<TerritoryEvent> Territory::events()
{
 return events_data;
}

void Territory::add_event(TerritoryEvent event)
{
 events_data.append(event);
}

void Territory::remove_event(TerritoryEvent event)
{
 events_data.remove(events_data.indexOf(event));
}

QString Territory::list_name()
{
 return QString(QString::number(id_data)+" - "+name_data);
}

TerritoryEvent Territory::last_out()
{
 if(events_data.isEmpty())
 {
  return TerritoryEvent();
 }
 else
 {
  TerritoryEvent last_out;
  foreach(TerritoryEvent event, events_data)
  {
   if (event.out_type() && event.date() > last_out.date())
   {
    last_out = event;
   }
  }
  return last_out;
 }
}

TerritoryEvent Territory::last_change_assignment()
{
 if(events_data.isEmpty())
 {
  return TerritoryEvent();
 }
 else
 {
  TerritoryEvent last_change;
  foreach(TerritoryEvent event, events_data)
  {
   if (event.change_assignment_type() && event.date() > last_change.date())
   {
    last_change = event;
   }
  }
  return last_change;
 }
}

TerritoryEvent Territory::last_enter()
{
 if(events_data.isEmpty())
 {
  return TerritoryEvent();
 }
 else
 {
  TerritoryEvent last_enter;
  foreach(TerritoryEvent event, events_data)
  {
   if (event.enter_type() && event.date() > last_enter.date())
   {
    last_enter = event;
   }
  }
  return last_enter;
 }
}

QDateTime Territory::last_out_date()
{
 return last_out().date();
}

QDateTime Territory::last_change_assignment_date()
{
 return last_change_assignment().date();
}

QDateTime Territory::last_enter_date()
{
 return last_enter().date();
}

int Territory::holder_id()
{
 if (available())
 {
  return 0;
 }
 else
 {
  if (last_out().date() > last_change_assignment().date())
  {
   return last_out().permission_id();
  }
  else
  {
   return last_change_assignment().permission_id();
  }
 }
}

bool Territory::available()
{
 return events_data.isEmpty() || last_enter_date() >= last_out_date();
}

void Territory::set_id(int id)
{
 id_data = id;
}

void Territory::set_name(QString name)
{
 name_data = name;
}

QDataStream &operator << (QDataStream &out, const Territory &territory)
{
 out << territory.id_data
     << territory.name_data
     << territory.events_data;
 return out;
}

QDataStream &operator >> (QDataStream &in, Territory &territory)
{
 in >> territory.id_data;
 in >> territory.name_data;
 in >> territory.events_data;
 return in;
}
