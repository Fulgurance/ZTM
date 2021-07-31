#include "TerritoryEvent.h"
#include "ZTM.h"

using ZTM::date_string;

TerritoryEvent::TerritoryEvent()
{

}

TerritoryEvent::TerritoryEvent(int type_value, QDateTime date_value, QString note_value, int permission_id_value)
{
 type_data = type_value;
 date_data = date_value;
 note_data = note_value;
 permission_id_data = permission_id_value;
}

int TerritoryEvent::type() const
{
 return type_data;
}

QDateTime TerritoryEvent::date() const
{
 return date_data;
}

QString TerritoryEvent::note() const
{
 return note_data;
}

int TerritoryEvent::permission_id() const
{
 return permission_id_data;
}

bool TerritoryEvent::out_type()
{
 return ZTM::OutType==type_data;
}

bool TerritoryEvent::change_assignment_type()
{
 return ZTM::ChangeAssignmentType==type_data;
}

bool TerritoryEvent::enter_type()
{
 return ZTM::EnterType==type_data;
}

QString TerritoryEvent::date_name()
{
 return date_string(date_data.date());
}

QString TerritoryEvent::type_name()
{
 QString action;
 switch (type_data)
 {
  case ZTM::OutType:
  {
   action = "<font color=\"#ff7700\"><b>Sortie</b></font>";
   break;
  }
  case ZTM::ChangeAssignmentType:
  {
   action = "<font color=\"#0000ff\"><b>Réassignation</b></font>";
   break;
  }
  case ZTM::EnterType:
  {
   action = "<font color=\"#00dd00\"><b>Entrée</b></font>";
   break;
  }
 }
 return action;
}

QString TerritoryEvent::list_name()//Permission
{
 QString time = date().time().toString();
 QString date = date_name();
 QString type = type_name();
 QString note;
 if (note_data.isEmpty())
 {
  note = "Aucune";
 }
 else
 {
  note = note_data;
 }
 return ("<b>"+date+" à "+time+":</b><br>"+type+" par "+ZTM::load_permission_data(permission_id_data).name()+"<br><u>Note:</u> "+note+"<br><br>");
}

QDataStream &operator << (QDataStream &out, const TerritoryEvent &territory_event)
{
 out << territory_event.type_data
     << territory_event.date_data
     << territory_event.note_data
     << territory_event.permission_id_data;
 return out;
}

QDataStream &operator >> (QDataStream &in, TerritoryEvent &territory_event)
{
 in >> territory_event.type_data;
 in >> territory_event.date_data;
 in >> territory_event.note_data;
 in >> territory_event.permission_id_data;
 return in;
}
