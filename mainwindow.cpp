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


    QRect rect(x, y, NULL, NULL);
    shape = nullptr; // null it every time
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
    {
        if(isConnectedWithShape(QPoint(event->x(), event->y()), firstID))
        {
            shape = new ConnectionLine(rect);
            dynamic_cast<ConnectionLine*>(shape)->linkToShape(firstID, NULL);
        }
            break;
    }
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
    if(tool == Tool::CONNTECTION_LINE)
    {
        if(!isConnectedWithShape(QPoint(event->x(), event->y()), secondID) || firstID == secondID)
        {
            if(dynamic_cast<ConnectionLine*>(shapes.back())!=nullptr && // if the last pushed element is a connection line.
               shape!=nullptr) // we can't delete a connected line now because the line was not created (is equal to nullptr)
            {
                delete shapes.back();
                shapes.pop_back();
            }
        }
        else
        {
            dynamic_cast<ConnectionLine*>(shapes.back())->linkToShape(NULL, secondID);
            dynamic_cast<ConnectionLine*>(shapes.back())->updateConnection(shapes);
        }
    }

    firstID = 0;
    secondID = 0;
    leftMouseIsDown = false;
    lastX = event->x();
    lastY = event->y();
    QPoint lastPoint(lastX, lastY);
    moveSelectedShape(lastPoint);
    update();

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(!shapes.empty())
    {
        if(tool==Tool::RECTAGLE || tool==Tool::ELLIPSE || tool == Tool::TRIANGLE && leftMouseIsDown)
            shapes.back()->updateCreate(lastX, lastY);

        else if(tool == Tool::CONNTECTION_LINE && leftMouseIsDown)
            if(dynamic_cast<ConnectionLine*>(shapes.back())!=nullptr) // if the last pushed element is a connection line.
                  shapes.back()->updateCreate(lastX, lastY);          // it will work only if a connection line was created,
                                                                      // in other words isConnectedWithShape -> true (in mousePressEvent)

    }

    lastX = event->x();
    lastY = event->y();
    QPoint lastPoint(lastX, lastY);
    moveSelectedShape(lastPoint);
    if(tool==Tool::MOVE && leftMouseIsDown)
    {
        x = lastX;
        y = lastY;
    }

    if(leftMouseIsDown)
    {
        for(auto shape:shapes)
        {
            if(dynamic_cast<ConnectionLine*>(shape)!=nullptr)
                dynamic_cast<ConnectionLine*>(shape)->updateConnection(shapes);
        }
    }

    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    // draw shapes from vector
    for(auto shape:shapes)
    {
        shape->draw(this);
        if(dynamic_cast<ConnectionLine*>(shape)!=nullptr)
           qDebug() << dynamic_cast<ConnectionLine*>(shape)->m_firstIDShape << " " << dynamic_cast<ConnectionLine*>(shape)->m_secondIDShape;
    }


    //painter.drawEllipse(rect);

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

bool MainWindow::isConnectedWithShape(QPoint point, int& IDConntectedWith)
{
    for(auto shape:shapes)
        if(dynamic_cast<AreaShape*>(shape)!=nullptr)
            if(dynamic_cast<AreaShape*>(shape)->containsCenter(point))
            {
                IDConntectedWith = dynamic_cast<AreaShape*>(shape)->getID();
                return true;
            }

    return false;
}

void MainWindow::loadFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open a file", "", filter);

    QFile file(filePath);
    int size{};

    if(!file.open((QIODevice::ReadOnly)))
    {
        qDebug() << "lol";
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_12);
    in>>size;

    shapes.clear();

    for(int i = 0; i < size; i++)
    {
        Shape* ellipse = new Ellipse(QRect(0,0,0,0));
        ellipse->load(in);
        shapes.push_back(ellipse);
    }


    file.close();
    update();

    //QMessageBox::information(this, "...", file);
}

void MainWindow::safeFile()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save your file", "", filter);
    filePath.append(".qda");

    QFile file(filePath);
    if(!file.open((QIODevice::WriteOnly)))
        return;

    QDataStream out(&file);
    out << (int)shapes.size();

    for(auto shape:shapes)
    {
        shape->safe(out, 0);
    }

    out.setVersion(QDataStream::Qt_5_12);

    file.flush();
    file.close();

    //QMessageBox::information(this, "...", filePath);



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

void MainWindow::on_actionLoad_triggered()
{
    tool = Tool::LOAD;
    loadFile();
}

void MainWindow::on_actionSave_triggered()
{
    tool = Tool::SAFE;
    safeFile();
}
