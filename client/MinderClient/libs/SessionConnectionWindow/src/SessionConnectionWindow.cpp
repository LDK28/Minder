#include "SessionConnectionWindow.h"
#include "ui_SessionConnectionWindow.h"

SessionConnectionWindow::SessionConnectionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SessionConnectionWindow)
{
    ui->setupUi(this);
    initConnections();
    hideErrorMsg();
}

SessionConnectionWindow::~SessionConnectionWindow()
{
    delete ui;
}

void SessionConnectionWindow::initConnections()
{
    connect(ui->btnCreateNewSession, &QPushButton::clicked, this, &SessionConnectionWindow::on_openNewSessionCreationWindowButtonClicked);
    connect(ui->btnConnectToSession, &QPushButton::clicked, this, &SessionConnectionWindow::on_connectToSessionButtonClicked);
}

void SessionConnectionWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Session Connection window close event";

    hideErrorMsg();

    emit on_closeSessionConnectionWindowButtonClicked();
}

void SessionConnectionWindow::on_connectToSessionButtonClicked()
{
    qDebug() << "Session connection pack data";
    ViewDataStructures::SessionConnectionData data(ui->lineSessiond->text(), ui->lineSessionPassword->text());
    qDebug() << "  " << data.id << " " << data.password;

    hideErrorMsg();

    emit on_connectToSession(data);
}

void SessionConnectionWindow::showErrorMsg(const QString &errMsg)
{
    ui->labelErrorMsg->setText(errMsg);
    ui->labelErrorMsg->show();
}

void SessionConnectionWindow::hideErrorMsg()
{
    ui->labelErrorMsg->hide();
}
