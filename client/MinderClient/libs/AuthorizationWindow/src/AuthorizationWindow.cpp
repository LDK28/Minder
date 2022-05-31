#include "AuthorizationWindow.h"
#include "ui_AuthorizationWindow.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
    initConnections();
    hideErrorMsg();
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

void AuthorizationWindow::initConnections()
{
    connect(ui->btnRegister, &QPushButton::clicked, this, &AuthorizationWindow::on_openRegisterWindowButtonClicked);
    connect(ui->btnSettings, &QPushButton::clicked, this, &AuthorizationWindow::on_openSettingsWindowButtonClicked);
    connect(ui->btnLogin, &QPushButton::clicked, this, &AuthorizationWindow::on_loginButtonClicked);
}

void AuthorizationWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Auth window close event";

    hideErrorMsg();

    emit on_closeAuthorizationWindowButtonClicked();
}

void AuthorizationWindow::on_loginButtonClicked()
{
    qDebug() << "Authorization pack data";
    ViewDataStructures::LoginData data = {ui->lineNickname->text(), ui->linePassword->text()};
    qDebug() << "  " << data.nickname << " " << data.password;

    hideErrorMsg();

    emit on_login(data);
}

void AuthorizationWindow::showErrorMsg(const QString &errMsg)
{
    ui->labelErrorMsg->setText(errMsg);
    ui->labelErrorMsg->show();
}

void AuthorizationWindow::hideErrorMsg()
{
    ui->labelErrorMsg->hide();
}
