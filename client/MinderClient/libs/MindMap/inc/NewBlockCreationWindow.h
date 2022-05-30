#ifndef NEWBLOCKCREATIONWINDOW_H
#define NEWBLOCKCREATIONWINDOW_H

#include <QWidget>
#include <QColorDialog>
#include <QFontDialog>
#include <QCloseEvent>

#include "ViewDataStructures.h"

namespace Ui {
class NewBlockCreationWindow;
}

class NewBlockCreationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewBlockCreationWindow(QWidget *parent = nullptr);
    ~NewBlockCreationWindow();

signals:
    void transmitNewBlock(const ViewDataStructures::Block& data);
    void on_closeNewBlockCreationWindowButtonClicked();

private slots:
    void on_changeTextColorButtonClicked();
    void on_changeTextFontButtonClicked();
    void on_changeBackgroundColorButtonClicked();
    void on_changeBorderColorButtonClicked();
    void packBlockData();

private:
    void initConnections();
    void closeEvent(QCloseEvent *event);

private:
    Ui::NewBlockCreationWindow *ui;
    ViewDataStructures::Block newBlock;

};

#endif // NEWBLOCKCREATIONWINDOW_H
