#include "SettingsWindow.h"
#include "ui_SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    connect(ui->btnSave, &QPushButton::clicked, this, &SettingsWindow::on_saveSettingsButtonClicked);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Settings window: close event";

    emit on_closeSettingsWindowButtonClicked();
}

void SettingsWindow::on_saveSettingsButtonClicked()
{
    qDebug() << "Settings window: pack data";
    ViewDataStructures::SettingsData data(ui->lineServerIP->text(), ui->lineServerPort->text());
    qDebug() << "  " << data.serverIP << " " << data.serverPort;
    emit on_saveSettings(data);
}

