#include "RegisterWindow.h"
#include "ui_RegisterWindow.h"

RegisterWindow::RegisterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    initConnections();
    hideErrorMsg();
}

void RegisterWindow::initConnections()
{
    connect(ui->btnLogin, &QPushButton::clicked, this, &RegisterWindow::on_openLoginWindowButtonCLicked);
    connect(ui->btnRegister, &QPushButton::clicked, this, &RegisterWindow::on_registerButtonClicked);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Register window close event";

    hideErrorMsg();

    emit on_closeRegisterWindowButtonClicked();
}

void RegisterWindow::on_registerButtonClicked()
{
    qDebug() << "Register pack data";
    ViewDataStructures::RegisterData data = {ui->lineNickname->text(), ui->linePassword->text(), ui->lineRepeatPassword->text()};
    qDebug() << "  " << data.nickname << " " << data.password << " " << data.repeatPassword;

    hideErrorMsg();

    emit on_register(data);
}

void RegisterWindow::showErrorMsg(const QString &errMsg)
{
    ui->labelErrorMsg->setText(errMsg);
    ui->labelErrorMsg->show();
}

void RegisterWindow::hideErrorMsg()
{
    ui->labelErrorMsg->hide();
}

