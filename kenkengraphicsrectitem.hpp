#ifndef KENKEN_GRAPHICS_RECT_ITEM_HPP
#define KENKEN_GRAPHICS_RECT_ITEM_HPP

#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QWidget>
#include <QPen>
#include <QPainter>

#include "parser.hpp"

class KenkenGraphicsRectItem : public QGraphicsPolygonItem
{
    QVector<QRect> _cells;
    QString _text;
    QFont _font;
public:
    const static int Size = 100;

public:
    KenkenGraphicsRectItem() = default;
    explicit KenkenGraphicsRectItem(const Block *block,
                                    QGraphicsItem *parent = nullptr);

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif // KENKEN_GRAPHICS_RECT_ITEM_HPP
