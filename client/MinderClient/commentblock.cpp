#include "commentblock.h"

CommentBlock::CommentBlock()
{
    type = Type::CommentBlock;
}

QRectF CommentBlock::boundingRect() const
{
    return QRectF();
}

void CommentBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

