#include "toolspalette.h"
#include "ui_toolspalette.h"

ToolsPalette::ToolsPalette(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolsPalette)
{
    ui->setupUi(this);
    initConnections();
}

ToolsPalette::~ToolsPalette()
{
    delete ui;
}

void ToolsPalette::initConnections()
{
    connect(ui->btnAddNewNode, &QPushButton::clicked, this, &ToolsPalette::on_addNewNodeButtonClicked);
    connect(ui->btnNewComment, &QPushButton::clicked, this, &ToolsPalette::on_addNewCommentButtonClicked);
    connect(ui->btnDeleteBlock, &QPushButton::clicked, this, &ToolsPalette::on_deleteBlockButtonClicked);
    connect(ui->btnZoomPlus, &QPushButton::clicked, this, &ToolsPalette::on_zoomPlusButtonClicked);
    connect(ui->btnZoomMinus, &QPushButton::clicked, this, &ToolsPalette::on_zoomMinusButtonClicked);
    connect(ui->btnZoomHome, &QPushButton::clicked, this, &ToolsPalette::on_zoomHomeButtonClicked);
}
