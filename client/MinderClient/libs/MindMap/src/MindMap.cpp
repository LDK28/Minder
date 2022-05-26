#include "MindMap.h"
#include "ui_MindMap.h"

MindMap::MindMap(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::MindMap),
    factor(1),
    baseFactor(1),
    selectedBlock(nullptr),
    newBlock(nullptr)
{
    qDebug() <<"Mind map ctor";

    /////////UI///////
    ui->setupUi(this);

    ////////Scene////////
    scene = new QGraphicsScene(this);
    ui->graphicsViewMindMap->setScene(scene);
    ui->graphicsViewMindMap->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    initConnections();
}

MindMap::~MindMap()
{
    delete ui;
}

void MindMap::initConnections()
{
    connect(scene, &QGraphicsScene::selectionChanged, this, &MindMap::changeSelectedBlock);
}

void MindMap::wheelEvent(QWheelEvent *event)
{
    qDebug() << "MindMap: whell event " << event->angleDelta();

    if(event->modifiers() & Qt::ControlModifier)
    {
        if(event->angleDelta().y() < 0)
        {
            changeScale(wheelZoomMinusDeltaScalePercent);
        }
        else
        {
            changeScale(wheelZoomPlusDeltaScalePercent);
        }
    }
    else
    {
        QFrame::wheelEvent(event);
    }
}

void MindMap::setScale(const double newScalePerc)
{
    qDebug() << "MindMap : Set scale " << newScalePerc;

    factor = newScalePerc / (baseFactor * 100);
    baseFactor *= factor;
    ui->graphicsViewMindMap->scale(factor, factor);
    qDebug() << factor << baseFactor;
    emit scaleChanged(baseFactor);
}

void MindMap::changeScale(const double dscalePerc)
{
    qDebug() << "MindMap : Change scale " << dscalePerc;

    factor = dscalePerc > 0 ? 1 + dscalePerc / 100 :  1 / (1 - dscalePerc / 100);
    baseFactor *= factor;
    ui->graphicsViewMindMap->scale(factor, factor);
    emit scaleChanged(baseFactor);
}

void MindMap::updateMindMap(const ViewDataStructures::MindMapData &data)
{
    qDebug() << "MinaMap: update mind map image";

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

void MindMap::drawNewBlock(const ViewDataStructures::Block &block)
{
    qDebug() << "MindMap: draw new block";

    newBlock = new BlockImage(block);

    newBlock->setFlag(QGraphicsTextItem::ItemIsMovable, true);
    newBlock->block.parentId = selectedBlock ? selectedBlock->block.id : 0;
    newBlock->setPos(selectedBlock ? selectedBlock->pos() + selectedBlock->boundingRect().bottomLeft() + QPointF(0, 30) : QPointF(30, 0));

    scene->addItem(newBlock);
    addArrow(newBlock);
}

void MindMap::setNewBlockId(const size_t newBlockId)
{
    qDebug() << "MindMap: get new block id";

    newBlock->block.id = newBlockId;

    blocks.append(newBlock);
    blocksMap.insert(newBlock->block.id, newBlock);
    newBlock->setFlag(QGraphicsTextItem::ItemIsSelectable, true);

    newBlock = nullptr;
}

void MindMap::drawBlock(const ViewDataStructures::Block &block)
{
    qDebug() << "MindMap: draw block";

    BlockImage *blockImage = new BlockImage(block);

    blocks.append(blockImage);
    blocksMap.insert(blockImage->block.id, blockImage);

    scene->addItem(blockImage);
    addArrow(blockImage);
}

void MindMap::addArrow(BlockImage *blockImage)
{
    qDebug() << "MindMap: add arrow" << blockImage->block.id << " " << blockImage->block.parentId;

    if(blockImage->block.parentId > 0)
    {
        Arrow *newArrow = new Arrow(blocksMap[blockImage->block.parentId], blockImage);

        blocksMap[blockImage->block.parentId]->arrows.append(newArrow);
        blockImage->arrows.append(newArrow);

        newArrow->updatePosition();
        scene->addItem(newArrow);
    }
}

void MindMap::blockWasDeleted(const size_t id)
{
    qDebug() << "MindMap: Delete selected block (another user)";
    BlockImage *targetBlock = blocksMap[id];
    deleteBlock(&targetBlock);
}

void MindMap::deleteSelectedBlock()
{
    qDebug() << "MindMap: Delete selected block (this user)";

    if(selectedBlock == nullptr)
    {
        QMessageBox::about(this, "Note", "Select block at first");
        return;
    }
    qDebug() << " " << selectedBlock->block.id;

    ViewDataStructures::MindMapData changedBlocks = deleteBlock(&selectedBlock);

    // отправка изменений на сервер
    emit transmitDeletedBlock(changedBlocks);

}

ViewDataStructures::MindMapData MindMap::deleteBlock(BlockImage **targetBlock)
{
    assert(targetBlock && *targetBlock);
    ViewDataStructures::MindMapData changedBlocks;
    changedBlocks.blocks.append((*targetBlock)->block); // удаляемый блок

    // Удаление стрелки от предка удаляемого блока к удаляемому блоку
    if((*targetBlock)->block.parentId != 0)
    {
        for(int i = 0; i < blocksMap[(*targetBlock)->block.parentId]->arrows.count(); ++i)
        {
            if(blocksMap[(*targetBlock)->block.parentId]->arrows[i]->getChildBlock() == (*targetBlock))
            {
                Arrow *arrow = blocksMap[(*targetBlock)->block.parentId]->arrows.at(i);
                blocksMap[(*targetBlock)->block.parentId]->arrows.removeAt(i);
                scene->removeItem(arrow);
                delete arrow;
                break;
            }
        }
    }

    //изменение потомков удаляемого блока
    for(int i = 0; i < blocks.count(); ++i)
    {
        if(blocks[i]->block.parentId == (*targetBlock)->block.id)
        {
            // Изменеине предка
            blocks[i]->block.parentId = (*targetBlock)->block.parentId;
            changedBlocks.blocks.append(blocks[i]->block); // изменненный блок

            // удаление стрелки от удаляемого к его потомку
            for(int j = 0; j < blocks[i]->arrows.count(); ++j)
            {
                if(blocks[i]->arrows[j]->getParentBlock() == (*targetBlock))
                {
                    if((*targetBlock)->block.parentId != 0)
                    {
                        blocks[i]->arrows[j]->changeParentBlock(blocksMap[(*targetBlock)->block.parentId]);
                    }
                    else
                    {
                        Arrow *arrow = blocks[i]->arrows[j];
                        blocks[i]->arrows.removeAt(j);
                        scene->removeItem(arrow);
                        delete arrow;
                    }
                    break;
                }
            }

        }
    }

    // удаление выбранного блока
    blocks.removeOne((*targetBlock));
    blocksMap.remove((*targetBlock)->block.id);
    scene->removeItem((*targetBlock));
    delete (*targetBlock);
    (*targetBlock) = nullptr;

    return changedBlocks;
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
