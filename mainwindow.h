#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QEvent>

#include <QObject>
#include <QCursor>
#include <QPoint>
#include <QPainterPath>

#include "ishape.h"

//stl
#include <vector>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //virtual
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private slots:
    void on_actionEllipse_triggered();

    void on_actionTriangle_triggered();

    void on_actionRectangle_triggered();

    void on_actionConnect_triggered();

    void on_actionMove_triggered();

private:
    Ui::MainWindow *ui;
    enum class Tool // добавление "class" к enum определяет перечисление с ограниченной областью видимости, вместо стандартного "глобального" перечисления
    {
        SAFE, // LEMON находится внутри той же области видимости, что и Fruits
        LOAD,
        ELLIPSE,
        RECTAGLE,
        TRIANGLE,
        CONNTECTION_LINE,
        MOVE
    };
    Tool tool;
    QPainter painter;
    int x;
    int y;
    int lastX;
    int lastY;
    bool leftMouseIsDown = false;
    vector<IShape*> shapes;



    //vector<


};
#endif // MAINWINDOW_H
