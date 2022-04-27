#ifndef SESSIONWINDOW_H
#define SESSIONWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>
#include <QFontDialog>
#include <QMessageBox>

#include "datastructures.h"

#include "sessionuserlist.h"
#include "toolspalette.h"
#include "mindmap.h"
#include "newblockcreationwindow.h"

namespace Ui {
class SessionWindow;
}

class SessionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SessionWindow(const SessionData &data, QWidget *parent = nullptr);
    ~SessionWindow();

    void showEvent(QShowEvent *event);

private:
    void closeEvent(QCloseEvent *event);
    void initConnections();

    //Interface
signals:
    void on_closeSessionWindowButtonClicked();
    void getUsersListData(const long sessionId);
    void getMindMapData(const long sessionId);
    void transmitNewBlock(const Block &newBlock);

public:
    void updateUsersList(const UsersInSessionData &data);
    void updateMindMap(const MindMapData &data);
    void setNewBlockId(const long newBlockId);
    void setBlock(const Block &block);
    void setSessionData(const SessionData &data);
    SessionData getSessionData() { return sessionData; }
    // End Interface

private slots:
    //from toolspalette
    void addNewBlockButtonClicked();
    void deleteBlockButtonClicked();
    void zoomPlusButtonClicked();
    void zoomMinusButtonClicked();
    void zoomHomeButtonClicked();

    // from new block window
    void getNewBlock(const Block & newBlock);
    void closeNewBlockCreationWindow();

    // from mind map widget

private:
    Ui::SessionWindow *ui;
    NewBlockCreationWindow newBlockWindow;

    SessionData sessionData;
};

#endif // SESSIONWINDOW_H
