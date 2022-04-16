#ifndef NODEBLOCK_H
#define NODEBLOCK_H

#include "block.h"

class NodeBlock : public Block
{
public:
    NodeBlock();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // NODEBLOCK_H
