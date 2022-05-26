#include "SessionWindow.h"
#include "ui_SessionWindow.h"

SessionWindow::SessionWindow(const ViewDataStructures::SessionData &data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SessionWindow)
{
    ui->setupUi(this);
    initConnections();

    ui->widgetMindMap->setScale(defaultScalePercent);
    setSessionData(data);
}

void SessionWindow::initConnections()
{
    connect(ui->btnQuit, &QPushButton::clicked, this, &SessionWindow::on_closeSessionWindowButtonClicked);

    connect(ui->widgetToolsPalette, &ToolsPalette::on_addNewBlockButtonClicked, this, &SessionWindow::addNewBlockButtonClicked);
    connect(ui->widgetToolsPalette, &ToolsPalette::on_deleteBlockButtonClicked, ui->widgetMindMap, &MindMap::deleteSelectedBlock);
    connect(ui->widgetToolsPalette, &ToolsPalette::on_zoomPlusButtonClicked, this, &SessionWindow::zoomPlusButtonClicked);
    connect(ui->widgetToolsPalette, &ToolsPalette::on_zoomMinusButtonClicked, this, &SessionWindow::zoomMinusButtonClicked);
    connect(ui->widgetToolsPalette, &ToolsPalette::on_zoomHomeButtonClicked, this, &SessionWindow::zoomHomeButtonClicked);

    connect(&newBlockWindow, &NewBlockCreationWindow::transmitNewBlock, this, &SessionWindow::getNewBlock);
    connect(&newBlockWindow, &NewBlockCreationWindow::on_closeNewBlockCreationWindowButtonClicked, this, &SessionWindow::closeNewBlockCreationWindow);

    connect(ui->widgetMindMap, &MindMap::transmitNewBlock, this, &SessionWindow::transmitNewBlock);
    connect(ui->widgetMindMap, &MindMap::transmitDeletedBlock, this, &SessionWindow::transmitDeletedBlock);
    connect(ui->widgetMindMap, &MindMap::scaleChanged, ui->widgetToolsPalette, &ToolsPalette::scaleChanged);
}

SessionWindow::~SessionWindow()
{
    qDebug() << "Session dctor";

    delete ui;
}

void SessionWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "Session window: close event";

    Q_UNUSED(event);
    newBlockWindow.hide();
    emit on_closeSessionWindowButtonClicked();
}

void SessionWindow::showEvent(QShowEvent *event)
{
    qDebug() << "Session window: show event";

    QWidget::showEvent(event);
    emit getUsersListData(sessionData.id);
    emit getMindMapData(sessionData.id);
}

void SessionWindow::setSessionData(const ViewDataStructures::SessionData &data)
{
    sessionData = data;
    ui->labelRoomName->setText(sessionData.name + "#" + QString::number(sessionData.id));
}

void SessionWindow::updateUsersList(const ViewDataStructures::UsersInSessionData &data)
{
    qDebug() << "Session window: update users list";

    this->ui->widgetSessionUsersList->updateUsersList(data);
}

void SessionWindow::updateMindMap(const ViewDataStructures::MindMapData &data)
{
    qDebug() << "Session window: update mindmap";

    this->ui->widgetMindMap->updateMindMap(data);
}

void SessionWindow::addNewBlockButtonClicked()
{
    qDebug() << "Session Window: add new block btn clicked";

    newBlockWindow.show();
    this->setEnabled(false);
}

void SessionWindow::getNewBlock(const ViewDataStructures::Block &newBlock)
{
    qDebug() << "Session Window: got new block: "; newBlock.print();

    newBlockWindow.hide();
    this->setEnabled(true);
    ui->widgetToolsPalette->setEnabled(false);
    ui->widgetMindMap->drawNewBlock(newBlock);
}

void SessionWindow::closeNewBlockCreationWindow()
{
    qDebug() << "Session Window: close new block window";

    newBlockWindow.hide();
    this->setEnabled(true);
}

void SessionWindow::deleteBlockButtonClicked()
{
    qDebug() << "Session Window: delete block";
}

void SessionWindow::zoomPlusButtonClicked()
{
    qDebug() << "Session Window: zoom plus";
    ui->widgetMindMap->changeScale(btnZoomPlusDeltaScalePercent);
}

void SessionWindow::zoomMinusButtonClicked()
{
    qDebug() << "Session Window: zoom minus";
    ui->widgetMindMap->changeScale(btnZoomMinusDeltaScalePercent);
}

void SessionWindow::zoomHomeButtonClicked()
{
    qDebug() << "Session Window: zoom home";
    ui->widgetMindMap->setScale(defaultScalePercent);
}

void SessionWindow::setNewBlockId(const size_t newBlockId)
{
    qDebug() << "Session Window: set id for new block";

    ui->widgetToolsPalette->setEnabled(true);
    ui->widgetMindMap->setNewBlockId(newBlockId);
}

void SessionWindow::setBlock(const ViewDataStructures::Block &block)
{
    qDebug() << "Session Window: set block";

    ui->widgetMindMap->drawBlock(block);
}

void SessionWindow::deleteBlock(const size_t id)
{
    qDebug() << "Session Window: another user deleted block";

    ui->widgetMindMap->blockWasDeleted(id);
}
