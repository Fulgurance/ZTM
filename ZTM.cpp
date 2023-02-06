#include "ZTM.h"
#include <QDir>
#include <QDataStream>
#include <iostream>

using std::sort;

namespace ZTM
{
 void create_database()
 {
  create_territories_database();
  create_permissions_database();
  create_settings_data();
 }

 void create_settings_data()
 {
  QString filepath = "Paramètres.ztm";
  QFile file(filepath);
  if(!QFileInfo::exists(filepath))
  {
   if (file.open(QIODevice::WriteOnly))
   {
    QDataStream flux(&file);
    Settings settings("Français","Dives sur mer",4,1);
    flux << settings;
    file.close();
   }
  }
 }

 void create_territories_database()
 {
  if(!QDir("Territoires").exists())
  {
   QDir().mkdir("Territoires");
  }
 }

 void create_permissions_database()
 {
  if(!QDir("Autorisations").exists())
  {
   QDir().mkdir("Autorisations");
  }
 }

 Territory load_territory_data(int id)
 {
  QFile file("Territoires/"+QString::number(id)+".ztm");
  Territory territory;
  if (file.open(QIODevice::ReadOnly))
  {
   QDataStream flux(&file);
   flux >> territory;
   file.close();
  }
  return territory;
 }

 Permission load_permission_data(int id)
 {
  QFile file("Autorisations/"+QString::number(id)+".ztm");
  Permission permission;
  if (file.open(QIODevice::ReadOnly))
  {
   QDataStream flux(&file);
   flux >> permission;
   file.close();
  }
  return permission;
 }

 Settings load_settings_data()
 {
  create_settings_data();
  QString filepath = "Paramètres.ztm";
  QFile file(filepath);
  Settings settings;
  if (file.open(QIODevice::ReadOnly))
  {
    QDataStream flux(&file);
    flux >> settings;
    file.close();
  }
  return settings;
 }

 QVector<Territory> load_territories_data()
 {
  QVector<Territory> data;
  QStringList filters;
  filters.append("*.ztm");
  QStringList files = QDir("Territoires/").entryList(filters);
  foreach(QString file_name, files)
  {
   file_name.remove(".ztm");
   Territory territory = load_territory_data(file_name.toInt());
   if (territory.available())
   {
    foreach(TerritoryEvent event, territory.events())
    {
     QDateTime date_range = event.date().addYears(load_settings_data().historic_duration());
     if (date_range.date() < QDate::currentDate())
     {
      territory.remove_event(event);
      QString filepath = "Territoires/"+QString::number(territory.id())+".ztm";
      QFile file(filepath);
      file.remove();
      if (file.open(QIODevice::WriteOnly))
      {
       QDataStream flux(&file);
       flux << territory;
       file.close();
      }
     }
    }
   }
   data.append(territory);
  }
  std::sort(data.begin(),data.end());
  return data;
 }

 QVector<Permission> load_permissions_data()
 {
  QVector<Permission> data;
  QStringList filters;
  filters.append("*.ztm");
  QStringList files = QDir("Autorisations/").entryList(filters);
  foreach(QString file_name, files)
  {
   file_name.remove(".ztm");
   Permission permission = load_permission_data(file_name.toInt());
   data.append(permission);
  }
  std::sort(data.begin(),data.end());
  return data;
 }

 QStringList territories_list()
 {
  QVector<Territory> data = load_territories_data();
  QStringList list;
  foreach(Territory territory, data)
  {
   list.append(territory.list_name());
  }
  return list;
 }

 QStringList available_territories_list()
 {
  QVector<Territory> data = load_territories_data();
  auto condition = [](Territory t1, Territory t2) {return t1.last_enter_date() < t2.last_enter_date();};
  sort(data.begin(),data.end(),condition);
  QStringList list;
  foreach(Territory territory, data)
  {
   if (territory.available())
   {  
    if (territory.last_enter_date().isNull())
    {
     list.append(territory.list_name()+" (Pas encore sortie)");
    }
    else
    {
     list.append(territory.list_name()+" (Rentré le "+date_string(territory.last_enter_date().date())+" à "+territory.last_enter_date().time().toString()+")");
    }
   }
  }
  return list;
 }

 QStringList out_territories_list()
 {
  QVector<Territory> data = load_territories_data();
  QStringList list;
  foreach(Territory territory, data)
  {
   if (!territory.available())
   {
    list.append(territory.list_name());
   }
  }
  return list;
 }

 QStringList permissions_list()
 {
  QVector<Permission> data = load_permissions_data();
  QStringList list;
  foreach(Permission permission, data)
  {
   list.append(permission.list_name());
  }
  return list;
 }

 QVector<LogEvent> load_warning_log_data()
 {
  QVector<Territory> data = load_territories_data();
  QVector<LogEvent> log_data;
  auto condition = [](LogEvent a, LogEvent b) { return a.event().date() < b.event().date();};
  foreach(Territory territory, data)
  {
   QDateTime date_range = (territory.last_out_date().addMonths(load_settings_data().territory_duration()));
   if (!territory.available() && (date_range.date() < QDate::currentDate()))
   {
    log_data.append(LogEvent(territory.id(),territory.last_out()));
   }
  }
  sort(log_data.begin(),log_data.end(), condition);
  return log_data;
 }

 QVector<LogEvent> load_log_data()
 {
  QVector<Territory> data = load_territories_data();
  QVector<LogEvent> log_data;
  auto condition = [](LogEvent a, LogEvent b) { return a.event().date() > b.event().date();};
  foreach(Territory territory, data)
  {
   foreach(TerritoryEvent event, territory.events())
   {
    log_data.append(LogEvent(territory.id(),event));
   }
  }
  sort(log_data.begin(),log_data.end(), condition);
  return log_data;
 }

 QString log_list()
 {
  QVector<LogEvent> warning_data = load_warning_log_data();
  QVector<LogEvent> data = load_log_data();
  QString warning_log;
  QString log;
  bool white_background(false);
  QString style("<thead><style>.white{background-color:white;}.Gainsboro{background-color:Gainsboro;}</style></thead>");
  foreach(LogEvent event, warning_data)
  {
   if (white_background)
   {
    warning_log.append("<tr class=whiter><td><font color=\"#ff0000\"><b>Attention !</b></font></td></tr><tr class=white><td>"+event.warning_list_name()+"</td></tr>");
    white_background = false;
   }
   else
   {
    warning_log.append("<tr class=Gainsboro><td><font color=\"#ff0000\"><b>Attention !</b></font></td></tr><tr class=Gainsboro><td>"+event.warning_list_name()+"</td></tr>");
    white_background = true;
   }
  }
  foreach(LogEvent event, data)
  {
   if (white_background)
   {
    log.append("<tr class=white><td><b>"+event.event().date_name()+" à "+event.event().date().time().toString()+":</b> "+event.event().type_name()+"</td></tr><tr class=white><td>"+event.list_name()+"</td></tr>");
    white_background = false;
   }
   else
   {
    log.append("<tr class=Gainsboro><td><b>"+event.event().date_name()+" à "+event.event().date().time().toString()+":</b> "+event.event().type_name()+"</td></tr><tr class=Gainsboro><td>"+event.list_name()+"</td></tr>");
    white_background = true;
   }
  }
  return (style+"<tbody><table cellspacing=\"0\" width=\"100%\">"+warning_log+log+"</table></tbody>");
 }

 QString print_period_list(QDate first_date, QDate second_date)
 {
  QVector<Territory> data = load_territories_data();
  QString list;
  list.append("<center><b>Assemblée locale de "+load_settings_data().congregation()+"<br>");
  list.append("Journal d'utilisation des territoires du "+date_string(first_date)+" au "+date_string(second_date)+"</b></center><br>");
  foreach(Territory territory, data)
  {
   bool to_be_printed = false;
   QString territory_text = "<br><u><b>Territoire n°"+QString::number(territory.id())+" - "+territory.name()+"</u></b><br>";
   QString events_text;
   foreach(TerritoryEvent event, territory.events())
   {
    if (event.date().date() >= first_date && event.date().date() <= second_date)
    {
     to_be_printed = true;
     QString date = event.date_name();
     QString action = event.type_name();
     events_text.append(date+": "+action+" par "+ZTM::load_permission_data(event.permission_id()).name()+"<br>");
    }
   }
   if (to_be_printed)
   {
    list.append(territory_text);
    list.append(events_text);
   }
  }
  return list;
 }

 QString territory_name(int id)
 {
  Territory territory = load_territory_data(id);
  return territory.name();
 }

 QString date_string(QDate date)
 {
  QString day = QString::number(date.day());
  QString month = QString::number(date.month());
  QString year = QString::number(date.year());
  QString text;
  if (date.month() < 10)
  {
   text = day+"/0"+month+"/"+year;
  }
  else
  {
   text = day+"/"+month+"/"+year;
  }
  return text;
 }
}
