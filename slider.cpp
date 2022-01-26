#include "slider.h"

#include <QApplication>
#include <QTimer>

slider::slider(pong *pong, QGraphicsScene *s, QTimer *t, int indent) //Конструктор
{
    m_pong = pong;
    m_indent = indent;
    m_timer = t;
    moveSpeed = 20;
    s->addItem(this);

    setBrush(QBrush(QColor(255, 255, 255, 255))); //Настройки размера и цвета слайдера
    setRect(0, 0, 20, 150);

    reset();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(slide())); //Связь с глобальным таймером
}

void slider::slide() {
    //Регулировка вертикального перемещения, зависящая от введенной кнопки
    if (moveUp) slideVelocity = -moveSpeed;
    else if (moveDown) slideVelocity =  moveSpeed;
    else slideVelocity = 0;

    //Проверка на не выход за пределы области
    if (slideVelocity > scene()->height()-(y()+rect().height()))
        slideVelocity = scene()->height()-(y()+rect().height());
    else if (slideVelocity < -y())
        slideVelocity = -y();

    setPos(x(), y()+slideVelocity); //Движение слайдера

    //Проверка мяча на сталкивание с объектами
    if (m_pong->x()+m_pong->rect().width()  > x() &&
        m_pong->x()+m_pong->rect().width()  < x()+rect().width() &&
        m_pong->y()+m_pong->rect().height() > y() &&
        m_pong->y()                         < y()+rect().height())
    {
        m_pong->deflect(slideVelocity);
    }
}

void slider::resiv(bool a, bool b) //Слот для получения сигнала от клавиатуры
{
    moveDown = a;
    moveUp   = b;
}

void slider::reset()    //Установление на стартовую позицию
{
    setPos(scene()->width() - m_indent - rect().width()/2, scene()->height()/2 - rect().height()/2);
    slideVelocity = 0;
    moveUp = false;
    moveDown = false;
}
