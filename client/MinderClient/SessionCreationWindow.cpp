#include "SessionCreationWindow.h"
#include "ui_sessioncreationwindow.h"

SessionCreationWindow::SessionCreationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SessionCreationWindow)
{
    ui->setupUi(this);
    connect(ui->btnCreateNewSession, &QPushButton::clicked, this, &SessionCreationWindow::on_createNewSessionButtonClicked);
    connect(ui->btnConnectToExistingSession, &QPushButton::clicked, this, &SessionCreationWindow::on_openSessionConnectionWindowButtonClicked);
}

SessionCreationWindow::~SessionCreationWindow()
{
    delete ui;
}

void SessionCreationWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Session Creation window close event";

    emit on_closeSessionCreationWindowButtonClicked();
}

void SessionCreationWindow::on_createNewSessionButtonClicked()
{
    qDebug() << "Session creation pack data";

    SessionCreationData data(ui->lineSessionName->text(), ui->lineNewSessionPassword->text(), ui->lineNewSessionRepeatPassword->text());
    qDebug() << "  " << data.name << " " << data.password << " " << data.repeatPassword;

    emit on_createNewSession(data);
}

