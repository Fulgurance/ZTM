#include <QApplication>
#include "MainWindow.h"
#include "ZTM.h"

using ZTM::create_database;

bool operator == (Permission const &a, Permission const &b)
{
 return(a.id()==b.id() && a.name()==b.name() && a.mail()==b.mail() && a.holded_territories()==b.holded_territories());
}

bool operator == (TerritoryEvent const &a, TerritoryEvent const &b)
{
 return(a.type()==b.type() && a.date()==b.date() && a.note()==b.note() && a.permission_id()==b.permission_id());
}

bool operator > (Territory const &a, Territory const &b)
{
 return(a.id() > b.id());
}

bool operator < (Territory const &a, Territory const &b)
{
 return(a.id() < b.id());
}

bool operator > (Permission const &a, Permission const &b)
{
 return(a.id() > b.id());
}

bool operator < (Permission const &a, Permission const &b)
{
 return(a.id() < b.id());
}

bool operator > (LogEvent const &a, LogEvent const &b)
{
 return(a.event().date() > b.event().date());
}

bool operator < (LogEvent const &a, LogEvent const &b)
{
 return(a.event().date() < b.event().date());
}

int main(int argc, char *argv[])
{
 create_database();
 QApplication application(argc, argv);
 application.setStyle("fusion");
 MainWindow window;
 window.load_log();
 window.showMaximized();
 return application.exec();
}
