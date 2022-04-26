#ifndef TOOLSPALETTE_H
#define TOOLSPALETTE_H

#include <QFrame>

namespace Ui {
class ToolsPalette;
}

class ToolsPalette : public QFrame
{
    Q_OBJECT

public:
    explicit ToolsPalette(QWidget *parent = nullptr);
    ~ToolsPalette();

private:
    void initConnections();

signals:
    void on_addNewBlockButtonClicked();
    void on_deleteBlockButtonClicked();
    void on_zoomPlusButtonClicked();
    void on_zoomMinusButtonClicked();
    void on_zoomHomeButtonClicked();
    void on_chooseFontButtonClicked();

private:
    Ui::ToolsPalette *ui;
};

#endif // TOOLSPALETTE_H
