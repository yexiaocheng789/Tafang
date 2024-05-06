#ifndef WAYPOINT_H
#define WAYPOINT_H
#include <qpoint.h>
#include <qpainter.h>
class Waypoint
{
public:
    Waypoint(QPoint pos);
    void setNextWayPoint(Waypoint *nextpoint);
    QPoint pos() ;
    Waypoint* nextWayPoint() ;
private:
    QPoint nowpos;
    Waypoint * nextpos;

};

#endif // WAYPOINT_H
