#ifndef PONG_H
#define PONG_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QObject>

class pong : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    pong(QGraphicsScene *s, QTimer *t);
    void deflect(double);
    int sc_1;
    int sc_2;

public slots:
    void move();

signals:
    void res1(int a);
    void res2(int a);

private:
    void reset();
    bool isDeflected;
    double paddleYVel;
    double xVelocity;
    double yVelocity;
};

#endif // PONG_H
