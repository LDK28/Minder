#ifndef NEWBLOCKCREATIONWINDOW_H
#define NEWBLOCKCREATIONWINDOW_H

#include <QWidget>

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
    Ui::NewBlockCreationWindow *ui;
};

#endif // NEWBLOCKCREATIONWINDOW_H
