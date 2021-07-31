#ifndef ZTM_H
#define ZTM_H

#include "Territory.h"
#include "Permission.h"
#include "Settings.h"
#include "LogEvent.h"
#include <QString>

namespace ZTM
{
 const int OutType=0;
 const int ChangeAssignmentType=1;
 const int EnterType=2;
 const int HelpOutButtonText=0;
 const int HelpAssignmentButtonText=1;
 const int HelpEnterButtonText=2;
 const int HelpDatabaseButtonText=3;
 const int HelpSettingsButtonText=4;
 const int HelpPrintButtonText=5;
 void create_database();
 void create_settings_data();
 void create_log_data();
 void create_territories_database();
 void create_permissions_database();
 Territory load_territory_data(int id);
 Permission load_permission_data(int id);
 Settings load_settings_data();
 QVector<Territory> load_territories_data();
 QVector<Permission> load_permissions_data();
 QStringList territories_list();
 QStringList permissions_list();
 QStringList available_territories_list();
 QStringList out_territories_list();
 QString log_list();
 QString print_period_list(QDate first_date, QDate second_date);
 QString territory_name(int id);
 QString date_string(QDate date);
}

#endif
