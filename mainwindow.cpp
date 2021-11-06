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

    unselectShapes(event);

    leftMouseIsDown = true;

    if(event->button() == Qt::LeftButton)
    {
        x = event->x();
        y = event->y();
    }

    if(tool == Tool::MOVE)
        selectShape(event);

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QRect rect(x, y, event->x()- x, event->y() - y);
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
    default:
        break;
    }
    // if the tool was not MOVE, SAFE or LOAD
    if(shape!=nullptr)
        shapes.push_back(shape);

    leftMouseIsDown = false;
    lastX = event->x();
    lastY = event->y();
    QPoint lastPoint(lastX, lastY);
    moveSelectedShape(lastPoint);
    update();

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
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

    // draw a shape that is going to be in the vector
    QPainter painter(this);
    QRect rect(x, y, lastX - x, lastY - y);
    if(leftMouseIsDown && tool == Tool::RECTAGLE)
    {
        painter.setBrush(Qt::white);
        painter.drawRect(rect);
    }
    else if(leftMouseIsDown && tool == Tool::ELLIPSE)
    {
        painter.setBrush(Qt::white);
        painter.drawEllipse(rect);
    }
    else if(leftMouseIsDown && tool == Tool::TRIANGLE)
    {

        QPainterPath path;

        path.moveTo(rect.left() + (rect.width() / 2), rect.top());
        path.lineTo(rect.bottomLeft());
        path.lineTo(rect.bottomRight());
        path.lineTo(rect.left() + (rect.width() / 2), rect.top());

        QPen pen(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawPath(path);
        painter.fillPath(path, QBrush(QColor ("white")));

    }
    else if(leftMouseIsDown && tool == Tool::CONNTECTION_LINE)
    {

        QPainterPath path;

        path.moveTo(rect.left(), rect.top());
        path.lineTo(rect.bottomRight());

        QPen pen(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawPath(path);
    }


}

void MainWindow::on_actionEllipse_triggered()
{
    tool = Tool::ELLIPSE;
}

void MainWindow::on_actionTriangle_triggered()
{
    tool = Tool::TRIANGLE;
}

void MainWindow::on_actionRectangle_triggered()
{
    tool = Tool::RECTAGLE;
}

void MainWindow::on_actionConnect_triggered()
{
    tool = Tool::CONNTECTION_LINE;
}

void MainWindow::on_actionMove_triggered()
{
    tool = Tool::MOVE;
}

void MainWindow::unselectShapes(QMouseEvent *event)
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
