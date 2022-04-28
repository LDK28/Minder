#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <BlockImage.h>

class Arrow : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 2 };
    Arrow(BlockImage *parentBlock = nullptr, BlockImage *childBlock = nullptr,
          QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void changeChildBlock(BlockImage * newChildBlock);
    void changeParentBlock(BlockImage * newParentBlock);
    BlockImage *getParentBlock() const { return parentBlock; }
    BlockImage *getChildBlock() const { return childBlock; }

    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    BlockImage *parentBlock;
    BlockImage *childBlock;
    QPolygonF arrowHead;
};

#endif // ARROW_H
