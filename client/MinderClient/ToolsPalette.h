#ifndef TOOLSPALETTE_H
#define TOOLSPALETTE_H

#include <QFrame>

#include"DataStructures.h"

using namespace ViewDataStructures;

namespace Ui {
class ToolsPalette;
}

class ToolsPalette : public QFrame
{
    Q_OBJECT

public:
    explicit ToolsPalette(QWidget *parent = nullptr);
    ~ToolsPalette();

signals:
    void on_addNewBlockButtonClicked();
    void on_deleteBlockButtonClicked();
    void on_zoomPlusButtonClicked();
    void on_zoomMinusButtonClicked();
    void on_zoomHomeButtonClicked();

public slots:
    void scaleChanged(const double scale);

private:
    void initConnections();

private:
    Ui::ToolsPalette *ui;
};

#endif // TOOLSPALETTE_H
