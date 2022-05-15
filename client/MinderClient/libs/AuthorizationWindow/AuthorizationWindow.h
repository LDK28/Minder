#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>

#include "DataStructures.h"

namespace Ui {
class AuthorizationWindow;
}

class AuthorizationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();

signals:
    void on_openRegisterWindowButtonClicked();
    void on_openSettingsWindowButtonClicked();
    void on_closeAuthorizationWindowButtonClicked();
    void on_login(const ViewDataStructures::LoginData &data);

public:
    void showErrorMsg(const QString &errMsg);
    void hideErrorMsg();

private:
    void closeEvent(QCloseEvent *event);
    void initConnections();

private slots:
    void on_loginButtonClicked();


private:
    Ui::AuthorizationWindow *ui;
};

#endif // AUTHORIZATIONWINDOW_H
