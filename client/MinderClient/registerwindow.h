#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>

#include "datastructures.h"

using namespace ViewDataStructures;

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_registerButtonClicked();

signals:
    void on_openLoginWindowButtonCLicked();
    void on_closeRegisterWindowButtonClicked();

    void on_register(RegisterData data);

private:
    Ui::RegisterWindow *ui;
};

#endif // REGISTERWINDOW_H
