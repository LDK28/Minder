#include "NewBlockCreationWindow.h"
#include "ui_newblockcreationwindow.h"

#include <QMessageBox>

NewBlockCreationWindow::NewBlockCreationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewBlockCreationWindow)
{
    ui->setupUi(this);
    initConnections();

    const QStringList typesValues
    {
        TYPES_ENUM(MAKE_STRINGS)
    };

    for(int i = 0; i < typesValues.count(); ++i)
    {
        ui->comboBoxType->addItem(typesValues[i]);
    }

}

void NewBlockCreationWindow::initConnections()
{
    connect(ui->btnBackgroudColor, &QPushButton::clicked, this, &NewBlockCreationWindow::on_changeBackgroundColorButtonClicked);
    connect(ui->btnBorderColor, &QPushButton::clicked, this, &NewBlockCreationWindow::on_changeBorderColorButtonClicked);
    connect(ui->btnTextColor, &QPushButton::clicked, this, &NewBlockCreationWindow::on_changeTextColorButtonClicked);
    connect(ui->btnTextFont, &QPushButton::clicked, this, &NewBlockCreationWindow::on_changeTextFontButtonClicked);

    connect(ui->btnAdd, &QPushButton::clicked, this, &NewBlockCreationWindow::packBlockData);
}

void NewBlockCreationWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "New Block creation window: close event";

    emit on_closeNewBlockCreationWindowButtonClicked();
}

void NewBlockCreationWindow::packBlockData()
{
    qDebug() << "New block creation: pack block";

    newBlock.text = ui->plainTextEdit->toPlainText();

    emit transmitNewBlock(newBlock);
}

NewBlockCreationWindow::~NewBlockCreationWindow()
{
    delete ui;
}

void NewBlockCreationWindow::on_changeTextColorButtonClicked()
{
    qDebug() << "New block creation: change text color";

    newBlock.textColor = QColorDialog::getColor(newBlock.textColor);
    if(!newBlock.textColor.isValid())
    {
        QMessageBox::about(this, "Error", "Invalid color");
    }
}

void NewBlockCreationWindow::on_changeBackgroundColorButtonClicked()
{
    qDebug() << "New background creation: change back color";

    newBlock.backgroundColor = QColorDialog::getColor(newBlock.backgroundColor);
    if(!newBlock.backgroundColor.isValid())
    {
        QMessageBox::about(this, "Error", "Invalid color");
    }

}

void NewBlockCreationWindow::on_changeBorderColorButtonClicked()
{
    qDebug() << "New block creation: change border color";

    newBlock.borderColor = QColorDialog::getColor(newBlock.borderColor);
    if(!newBlock.borderColor.isValid())
    {
        QMessageBox::about(this, "Error", "Invalid color");
    }

}

void NewBlockCreationWindow::on_changeTextFontButtonClicked()
{
    qDebug() << "New block creation: change font";

    bool isOk;
    QFont font = QFontDialog::getFont(&isOk, this);
    if(isOk)
    {
        ui->plainTextEdit->setFont(font);
        newBlock.textFont = font;
    }
    else
    {
        QMessageBox::about(this, "Error", "Invalid font");
    }
}
