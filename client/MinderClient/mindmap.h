#ifndef MINDMAP_H
#define MINDMAP_H

#include <QWidget>
#include <QList>

#include "block.h"
#include "nodeblock.h"
#include "commentblock.h"


namespace Ui {
class MindMap;
}

class MindMap : public QWidget
{
    Q_OBJECT

public:
    explicit MindMap(QWidget *parent = nullptr);
    ~MindMap();

signals:
    void getData();

private: //slots
    void updateImage(const QList<NodeBlock> &nodes, const QList<NodeBlock> &comments);
    void pasteNewBlock(const Block &block);

protected:
    QList<NodeBlock> nodes;
    QList<CommentBlock> comments;
    int zoomScale;
    double xOffset;
    double yOffset;
    double xLength;
    double yLength;

private:
    Ui::MindMap *ui;

};

#endif // MINDMAP_H
