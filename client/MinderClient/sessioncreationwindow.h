#ifndef SESSIONCREATIONWINDOW_H
#define SESSIONCREATIONWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>

#include "datastructures.h"

namespace Ui {
class SessionCreationWindow;
}

class SessionCreationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SessionCreationWindow(QWidget *parent = nullptr);
    ~SessionCreationWindow();

private:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_createNewSessionButtonClicked();

signals:
    void on_createNewSession(SessionCreationData data);
    void on_openSessionConnectionWindowButtonClicked();
    void on_closeSessionCreationWindowButtonClicked();

private:
    Ui::SessionCreationWindow *ui;
};

#endif // SESSIONCREATIONWINDOW_H
