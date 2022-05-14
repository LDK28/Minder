#ifndef BLOCKIMAGE_H
#define BLOCKIMAGE_H

#include <QGraphicsTextItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QPen>
#include <QRect>
#include <QFontMetrics>
#include <QFont>
#include <QList>

#include "DataStructures.h"

class Arrow;

class BlockImage: public QGraphicsTextItem
{
public:
    explicit BlockImage(const ViewDataStructures::Block &b);

    enum { Type = UserType + 1 };

    int type() const override { return Type; }
    void addArrow(Arrow *arrow) { this->arrows.append(arrow);}
    void deleteArrow(Arrow *arrow) { Q_UNUSED(arrow); }//this-> arrow = nullptr;};

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    ViewDataStructures::Block block;
    QList<Arrow *> arrows;
};

#endif // BLOCKIMAGE_H
