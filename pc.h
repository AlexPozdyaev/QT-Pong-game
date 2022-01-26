#ifndef PC_H
#define PC_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>

#include "pong.h"

class pc : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    pc(pong *pong, QGraphicsScene *s, QTimer *t, int indent);

public slots:
    void track();

private:
    void reset();
    pong *m_pong;
    int m_indent;
    double slideVelocity;
};

#endif // PC_H
