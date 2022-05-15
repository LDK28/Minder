#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <BlockImage.h>

class Arrow : public QGraphicsLineItem
{
public:
    explicit Arrow(BlockImage *parentBlock = nullptr, BlockImage *childBlock = nullptr,
          QGraphicsItem *parent = nullptr);

    void changeChildBlock(BlockImage * newChildBlock);
    void changeParentBlock(BlockImage * newParentBlock);
    BlockImage *getParentBlock() const { return parentBlock; }
    BlockImage *getChildBlock() const { return childBlock; }
    void updatePosition();


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

public:
    enum { Type = UserType + 2 };

private:
    BlockImage *parentBlock;
    BlockImage *childBlock;
    QPolygonF arrowHead;
};

#endif // ARROW_H
