#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include "pong.h"
#include "slider.h"
#include "en_slider.h"

//extern bool flag;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *obj, QEvent *e);

signals:
    void z1(bool, bool);
    void z2(bool, bool);
public slots:
    void pol1(int a);
    void pol2(int a);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    bool moveUp;
    bool moveDown;
    bool moveUp_en;
    bool moveDown_en;

};


#endif // MAINWINDOW_H
