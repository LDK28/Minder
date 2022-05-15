#ifndef MINDMAP_H
#define MINDMAP_H

#include <QFrame>
#include <QWidget>
#include <QList>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMap>
#include <QWheelEvent>
#include <QMessageBox>

#include "DataStructures.h"
#include "NewBlockCreationWindow.h"
#include "BlockImage.h"
#include "Arrow.h"

namespace Ui {
class MindMap;
}

class MindMap : public QFrame
{
    Q_OBJECT

public:
    explicit MindMap(QWidget *parent = nullptr);
    ~MindMap();

    // Interface
signals:
    void transmitNewBlock(const ViewDataStructures::Block & newBlock);
    void transmitDeletedBlock(const ViewDataStructures::MindMapData & changedBlocks);
    void scaleChanged(const double scale);

public slots:
    void updateMindMap(const ViewDataStructures::MindMapData &data);
    void drawBlock(const ViewDataStructures::Block &block);
    void drawNewBlock(const ViewDataStructures::Block &newBlock);
    void setNewBlockId(const size_t newBlockId);
    void setScale(const double newScalePerc);
    void changeScale(const double dscalePerc);
    void deleteSelectedBlock();
    void blockWasDeleted(const size_t id);
    // end Interface


private:
    void addArrow(BlockImage *block);
    void initConnections();
    ViewDataStructures::MindMapData deleteBlock(BlockImage **targetBlock);

private slots:
    void changeSelectedBlock();

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    Ui::MindMap *ui;
    QGraphicsScene *scene;

    double factor;
    double baseFactor;

    QList<BlockImage *> blocks;
    QMap<int, BlockImage *> blocksMap;

    BlockImage *selectedBlock;
    BlockImage *newBlock;

    friend class test_MindMap;
};

#endif // MINDMAP_H
