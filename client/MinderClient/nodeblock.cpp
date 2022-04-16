#include "nodeblock.h"

NodeBlock::NodeBlock()
{
    type = Type::NodeBlock;
}

QRectF NodeBlock::boundingRect() const
{
    return QRectF();
}

void NodeBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
