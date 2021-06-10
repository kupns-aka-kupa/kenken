#include "kenkengraphicsrectitem.hpp"

void KenkenGraphicsRectItem::paint(QPainter *painter,
                                   const QStyleOptionGraphicsItem *option,
                                   QWidget *widget)
{
    painter->setFont(_font);
    painter->setPen(QPen(Qt::black, 5));
    painter->drawPolygon(polygon());

    painter->drawText(_cells.front(), Qt::AlignLeft | Qt::AlignTop, _text);

    painter->setPen(QPen(Qt::gray, .5));
    foreach(auto cell, _cells)
    {
        painter->drawRect(cell);
    }
}

KenkenGraphicsRectItem::KenkenGraphicsRectItem(const Block *block, QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
    , _text(QString("%0 %1").arg(block->Total).arg(block->Op))
{
    _font.setPointSize(20);

    auto i = block->Indexes;

    auto rect = [&](const QPoint &p) -> QRect
    {
        QRect r;
        r.moveTo(p * Size);
        r.setSize({Size, Size});
        return r;
    };

    std::transform(i.begin(), i.end(), std::back_inserter(_cells), rect);

    QPainterPath path;

    /* TODO use std::for_each with bind instead of foreach
    {
        using namespace std::placeholders;
        std::for_each(_cells.begin(), _cells.end(), std::bind(&QPainterPath::addRect, path, _1));
    }
     */

    foreach(auto &cell, _cells)
        path.addRect(cell);

    setPolygon(path.simplified().toFillPolygon());
}
