#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    unselectShapes();

    leftMouseIsDown = true;

    if(event->button() == Qt::LeftButton)
    {
        x = event->x();
        y = event->y();
        lastX = x;
        lastY = y;
    }



    QRect rect(x, y, 0, 0);
    IShape* shape = nullptr;
    switch(tool)
    {
    case Tool::RECTAGLE:
        shape = new Rectangle(rect);
        break;
    case Tool::ELLIPSE:
        shape = new Ellipse(rect);
        break;
    case Tool::TRIANGLE:
        shape = new Triangle(rect);
        break;
    case Tool::CONNTECTION_LINE:
        shape = new ConnectionLine(rect);
        break;
    case Tool::MOVE:
        selectShape(event);
        break;
    default:
        break;
    }
    // if the tool was not MOVE, SAFE or LOAD
    if(shape!=nullptr)
        shapes.push_back(shape);

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{


    leftMouseIsDown = false;
    lastX = event->x();
    lastY = event->y();
    QPoint lastPoint(lastX, lastY);
    moveSelectedShape(lastPoint);
    update();

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(tool!=Tool::MOVE/* || tool!=Tool::SAFE || tool!=Tool::LOAD*/)
        shapes.back()->updateCreate(lastX, lastY);
    lastX = event->x();
    lastY = event->y();
    QPoint lastPoint(lastX, lastY);
    moveSelectedShape(lastPoint);
    if(tool==Tool::MOVE && leftMouseIsDown)
    {
        x = lastX;
        y = lastY;
    }
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    // draw shapes from vector
    for(auto shape:shapes)
        shape->draw(this);

}

void MainWindow::on_actionEllipse_triggered()
{
    tool = Tool::ELLIPSE;
    unselectShapes();
    drawCenters(false);
    update();
}

void MainWindow::on_actionTriangle_triggered()
{
    tool = Tool::TRIANGLE;
    unselectShapes();
    drawCenters(false);
    update();
}

void MainWindow::on_actionRectangle_triggered()
{
    tool = Tool::RECTAGLE;
    unselectShapes();
    drawCenters(false);
    update();
}

void MainWindow::on_actionConnect_triggered()
{
    tool = Tool::CONNTECTION_LINE;
    unselectShapes();
    drawCenters(true);
    update();
}

void MainWindow::on_actionMove_triggered()
{
    tool = Tool::MOVE;
    drawCenters(false);
    update();
}

void MainWindow::unselectShapes()
{
    for(auto shape:shapes)
        if(dynamic_cast<AreaShape*>(shape)!=nullptr)
            dynamic_cast<AreaShape*>(shape)->setSelected(false);
}

void MainWindow::moveSelectedShape(const QPoint &lastPoint)
{
    for(auto shape:shapes)
        if(dynamic_cast<AreaShape*>(shape)!=nullptr)
            if(dynamic_cast<AreaShape*>(shape)->isSelected())
                dynamic_cast<AreaShape*>(shape)->update(x-lastPoint.x(), y-lastPoint.y());
}

void MainWindow::drawCenters(bool shouldDrawCenters)
{
    for(auto shape:shapes)
        if(dynamic_cast<AreaShape*>(shape)!=nullptr)
        {
            if(shouldDrawCenters)
                dynamic_cast<AreaShape*>(shape)->drawCenter(true);
            else
                dynamic_cast<AreaShape*>(shape)->drawCenter(false);
        }
}

void MainWindow::selectShape(QMouseEvent *event)
{
    for(int i = shapes.size() - 1; i>=0; i--)
        if(dynamic_cast<AreaShape*>(shapes[i])!=nullptr)
            if(dynamic_cast<AreaShape*>(shapes[i])->contains(QPoint(event->x(), event->y())))
            {
                dynamic_cast<AreaShape*>(shapes[i])->setSelected(true);
                return;
            }
}
