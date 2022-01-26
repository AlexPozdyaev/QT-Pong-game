#include "pc.h"
#include <QTimer>

pc::pc(pong *pong, QGraphicsScene *s, QTimer *t, int indent) { //Конструктор
    m_pong = pong;
    m_indent = indent;

    connect(t, SIGNAL(timeout()), this, SLOT(track())); //Связь с глобальным таймером

    setBrush(QBrush(QColor(255, 255, 255, 255)));  //Настройки размера и цвета слайдера
    setRect(0, 0, 20, 150);

    s->addItem(this);
    reset();
}

void pc::track() { //Слежение за мячом
    if      (m_pong->y()                         < y()                ) slideVelocity = m_pong->y()-y();
    else if (m_pong->y()+m_pong->rect().height() > y()+rect().height())
        slideVelocity = m_pong->y()+m_pong->rect().height() - (y()+rect().height());
    else slideVelocity = 0;

    if (slideVelocity >  20) slideVelocity =  20;
    if (slideVelocity < -20) slideVelocity = -20;

    //Проверка на не выход за пределы области
    if (slideVelocity > scene()->height()-(y()+rect().height()))
        slideVelocity = scene()->height()-(y()+rect().height());
    else if (slideVelocity < -y())
        slideVelocity = -y();

    setPos(x(), y()+slideVelocity); //Движение слайдера противника

    //Проверка мяча на сталкивание с объектами
    if (m_pong->x()                         < x()+rect().width() &&
        m_pong->x()                         > x()                &&
        m_pong->y()+m_pong->rect().height() > y()                &&
        m_pong->y()                         < y()+rect().height())
    {
        m_pong->deflect(slideVelocity); //отражение мяча
    }
}

void pc::reset() { //Установление на стартовую позицию
    slideVelocity = 0;
    setPos(m_indent - rect().width() /2, scene()->height()/2 - rect().height()/2);
}

