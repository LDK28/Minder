#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>

#include "DataStructures.h"

using namespace ViewDataStructures;

namespace Ui {
class AuthorizationWindow;
}

class AuthorizationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();

private:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_loginButtonClicked();

signals:
    void on_openRegisterWindowButtonClicked();
    void on_openSettingsWindowButtonClicked();
    void on_closeAuthorizationWindowButtonClicked();

    void on_login(const LoginData &data);

private:
    Ui::AuthorizationWindow *ui;
};

#endif // AUTHORIZATIONWINDOW_H
