#include <QObject>
#include <QTest>
#include <QSignalSpy>
#include <QGraphicsView>

#include "MindMap.h"
#include "DataStructures.h"


class test_MindMap : public QObject
{
    Q_OBJECT
public:
    explicit test_MindMap(QObject *parent = 0) : QObject(parent) {}

private slots: // должны быть приватными
    void test_changeScale();
    void test_setScale();
    void test_drawNewBlock();
    void test_drawBlock();
    void test_deleteSelectedBlock();
    void test_updateMindMap();
    
};


void test_MindMap::test_changeScale()
{
    MindMap mm;
    QSignalSpy spy(&mm, SIGNAL(scaleChanged(const double)));

    mm.changeScale(20);
    spy.wait(100);
    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments[0].toDouble() == 1.2);
    arguments.clear();

    mm.changeScale(-20);
    spy.wait(100);
    QCOMPARE(spy.count(), 1);
    arguments = spy.takeFirst();
    QVERIFY(arguments[0].toDouble() == 1.0);

    mm.changeScale(0);
    spy.wait(100);
    QCOMPARE(spy.count(), 1);
    arguments = spy.takeFirst();
    QVERIFY(arguments[0].toDouble() == 1.0);
}

void test_MindMap::test_setScale()
{
    MindMap mm;
    QSignalSpy spy(&mm, SIGNAL(scaleChanged(const double)));

    mm.setScale(200);
    spy.wait(100);
    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments[0].toDouble() == 2.0);
    arguments.clear();

    mm.setScale(100);
    spy.wait(100);
    QCOMPARE(spy.count(), 1);
    arguments = spy.takeFirst();
    QVERIFY(arguments[0].toDouble() == 1.0);

    mm.setScale(50);
    spy.wait(100);
    QCOMPARE(spy.count(), 1);
    arguments = spy.takeFirst();
    QVERIFY(arguments[0].toDouble() == 0.5);
}


void test_MindMap::test_drawNewBlock()
{
    MindMap mm;

    QSignalSpy spy(&mm, &MindMap::transmitNewBlock);


    mm.drawNewBlock(ViewDataStructures::Block(999, 998, QPoint(-100, -100), "dwadaw", QFont(), QColor(), QColor(), QColor(), 0));
    QTEST_ASSERT(mm.newBlock != nullptr);
    mm.newBlock->setSelected(true);
    mm.newBlock->setSelected(false);

    spy.wait(100);
    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    ViewDataStructures::Block newTestBl = qvariant_cast<ViewDataStructures::Block>(arguments[0]);

    QCOMPARE(newTestBl.id, (unsigned long)999);
    QCOMPARE(newTestBl.parentId, (unsigned long)0);

    mm.setNewBlockId(20);

    QTest::qWait(100);
    QCOMPARE(mm.blocks[0]->block.id, (unsigned long)20);

}


void test_MindMap::test_drawBlock()
{
    MindMap mm;

    mm.drawBlock(ViewDataStructures::Block(10, 0, QPoint(-100, -100), "dwadaw", QFont(), QColor(), QColor(), QColor(), 0));
    QCOMPARE(mm.blocks.at(0)->block.id, (unsigned long)10);
    QCOMPARE(mm.blocksMap[10], mm.blocks.at(0));
}

void test_MindMap::test_deleteSelectedBlock()
{
    MindMap mm;

    mm.drawBlock(ViewDataStructures::Block(10, 0, QPoint(-100, -100), "dwadaw", QFont(), QColor(), QColor(), QColor(), 0));
    mm.selectedBlock = mm.blocks.at(0);
    QSignalSpy spy(&mm, &MindMap::transmitDeletedBlock);

    mm.deleteSelectedBlock();
    spy.wait(100);
    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    ViewDataStructures::MindMapData data = qvariant_cast<ViewDataStructures::MindMapData>(arguments[0]);
    QCOMPARE(data.blocks.at(0).id, (unsigned long)10);
}

void test_MindMap::test_updateMindMap()
{
    MindMap mm;
    ViewDataStructures::MindMapData data;
    for(int i = 0; i < 2; ++i)
    {
        ViewDataStructures::Block b;
        b.id = i+1;
        b.parentId = i;
        b.text = QString::number(i + 1);
        data.blocks.append(b);
    }

    mm.updateMindMap(data);
    for(int i = 0; i < 2; ++i)
    {
        QCOMPARE(mm.blocks[i]->block.id, (unsigned long)i + 1);
        QCOMPARE(mm.blocks[i]->block.parentId, (unsigned long)i);
        QCOMPARE(mm.blocks[i]->block.text, QString::number(i + 1));

        QCOMPARE(mm.blocksMap[i + 1], mm.blocks[i]);
    }
}

#include "test_MindMap.moc"
