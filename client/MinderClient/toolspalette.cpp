#include "toolspalette.h"
#include "ui_toolspalette.h"

ToolsPalette::ToolsPalette(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ToolsPalette)
{
    ui->setupUi(this);
    initConnections();
    scaleChanged(DEF_SCALE / 100);
}

ToolsPalette::~ToolsPalette()
{
    delete ui;
}

void ToolsPalette::initConnections()
{
    connect(ui->btnAddNewNode, &QPushButton::clicked, this, &ToolsPalette::on_addNewBlockButtonClicked);
    connect(ui->btnDeleteBlock, &QPushButton::clicked, this, &ToolsPalette::on_deleteBlockButtonClicked);
    connect(ui->btnZoomPlus, &QPushButton::clicked, this, &ToolsPalette::on_zoomPlusButtonClicked);
    connect(ui->btnZoomMinus, &QPushButton::clicked, this, &ToolsPalette::on_zoomMinusButtonClicked);
    connect(ui->btnZoomHome, &QPushButton::clicked, this, &ToolsPalette::on_zoomHomeButtonClicked);
}

void ToolsPalette::scaleChanged(const double scale)
{
//    qDebug() << scale;
    ui->labelScale->setText(QString::number(std::round(scale * 10000.0) / 100.0) + QString("%"));
}
