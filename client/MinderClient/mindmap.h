#ifndef MINDMAP_H
#define MINDMAP_H
#include <QFrame>

#include <QWidget>
#include <QList>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMap>
#include <QWheelEvent>

#include "datastructures.h"
#include "newblockcreationwindow.h"
#include "blockimage.h"
#include "arrow.h"

namespace Ui {
class MindMap;
}

class MindMap : public QFrame
{
    Q_OBJECT

public:
    explicit MindMap(QWidget *parent = nullptr);
    ~MindMap();
    void wheelEvent(QWheelEvent *event) override;

    // Interface
signals:
    void transmitNewBlock(const Block & newBlock);

public:
    void setNewBlockId(const long newBlockId);
    void drawNewBlock(const Block &block);
    void updateMindMap(const MindMapData &data);

    // end Interface

private:
    void updateImage(const MindMapData &data);
    void addArrow(BlockImage *block);

private slots:
    void changeSelectedBlock();

private:
    Ui::MindMap *ui;
    QGraphicsScene *scene;

    QList<BlockImage *> blocks;
    QMap<int, BlockImage *> blocksMap;

    BlockImage *selectedBlock;
    BlockImage *newBlock;
};

#endif // MINDMAP_H
