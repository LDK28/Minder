#ifndef SESSIONWINDOW_H
#define SESSIONWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QCloseEvent>
#include <QFontDialog>
#include <QMessageBox>

#include "DataStructures.h"

#include "SessionUsersList.h"
#include "ToolsPalette.h"
#include "MindMap.h"
#include "NewBlockCreationWindow.h"

using namespace ViewDataStructures;

namespace Ui {
class SessionWindow;
}

class SessionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SessionWindow(const SessionData &data, QWidget *parent = nullptr);
    ~SessionWindow();

    //Interface
signals:
    void on_closeSessionWindowButtonClicked();
    void getUsersListData(const long sessionId);
    void getMindMapData(const long sessionId);
    void transmitNewBlock(const ViewDataStructures::Block &newBlock);
    void transmitDeletedBlock(const ViewDataStructures::MindMapData & changedBlocks);

public:
    void updateUsersList(const UsersInSessionData &data);
    void updateMindMap(const MindMapData &data);
    void setNewBlockId(const size_t newBlockId);
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
    void getNewBlock(const ViewDataStructures::Block & newBlock);
    void closeNewBlockCreationWindow();

    // from mind map widget

protected:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    void initConnections();

private:
    Ui::SessionWindow *ui;
    NewBlockCreationWindow newBlockWindow;

    SessionData sessionData;
};

#endif // SESSIONWINDOW_H
