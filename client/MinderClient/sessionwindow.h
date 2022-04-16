#ifndef SESSIONWINDOW_H
#define SESSIONWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>

#include "datastructures.h"


#include "sessionuserlist.h"
#include "toolspalette.h"
#include "mindmap.h"

namespace Ui {
class SessionWindow;
}

class SessionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SessionWindow(QWidget *parent = nullptr);
    ~SessionWindow();
    void showEvent(QShowEvent *event);

private:
    void closeEvent(QCloseEvent *event);
    void initConnections();

signals:
    void on_closeSessionWindowButtonClicked();

    void getUsersList();

    void addNewComment();
    void addNewNode();
    void deleteBlock();

public slots:
    void updateUsersList(const UsersInSessionData &data);

private slots:
    void addNewCommentButtonClicked();
    void addNewNodeButtonClicked();
    void deleteBlockButtonClicked();
    void zoomPlusButtonClicked();
    void zoomMinusButtonClicked();
    void zoomHomeButtonClicked();

private:
    Ui::SessionWindow *ui;
};

#endif // SESSIONWINDOW_H
