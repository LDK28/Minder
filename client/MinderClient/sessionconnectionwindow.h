#ifndef SESSIONCONNECTIONWINDOW_H
#define SESSIONCONNECTIONWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>

#include "datastructures.h"

namespace Ui {
class SessionConnectionWindow;
}

class SessionConnectionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SessionConnectionWindow(QWidget *parent = nullptr);
    ~SessionConnectionWindow();

private:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_connectToSessionButtonClicked();

signals:
    void on_openNewSessionCreationWindowButtonClicked();
    void on_closeSessionConnectionWindowButtonClicked();

    void on_connectToSession(const SessionConnectionData &data);

private:
    Ui::SessionConnectionWindow *ui;
};

#endif // SESSIONCONNECTIONWINDOW_H
