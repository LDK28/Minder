#include "SessionCreationWindow.h"
#include "ui_SessionCreationWindow.h"

SessionCreationWindow::SessionCreationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SessionCreationWindow)
{
    ui->setupUi(this);
    initConnections();
    hideErrorMsg();
}

SessionCreationWindow::~SessionCreationWindow()
{
    delete ui;
}

void SessionCreationWindow::initConnections()
{
    connect(ui->btnCreateNewSession, &QPushButton::clicked, this, &SessionCreationWindow::on_createNewSessionButtonClicked);
    connect(ui->btnConnectToExistingSession, &QPushButton::clicked, this, &SessionCreationWindow::on_openSessionConnectionWindowButtonClicked);
}

void SessionCreationWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Session Creation window close event";

    hideErrorMsg();

    emit on_closeSessionCreationWindowButtonClicked();
}

void SessionCreationWindow::on_createNewSessionButtonClicked()
{
    qDebug() << "Session creation pack data";

    ViewDataStructures::SessionCreationData data(ui->lineSessionName->text(), ui->lineNewSessionPassword->text(), ui->lineNewSessionRepeatPassword->text());
    qDebug() << "  " << data.name << " " << data.password << " " << data.repeatPassword;

    hideErrorMsg();

    emit on_createNewSession(data);
}

void SessionCreationWindow::showErrorMsg(const QString &errMsg)
{
    ui->labelErrorMsg->setText(errMsg);
    ui->labelErrorMsg->show();
}

void SessionCreationWindow::hideErrorMsg()
{
    ui->labelErrorMsg->hide();
}

