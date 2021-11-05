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

    qDebug() << event->x()<< " "<<event->y();
    if(tool==Tool::ELLIPSE)
    {
        leftMouseIsDown = true;
        if(event->button() == Qt::LeftButton)
        {
            x = event->x();
            y = event->y();


            //test *t = new testChild();
            //t->printTest();
            /*IShape *a = new Ellipse();
            a->draw();
            leftMouseIsDown = true;
            qDebug() << leftMouseIsDown  << " mousePressEvent" ;
            x = event->x();
            y = event->y();
            update();
            delete a;*/
        }

    }


}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    IShape* shape = new Ellipse(x, y, event->x()- x, event->y() - y);
    shapes.push_back(shape);
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
    qDebug() << lastX - x << " " << lastY - y;
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPoint v = QCursor::pos();

    for(auto shape:shapes)
    {
        shape->draw(this);
    }
    qDebug() << leftMouseIsDown;

    if(leftMouseIsDown)
    {
        qDebug() << "here";
        QPainter painter(this);
        QRect rect(x, y, lastX - x, lastY - y);
        painter.drawEllipse(rect);
    }

}
