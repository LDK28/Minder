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


using namespace ViewDataStructures;

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
    void transmitDeletedBlock(const MindMapData & changedBlocks);
    void scaleChanged(const double scale);

public slots:
    void updateMindMap(const MindMapData &data);
    void drawBlock(const Block &block);
    void drawNewBlock(const Block &newBlock);
    void setNewBlockId(const size_t newBlockId);
    void deleteBlock();
    void setScale(const double newScalePerc);
    void changeScale(const double dscalePerc);

    // end Interface

private:
    void addArrow(BlockImage *block);
    void initConnections();

private slots:
    void changeSelectedBlock();

private:
    Ui::MindMap *ui;
    QGraphicsScene *scene;
    double factor;
    double baseFactor;

    QList<BlockImage *> blocks;
    QMap<int, BlockImage *> blocksMap;

    BlockImage *selectedBlock;
    BlockImage *newBlock;
};

#endif // MINDMAP_H
