#include "BlockImage.h"
#include "Arrow.h"

BlockImage::BlockImage(const ViewDataStructures::Block &b): QGraphicsTextItem(b.text),  block(b)
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
        setCursor(QCursor(Qt::ClosedHandCursor));
        update(boundingRect());
    }
}

void BlockImage::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(flags().testFlag(QGraphicsItem::ItemIsMovable))
    {
        setPos(mapToScene(event->scenePos()));
        QGraphicsItem::mouseMoveEvent(event);
    }

    for(int i = 0; i < arrows.count(); ++i)
    {
        if(arrows[i])
        {
            arrows[i]->updatePosition();
        }
    }
}

void BlockImage::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Release" << pos().toPoint();
    Q_UNUSED(event);
    setCursor(QCursor(Qt::ArrowCursor));
    block.position = pos().toPoint();
}

void BlockImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    bool selectionFlag = option->state & (QStyle::State_Selected);

    QStyleOptionGraphicsItem* style = const_cast<QStyleOptionGraphicsItem*>(option);
    style->state &= ~QStyle::State_Selected;

    if (selectionFlag)
    {
        painter->setBrush(block.backgroundColor.darker(120));
        painter->setPen(QPen(block.borderColor.darker(120), 4));
        painter->drawRoundedRect(boundingRect(), 5, 5);
    }

    else
    {
        painter->setPen(QPen(block.borderColor, 4));
        painter->setBrush(QBrush(block.backgroundColor));
        painter->drawRoundedRect(boundingRect(), 5, 5);
    }

    QGraphicsTextItem::paint(painter, option, widget);
}
