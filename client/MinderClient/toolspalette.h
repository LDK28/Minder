#ifndef TOOLSPALETTE_H
#define TOOLSPALETTE_H

#include <QWidget>

namespace Ui {
class ToolsPalette;
}

class ToolsPalette : public QWidget
{
    Q_OBJECT

public:
    explicit ToolsPalette(QWidget *parent = nullptr);
    ~ToolsPalette();

private:
    void initConnections();

signals:
    void on_addNewCommentButtonClicked();
    void on_addNewNodeButtonClicked();
    void on_deleteBlockButtonClicked();
    void on_zoomPlusButtonClicked();
    void on_zoomMinusButtonClicked();
    void on_zoomHomeButtonClicked();

private:
    Ui::ToolsPalette *ui;
};

#endif // TOOLSPALETTE_H
