#ifndef DRAWING_H
#define DRAWING_H

#include <QtWidgets>

#include "DataStructures.h"
#include "HttpClient.h"

class Drawing : public QObject {
Q_OBJECT
public:
    explicit Drawing() = default;
    explicit Drawing(HttpClient *network_) : network(network_) {}
    ~Drawing() = default;
public slots:
    void addBlock();
    void deleteBlock();
    void changeBlock();
    void getCurrentState();
    void changeSize();
signals:
    void changeView();
private:
    std::shared_ptr <HttpClient> network = nullptr;
};

#endif // DRAWING_H
