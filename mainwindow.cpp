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
    if(tool==Tool::ELLIPSE)
    {
        if(event->button() == Qt::LeftButton)
        {
            x = event->x();
            y = event->y();
        }
    }
    else if(tool == Tool::TRIANGLE)
    {
        if(event->button() == Qt::LeftButton)
        {
            x = event->x();
            y = event->y();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(tool == Tool::ELLIPSE)
    {
        IShape* shape = new Ellipse(x, y, event->x()- x, event->y() - y);
        shapes.push_back(shape);
    }
    else if(tool == Tool::TRIANGLE)
    {
        QRect rect(x, y, event->x()- x, event->y() - y);
        IShape* shape = new Triangle(rect);
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
    if(leftMouseIsDown && tool == Tool::ELLIPSE)
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





}

void MainWindow::on_actionTriangle_triggered()
{
    tool = Tool::TRIANGLE;
}
