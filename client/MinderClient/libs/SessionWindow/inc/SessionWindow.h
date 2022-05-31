#ifndef SESSIONWINDOW_H
#define SESSIONWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>
#include <QFontDialog>
#include <QMessageBox>

#include "ViewDataStructures.h"

#include "SessionUsersList.h"
#include "ToolsPalette.h"
#include "MindMap.h"
#include "NewBlockCreationWindow.h"

namespace Ui {
class SessionWindow;
}

class SessionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SessionWindow(const ViewDataStructures::SessionData &data, QWidget *parent = nullptr);
    ~SessionWindow();

    //Interface
signals:
    void disconnectFromSession(const size_t sessionId);

    void getUsersListData(const long sessionId);

    void getMindMapData(const long sessionId);
    void transmitNewBlock(const size_t sessionId, const ViewDataStructures::Block &newBlock);
    void transmitDeletedBlock(const ViewDataStructures::MindMapData & changedBlocks);

public:
    void setSessionData(const ViewDataStructures::SessionData &data);
    ViewDataStructures::SessionData getSessionData() { return sessionData; }

    void updateUsersList(const ViewDataStructures::UsersInSessionData &data);

    void updateMindMap(const ViewDataStructures::MindMapData &data);
    void setNewBlockId(const size_t newBlockId);
    void setBlock(const ViewDataStructures::Block &block);
    void deleteBlock(const size_t id);
    // End Interface

private slots:
    //from toolspalette
    void addNewBlockButtonClicked();
    void deleteBlockButtonClicked();
    void zoomPlusButtonClicked();
    void zoomMinusButtonClicked();
    void zoomHomeButtonClicked();

    // from new block window
    void getNewBlock(const ViewDataStructures::Block & newBlock);
    void closeNewBlockCreationWindow();

    // from mind map widget
    void handlerDisconnect();
    void handlerNewBlock(const ViewDataStructures::Block &block);

protected:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    void initConnections();

private:
    Ui::SessionWindow *ui;
    NewBlockCreationWindow newBlockWindow;

    ViewDataStructures::SessionData sessionData;
};

#endif // SESSIONWINDOW_H
