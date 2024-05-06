#include "waypoint.h"
#include <qpoint.h>
#include <qpainter.h>
#include <qcolor.h>

Waypoint::Waypoint(QPoint pos)
    :nowpos(pos),nextpos(NULL)
{
}
void Waypoint::setNextWayPoint(Waypoint *nextpoint)
{
    nextpos=nextpoint;
}
QPoint Waypoint::pos(){return nowpos;}

Waypoint* Waypoint::nextWayPoint(){return nextpos;}
