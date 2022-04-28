#ifndef NEWBLOCKCREATIONWINDOW_H
#define NEWBLOCKCREATIONWINDOW_H

#include <QWidget>
#include <QColorDialog>
#include <QFontDialog>
#include <QCloseEvent>

#include "DataStructures.h"

using namespace ViewDataStructures;

namespace Ui {
class NewBlockCreationWindow;
}

class NewBlockCreationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewBlockCreationWindow(QWidget *parent = nullptr);
    ~NewBlockCreationWindow();

private:
    void initConnections();
    void closeEvent(QCloseEvent *event);

signals:
    void transmitNewBlock(const Block& data);
    void on_closeNewBlockCreationWindowButtonClicked();

private slots:
    void on_changeTextColorButtonClicked();
    void on_changeTextFontButtonClicked();
    void on_changeBackgroundColorButtonClicked();
    void on_changeBorderColorButtonClicked();

    void packBlockData();

private:
    Ui::NewBlockCreationWindow *ui;
    Block newBlock;

};

#endif // NEWBLOCKCREATIONWINDOW_H
