#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>

#include "DataStructures.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

signals:
    void on_openLoginWindowButtonCLicked();
    void on_closeRegisterWindowButtonClicked();
    void on_register(const ViewDataStructures::RegisterData data);

public:
    void showErrorMsg(const QString &errMsg);
    void hideErrorMsg();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_registerButtonClicked();

private:
    Ui::RegisterWindow *ui;
};

#endif // REGISTERWINDOW_H
