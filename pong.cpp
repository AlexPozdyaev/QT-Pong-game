#include "pong.h"

#include <QGraphicsScene>
#include <QTimer>
#include <math.h>


pong::pong(QGraphicsScene *s, QTimer *t) //Конструктор
{
    connect(t, SIGNAL(timeout()), this, SLOT(move())); //Связь с глобальным таймером
    sc_1=sc_2=0; //Счетчик голов


    setRect(0, 0, 15, 15); //Настройки размера и цвета мяча
    setBrush(QBrush(QColor(255, 255, 255, 255)));

    s->addItem(this);

    reset();
}

void pong::move()
{
    //Отскакивание от верха и низа формы
    if (y()+rect().height() > scene()->height() || y() < 0) {
        yVelocity *= -1;
    }
    //Отскакивание от слайдера
    if (isDeflected) {
        xVelocity *= -1;
        yVelocity += paddleYVel;
        isDeflected = false;
        paddleYVel = 0;
    }

    setPos(x()+xVelocity, y()+yVelocity); //Движение мяча

    //Касание мячем области, для засчитывания гола
    if (x() < 0) {
        reset();
        sc_1++;
        emit res1(sc_1);
    }
        else if(x()+rect().width() > scene()->width()) {
            reset();
            sc_2++;
            emit res2(sc_2);
    }

}

void pong::deflect(double yVel) //Обработка отражения от слайдера
{
    isDeflected = true;
    paddleYVel = yVel;
}

void pong::reset() //Установление на стартовую позицию
{
    setPos(scene()->width()/2 - rect().width()/2, scene()->height()/2 - rect().height()/2);
    isDeflected = false;
    paddleYVel = 0;
    xVelocity = pow((-1),rand()%2+1)*(rand()%15+7); //рандомайзер на направление и скорось мяча
    yVelocity = pow((-1),rand()%2+1)*(rand()%15+5);
}
