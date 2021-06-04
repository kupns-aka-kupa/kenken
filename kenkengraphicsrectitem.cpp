#include "kenkengraphicsrectitem.hpp"

void KenkenGraphicsRectItem::paint(QPainter *painter,
                                   const QStyleOptionGraphicsItem *option,
                                   QWidget *widget)
{
    QRectF rect = boundingRect();
    painter->setFont(_font);
    painter->setPen(QPen(Qt::black, 5));
    painter->drawRect(rect);

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
        r.moveTo(p * _size);
        r.setSize({_size, _size});
        return r;
    };

    auto acc = [&](const QPolygon &i, const QRect &p)
    {
        return i.united(p);
    };

    std::transform(i.begin(), i.end(), std::back_inserter(_cells), rect);
    auto polygon = std::accumulate(_cells.begin(), _cells.end(), QPolygon(), acc);

    setPolygon(polygon);
}
