#include "sessionwindow.h"
#include "ui_sessionwindow.h"

SessionWindow::SessionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SessionWindow)
{
    ui->setupUi(this);
    initConnections();
}

void SessionWindow::initConnections()
{
    connect(ui->btnQuit, &QPushButton::clicked, this, &SessionWindow::on_closeSessionWindowButtonClicked);

    connect(ui->widgetTooldPallette, &ToolsPalette::on_addNewNodeButtonClicked, this, &SessionWindow::addNewNodeButtonClicked);
    connect(ui->widgetTooldPallette, &ToolsPalette::on_addNewCommentButtonClicked, this, &SessionWindow::addNewCommentButtonClicked);
    connect(ui->widgetTooldPallette, &ToolsPalette::on_deleteBlockButtonClicked, this, &SessionWindow::deleteBlockButtonClicked);
    connect(ui->widgetTooldPallette, &ToolsPalette::on_zoomPlusButtonClicked, this, &SessionWindow::zoomPlusButtonClicked);
    connect(ui->widgetTooldPallette, &ToolsPalette::on_zoomMinusButtonClicked, this, &SessionWindow::zoomMinusButtonClicked);
    connect(ui->widgetTooldPallette, &ToolsPalette::on_zoomHomeButtonClicked, this, &SessionWindow::zoomHomeButtonClicked);
}

SessionWindow::~SessionWindow()
{
    delete ui;
}

void SessionWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "Session window close event";
    emit on_closeSessionWindowButtonClicked();
}

void SessionWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    emit getUsersList();
}

void SessionWindow::updateUsersList(const UsersInSessionData &data)
{
    this->ui->widgetSessionUsersList->updateUsersList(data);
}


void SessionWindow::addNewCommentButtonClicked()
{
    qDebug() << "Session: add new comment block";
}

void SessionWindow::addNewNodeButtonClicked()
{
    qDebug() << "Session: add new node block";
}

void SessionWindow::deleteBlockButtonClicked()
{
    qDebug() << "Session: delete block";
}

void SessionWindow::zoomPlusButtonClicked()
{
    qDebug() << "Session: zoom plus";
}

void SessionWindow::zoomMinusButtonClicked()
{
    qDebug() << "Session: zoom minus";
}

void SessionWindow::zoomHomeButtonClicked()
{
    qDebug() << "Session: zoom home";
}

