#include "utils.hpp"

uint qHash(const QPoint &key)
{
    return qHash(QPair<int, int>(key.x(), key.y()));
}

