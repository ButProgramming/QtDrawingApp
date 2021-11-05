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
    if(tool==Tool::ELLIPSE)
    {
        if(event->button() == Qt::LeftButton)
        {
            leftMouseIsDown = true;
            qDebug() << leftMouseIsDown  << " mousePressEvent" ;
            x = event->x();
            y = event->y();
            update();
        }

    }


}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
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



    if(leftMouseIsDown)
    {
        QPainter painter(this);
        QRect rect(x, y, lastX - x, lastY - y);
        painter.drawEllipse(rect);
    }

}
