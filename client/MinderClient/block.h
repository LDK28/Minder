#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include <QString>
#include <QPoint>

#include "datastructures.h"

class Block
{

public:
    Block();

    enum Type
    {
        NodeBlock,
        CommentBlock
    };

protected:
    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

protected:
    QPointF position;
    int height;
    int width;
    int type;

    QString text;
    QColor textColor;
    QColor borderColor;
    QColor backgroundCOlor;
//    User author;

};

#endif // BLOCK_H
