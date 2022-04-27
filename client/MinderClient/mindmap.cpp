#include "mindmap.h"
#include "ui_mindmap.h"

MindMap::MindMap(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MindMap),
    selectedBlock(nullptr),
    newBlock(nullptr)
{
    /////////UI///////
    ui->setupUi(this);

    ////////Scene////////
    scene = new QGraphicsScene(this);
    ui->graphicsViewMindMap->setScene(scene);
    connect(scene, &QGraphicsScene::selectionChanged, this, &MindMap::changeSelectedBlock);
}

MindMap::~MindMap()
{
    delete ui;
}

void MindMap::wheelEvent(QWheelEvent *event)
{
    //    qDebug() << "MindMap: whell event " << event->angleDelta();

    ui->graphicsViewMindMap->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scale = 1.05;
    if(event->angleDelta().y() > 0)
    {
        ui->graphicsViewMindMap->scale(scale, scale);
    }
    else
    {
        ui->graphicsViewMindMap->scale(1 / scale, 1 / scale);
    }
    event->accept();
}

void MindMap::updateMindMap(const MindMapData &data)
{
    //    qDebug() << "MinaMap: update image";

    scene->clear();
    blocks.clear();
    blocksMap.clear();

    blocksMap.insert(0, nullptr);

    ///////Create view for all blocks//////////
    for(int i = 0; i < data.blocks.count(); ++i)
    {
        BlockImage *blockImage = new BlockImage(data.blocks[i]);

        blocks.append(blockImage);
        blocksMap.insert(blockImage->block.id, blockImage);

        scene->addItem(blockImage);
    }

    ///////Draw all arrows////////
    for(int i = 0; i < blocks.count(); ++i)
    {
        addArrow(blocks[i]);
    }

}

void MindMap::drawNewBlock(const Block &block)
{
    //    qDebug() << "MindMap: draw new block";

    newBlock = new BlockImage(block);

    newBlock->setFlag(QGraphicsTextItem::ItemIsMovable, true);
    newBlock->block.parentId = selectedBlock ? selectedBlock->block.id : 0;
    newBlock->setPos(selectedBlock ? selectedBlock->pos() + selectedBlock->boundingRect().bottomLeft() + QPointF(0, 30) : QPointF(30, 0));

    scene->addItem(newBlock);
    addArrow(newBlock);
}

void MindMap::addArrow(BlockImage *blockImage)
{
    qDebug() << "MindMap: add arrow";

    if(blockImage->block.parentId > 0)
    {
        Arrow *newArrow = new Arrow(blocksMap[blockImage->block.parentId], blockImage);

        blocksMap[blockImage->block.parentId]->arrows.append(newArrow);
        blockImage->arrows.append(newArrow);

        newArrow->updatePosition();
        scene->addItem(newArrow);
    }
}

void MindMap::changeSelectedBlock()
{
    selectedBlock = scene->selectedItems().count() ?
                qgraphicsitem_cast<BlockImage *>(scene->selectedItems().at(0))
              :
                nullptr;

    if(newBlock)
    {
        if(selectedBlock == newBlock)
        {
            qDebug() << "Start moving new block";

            newBlock->setFlag(QGraphicsItem::ItemIsMovable, true);
        }
        else
        {
            qDebug() << "Stop moving new block";

            newBlock->setFlag(QGraphicsItem::ItemIsMovable, false);

            // send new block
            newBlock->block.position = QPoint(newBlock->pos().toPoint());
            newBlock->setFlag(QGraphicsTextItem::ItemIsSelectable, false);

            emit transmitNewBlock(newBlock->block);
            //

            qDebug() << "   Selected block: " << (selectedBlock ? selectedBlock->block.id : 0);
        }
    }
    else
    {
        qDebug() << "Selected block: " << (selectedBlock ? selectedBlock->block.id : 0);
    }
}

void MindMap::setNewBlockId(const long newBlockId)
{
    qDebug() << "MindMap: get new block id";

    newBlock->block.id = newBlockId;

    blocks.append(newBlock);
    blocksMap.insert(newBlock->block.id, newBlock);
    newBlock->setFlag(QGraphicsTextItem::ItemIsSelectable, true);

    newBlock = nullptr;
}

void MindMap::drawBlock(const Block &block)
{

    BlockImage *blockImage = new BlockImage(block);

    blocks.append(blockImage);
    blocksMap.insert(blockImage->block.id, blockImage);

    scene->addItem(blockImage);
    addArrow(blockImage);
}
