#ifndef SESSIONCREATIONWINDOW_H
#define SESSIONCREATIONWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>

#include "DataStructures.h"

namespace Ui {
class SessionCreationWindow;
}

class SessionCreationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SessionCreationWindow(QWidget *parent = nullptr);
    ~SessionCreationWindow();

signals:
    void on_createNewSession(const ViewDataStructures::SessionCreationData &data);
    void on_openSessionConnectionWindowButtonClicked();
    void on_closeSessionCreationWindowButtonClicked();

public:
    void showErrorMsg(const QString &errMsg);
    void hideErrorMsg();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_createNewSessionButtonClicked();

private:
    Ui::SessionCreationWindow *ui;
};

#endif // SESSIONCREATIONWINDOW_H
