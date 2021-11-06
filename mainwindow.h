#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QMessageBox>

// classes
#include "rectangle.h"
#include "ellipse.h"
#include "triangle.h"
#include "conntectionline.h"

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
    void selectShape(QMouseEvent *event);
    void unselectShapes();
    void moveSelectedShape(const QPoint& lastPoint);
    void drawCenters(bool shouldDrawCenters);
    bool isConnectedWithShape(QPoint point, int& IDConnectedWith);
    enum class Tool
    {
        SAFE,
        LOAD,
        ELLIPSE,
        RECTAGLE,
        TRIANGLE,
        CONNTECTION_LINE,
        MOVE
    };

private:
    Ui::MainWindow *ui;
    int x{};
    int y{};
    int lastX{};
    int lastY{};
    bool leftMouseIsDown = false;
    int firstID{};
    int secondID{};
    Tool tool = Tool::MOVE;
    QPainter painter;
    vector<Shape*> shapes;

};

#endif // MAINWINDOW_H
