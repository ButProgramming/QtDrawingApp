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


void MainWindow::on_actionEllipse_triggered()
{
    tool = Tool::ELLIPSE;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{



    leftMouseIsDown = true;

    if(event->button() == Qt::LeftButton)
    {
        x = event->x();
        y = event->y();
    }

    if(tool == Tool::MOVE)
    {
        for(auto shape:shapes)
        {
            if(dynamic_cast<AreaShape*>(shape)!=nullptr)
            {
                QPoint point(event->x(), event->y());
                if(dynamic_cast<AreaShape*>(shape)->contains(point))
                {
                    dynamic_cast<AreaShape*>(shape)->setSelected();
                }


            }
        }
    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(tool == Tool::RECTAGLE)
    {
        QRect rect(x, y, event->x()- x, event->y() - y);
        IShape* shape = new Rectangle(rect);
        shapes.push_back(shape);
    }
    else if(tool == Tool::ELLIPSE)
    {
        QRect rect(x, y, event->x()- x, event->y() - y);
        IShape* shape = new Ellipse(rect);
        //IShape* shape = new Ellipse(x, y, event->x()- x, event->y() - y);
        shapes.push_back(shape);
    }
    else if(tool == Tool::TRIANGLE)
    {
        QRect rect(x, y, event->x()- x, event->y() - y);
        IShape* shape = new Triangle(rect);
        shapes.push_back(shape);
    }
    else if(tool == Tool::CONNTECTION_LINE)
    {
        QRect rect(x, y, event->x()- x, event->y() - y);
        IShape* shape = new ConnectionLine(rect);
        shapes.push_back(shape);
    }

    leftMouseIsDown = false;
    lastX = event->x();
    lastY = event->y();
    update();
    QString s = QString("My RELEASE key");
    qDebug() << s;

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    lastX = event->x();
    lastY = event->y();
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    for(auto shape:shapes)
    {
        shape->draw(this);
    }

    QPainter painter(this);
    if(leftMouseIsDown && tool == Tool::RECTAGLE)
    {
        QRect rect(x, y, lastX - x, lastY - y);
        painter.setBrush(Qt::white);
        painter.drawRect(rect);
    }
    else if(leftMouseIsDown && tool == Tool::ELLIPSE)
    {
        QRect rect(x, y, lastX - x, lastY - y);
        painter.setBrush(Qt::white);
        painter.drawEllipse(rect);
    }
    else if(leftMouseIsDown && tool == Tool::TRIANGLE)
    {
        QRect rect(x, y, lastX - x, lastY - y);


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
        QRect rect(x, y, lastX - x, lastY - y);

        QPainterPath path;

        path.moveTo(rect.left(), rect.top());
        path.lineTo(rect.bottomRight());

        QPen pen(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawPath(path);
    }





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
