#include "mindmap.h"
#include "ui_mindmap.h"

MindMap::MindMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MindMap)
{
    ui->setupUi(this);
}

MindMap::~MindMap()
{
    delete ui;
}
