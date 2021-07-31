#include "LogEvent.h"
#include "ZTM.h"

using ZTM::territory_name;

LogEvent::LogEvent()
{

}

LogEvent::LogEvent(int id_value, TerritoryEvent event_value)
{
 territory_id=id_value;
 territory_event=event_value;
}

int LogEvent::id() const
{
 return territory_id;
}

TerritoryEvent LogEvent::event() const
{
 return territory_event;
}

QString LogEvent::warning_list_name()
{
 QString date = territory_event.date_name();
 return ("<font color=\"#ff0000\"><b>Le territoire n°"+QString::number(territory_id)+" sortit le "+date+" à "+territory_name(territory_id)+" n'est toujours pas rentré</b></font>");
}

QString LogEvent::list_name()
{
 return ("Territoire n°"+QString::number(territory_id)+" à "+territory_name(territory_id)+" par "+ZTM::load_permission_data(territory_event.permission_id()).name());
}
