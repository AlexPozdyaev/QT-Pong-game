#ifndef EN_SLIDER_H
#define EN_SLIDER_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>

#include "pong.h"

class en_slider : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    en_slider(pong *pong, QGraphicsScene *s, QTimer *t, int indent);

public slots:
    void slide();
    void resiv(bool a, bool b);

private:
    void reset();
    pong *m_pong;
    int m_indent;
    QTimer *m_timer;
    double slideVelocity;
    bool moveUp;
    bool moveDown;
    double moveSpeed;
};

#endif // EN_SLIDER_H
