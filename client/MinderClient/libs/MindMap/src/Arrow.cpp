#include "Arrow.h"

#include <QPainter>
#include <QPen>
#include <QtMath>

Arrow::Arrow(BlockImage *parentBlock, BlockImage *childBlock,
             QGraphicsItem *parent) :
    parentBlock(parentBlock),
    childBlock(childBlock)
{
    Q_UNUSED(parent);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setZValue(-1000);
}


QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                  QWidget *)
{
    if (parentBlock->collidesWithItem(childBlock))
    {
        return;
    }

    QLinearGradient gradient(this->line().p1(), line().p2());
    gradient.setColorAt(0, parentBlock->block.borderColor);
    gradient.setColorAt(1, childBlock->block.borderColor);
    painter->setBrush(QBrush(gradient));
    painter->setPen(QPen(painter->brush(), 3));

    QTransform transformer;
    QPolygon childPolygon = transformer.mapToPolygon(childBlock->boundingRect().toRect());

    QPointF intersectPoint;

    for (int i = 1; i < childPolygon.count() + 1; ++i) {

        QPointF p1 = childPolygon.at(i % childPolygon.count()) + childBlock->pos();
        QPointF p2 = childPolygon.at((i - 1) % childPolygon.count()) + childBlock->pos();
        QLineF polyLine = QLineF(p1, p2);

        QLineF::IntersectionType intersectionType = polyLine.intersects(line(), &intersectPoint);

        if (intersectionType == QLineF::BoundedIntersection)
            break;
    }

    setLine(QLineF(line().p1() , intersectPoint));

    qreal arrowSize = 15;
    double angle = std::atan2(-line().dy(), line().dx());
    QPointF arrowP1 = line().p2() - QPointF(sin(angle + M_PI / 3) * arrowSize,
                                            cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line().p2() - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                            cos(angle + M_PI - M_PI / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p2() << arrowP1 << arrowP2;

    painter->drawPolygon(arrowHead, Qt::OddEvenFill);
    painter->drawLine(line());
}

void Arrow::changeParentBlock(BlockImage * newParentBlock)
{
    parentBlock = newParentBlock;
    updatePosition();
}

void Arrow::changeChildBlock(BlockImage * newChildBlock)
{
    childBlock = newChildBlock;
    updatePosition();
}

void Arrow::updatePosition()
{
    QLineF line(mapFromItem(parentBlock, parentBlock->boundingRect().width() / 2, parentBlock->boundingRect().height() / 2), mapFromItem(childBlock, childBlock->boundingRect().width() / 2, childBlock->boundingRect().height() / 2));
    setLine(line);
}
