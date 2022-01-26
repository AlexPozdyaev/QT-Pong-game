#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>

#include "pong.h"
#include "slider.h"
#include "en_slider.h"
#include "pc.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_3->setNum(0);
    ui->label_4->setNum(0);
    ui->label->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->graphicsView->hide();
}


MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)   //Фильтр событий клавиатуры
{
    if (e->type() == QEvent::KeyPress) {
        QKeyEvent *k= static_cast <QKeyEvent *>(e);
        if      (k->key() == Qt::Key_Escape) QApplication::quit();
        else if (k->key() == Qt::Key_W) {
            moveDown_en = false;
            moveUp_en   = true;
            emit z1(moveDown_en, moveUp_en);
            return true;
        }
        else if (k->key() == Qt::Key_S) {
            moveDown_en = true;
            moveUp_en   = false;
            emit z1(moveDown_en, moveUp_en);
            return true;
        }
        else if (k->key() == Qt::Key_Up)
        {
            moveDown = false;
            moveUp   = true;
            emit z2(moveDown, moveUp);
            return true;
        }
        else if (k->key() == Qt::Key_Down)
        {
            moveDown = true;
            moveUp   = false;
            emit z2(moveDown, moveUp);
            return true;
        }
        return false;
    }
    if (e->type()== QEvent::KeyRelease) {
        QKeyEvent *k= static_cast <QKeyEvent *>(e);
        if (k->key() == Qt::Key_W   && moveUp_en  ) {
            moveDown_en = false;
            moveUp_en   = false;
            emit z1(moveDown_en, moveUp_en);
            return true;
        }
        else if (k->key() == Qt::Key_S && moveDown_en) {
            moveDown_en = false;
            moveUp_en   = false;
            emit z1(moveDown_en, moveUp_en);
            return true;
        }
        else if (k->key() == Qt::Key_Up   && moveUp  )
        {
            moveDown = false;
            moveUp   = false;
            emit z2(moveDown, moveUp);
            return true;
        }
        else if (k->key() == Qt::Key_Down && moveDown)
        {
            moveDown = false;
            moveUp   = false;
            emit z2(moveDown, moveUp);
            return true;
        }
        return false;
    }
    return false;
}

void MainWindow::pol1(int a) //установление счета для левого игрока
{
    ui->label_4->setNum(a);
}

void MainWindow::pol2(int a) //установление счета для правого игрока
{
    ui->label_3->setNum(a);
}

void MainWindow::on_pushButton_clicked() //Игра против ПК
{
    ui->label_2->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->label->show();
    ui->label_3->show();
    ui->label_4->show();

    QTimer *timer = new QTimer();
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 850, 500);
    scene->setBackgroundBrush(QBrush(QColor(0, 0, 0, 255)));
    scene->setStickyFocus(true);    //При нажатие на сцену, фокус с нее не сбрасывается


    int paddleIndent = 70;
    pong *p = new pong(scene, timer);
    slider *pp = new slider(p, scene, timer, paddleIndent);
    pc *sl = new pc(p, scene, timer, paddleIndent);

    scene->installEventFilter(this);
    connect(this,SIGNAL(z2(bool, bool)),pp,SLOT(resiv(bool, bool)));
    


    pp->setFlag(QGraphicsItem::ItemIsFocusable);
    scene->setFocus();
    timer->start(40);

    connect(p, SIGNAL(res1(int)), this, SLOT(pol1(int)));
    connect(p, SIGNAL(res2(int)), this, SLOT(pol2(int)));

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::on_pushButton_2_clicked()  //Игра на 2 игроков
{
    ui->label_2->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->label->show();
    ui->label_3->show();
    ui->label_4->show();

    QTimer *timer = new QTimer();   //Создание таймера и сцены
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 850, 500);
    scene->setBackgroundBrush(QBrush(QColor(0, 0, 0, 255)));
    scene->setStickyFocus(true);    //При нажатие на сцену, фокус с нее не сбрасывается

    int paddleIndent = 70;  //Отступ от края экрана
    pong *p = new pong(scene, timer);
    slider *pp = new slider(p, scene, timer, paddleIndent);
    en_slider *en = new en_slider(p, scene, timer, paddleIndent);
    scene->setFocus();

    scene->installEventFilter(this);
    connect(this,SIGNAL(z2(bool,bool)),pp,SLOT(resiv(bool,bool)));
    connect(this,SIGNAL(z1(bool,bool)),en,SLOT(resiv(bool,bool)));

    pp->setFlag(QGraphicsItem::ItemIsFocusable);
    en->setFlag(QGraphicsItem::ItemIsFocusable);

    timer->start(40);

    connect(p, SIGNAL(res1(int)), this, SLOT(pol1(int)));
    connect(p, SIGNAL(res2(int)), this, SLOT(pol2(int)));

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}
