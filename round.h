#ifndef ROUND_H
#define ROUND_H
#include <qpoint.h>
#include <qmath.h>
inline bool judgeCircle(QPoint point1, int radius1, QPoint point2, int radius2)
{
    const int xdif = point1.x() - point2.x();
    const int ydif = point1.y() - point2.y();
    const int distance = qSqrt(xdif * xdif + ydif * ydif);
    if (distance <= radius1 + radius2)
        return true;
    return false;
}
#endif
