#include "newblockcreationwindow.h"
#include "ui_newblockcreationwindow.h"

NewBlockCreationWindow::NewBlockCreationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewBlockCreationWindow)
{
    ui->setupUi(this);
}

NewBlockCreationWindow::~NewBlockCreationWindow()
{
    delete ui;
}
