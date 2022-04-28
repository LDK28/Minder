#include "AuthorizationWindow.h"
#include "ui_authorizationwindow.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
    connect(ui->btnRegister, &QPushButton::clicked, this, &AuthorizationWindow::on_openRegisterWindowButtonClicked);
    connect(ui->btnSettings, &QPushButton::clicked, this, &AuthorizationWindow::on_openSettingsWindowButtonClicked);

    connect(ui->btnLogin, &QPushButton::clicked, this, &AuthorizationWindow::on_loginButtonClicked);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

void AuthorizationWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Auth window close event";
//    event->ignore();
    emit on_closeAuthorizationWindowButtonClicked();
}

void AuthorizationWindow::on_loginButtonClicked()
{
    qDebug() << "Authorization pack data";
    LoginData data = {ui->lineNickname->text(), ui->linePassword->text()};
    qDebug() << "  " << data.nickname << " " << data.password;
    emit on_login(data);
}

