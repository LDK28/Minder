#include "sessionconnectionwindow.h"
#include "ui_sessionconnectionwindow.h"

SessionConnectionWindow::SessionConnectionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SessionConnectionWindow)
{
    ui->setupUi(this);
    connect(ui->btnCreateNewSession, &QPushButton::clicked, this, &SessionConnectionWindow::on_openNewSessionCreationWindowButtonClicked);
    connect(ui->btnConnectToSession, &QPushButton::clicked, this, &SessionConnectionWindow::on_connectToSessionButtonClicked);
}

SessionConnectionWindow::~SessionConnectionWindow()
{
    delete ui;
}

void SessionConnectionWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Session Connection window close event";
    emit on_closeSessionConnectionWindowButtonClicked();
}

void SessionConnectionWindow::on_connectToSessionButtonClicked()
{
    qDebug() << "Session connection pack data";
    SessionConnectionData data(ui->lineSessiond->text(), ui->lineSessionPassword->text());
    qDebug() << "  " << data.id << " " << data.password;
    emit on_connectToSession(data);
}
