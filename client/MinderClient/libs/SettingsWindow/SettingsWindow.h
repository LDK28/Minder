#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>

#include "DataStructures.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

signals:
    void on_closeSettingsWindowButtonClicked();
    void on_saveSettings(const ViewDataStructures::SettingsData &data);

public:
    void showErrorMsg(const QString &errMsg);
    void hideErrorMsg();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_saveSettingsButtonClicked();

private:
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
