#include "blockimage.h"
#include "arrow.h"

BlockImage::BlockImage(const Block &b): QGraphicsTextItem(b.text),  block(b)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, false);

    setTextWidth(QFontMetrics(block.textFont).horizontalAdvance('O') * std::max(sqrt(block.text.length()), 10.));
    setFont(block.textFont);
    setDefaultTextColor(block.textColor);
    setPos(block.position);
}

void BlockImage::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->modifiers())
    {
        event->ignore();
    }
    else
    {
        qDebug() << "Click on block" << block.id;
        QGraphicsItem::mousePressEvent(event);
        update(boundingRect());
    }
}

void BlockImage::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    for(int i = 0; i < arrows.count(); ++i)
    {
        if(arrows[i])
        {
            arrows[i]->updatePosition();
        }
    }
}

void BlockImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(block.borderColor, 3));

    if(!isSelected())
        painter->setBrush(block.backgroundColor);
    else
        painter->setBrush(block.backgroundColor.darker());

    painter->drawRect(boundingRect());
    QGraphicsTextItem::paint(painter, option, widget);
}
