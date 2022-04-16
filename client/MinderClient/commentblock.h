#ifndef COMMENTBLOCK_H
#define COMMENTBLOCK_H

#include "block.h"

class CommentBlock : public Block
{
public:
    CommentBlock();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // COMMENTBLOCK_H
