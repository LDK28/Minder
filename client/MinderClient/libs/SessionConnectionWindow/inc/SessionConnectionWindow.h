#ifndef SESSIONCONNECTIONWINDOW_H
#define SESSIONCONNECTIONWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>

#include "DataStructures.h"

namespace Ui {
class SessionConnectionWindow;
}

class SessionConnectionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SessionConnectionWindow(QWidget *parent = nullptr);
    ~SessionConnectionWindow();

signals:
    void on_openNewSessionCreationWindowButtonClicked();
    void on_closeSessionConnectionWindowButtonClicked();
    void on_connectToSession(const ViewDataStructures::SessionConnectionData &data);
public:
    void showErrorMsg(const QString &errMsg);
    void hideErrorMsg();

private:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_connectToSessionButtonClicked();

private:
    Ui::SessionConnectionWindow *ui;
};

#endif // SESSIONCONNECTIONWINDOW_H
