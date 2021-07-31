#ifndef LOGEVENT_H
#define LOGEVENT_H

#include "TerritoryEvent.h"

class LogEvent
{
public:
    LogEvent();
    LogEvent(int id_value, TerritoryEvent event_value);
    int id() const;
    TerritoryEvent event() const;
    QString warning_list_name();
    QString list_name();
private:
    int territory_id;
    TerritoryEvent territory_event;
};
bool operator > (LogEvent const &a, LogEvent const &b);
bool operator < (LogEvent const &a, LogEvent const &b);
#endif // LOGEVENT_H
