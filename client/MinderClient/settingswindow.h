#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>

#include "datastructures.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

private:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_saveSettingsButtonClicked();

signals:
    void on_closeSettingsWindowButtonClicked();

    void on_saveSettings(SettingsData data);

private:
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
