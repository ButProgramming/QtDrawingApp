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
        point.setX(event->x());
        point.setY(event->y());
        //x = event->x();
        //y = event->y();

        // avoid false shape printing, when a new shape is creating
        lastPoint = point;
        //lastX = x;
        //lastY = y;
    }


    //QPoint point(x, y);
    shape = nullptr; // null it every time
    switch(tool)
    {
    case Tool::RECTAGLE:
        shape = new Rectangle(point);
        break;
    case Tool::ELLIPSE:
        shape = new Ellipse(point);
        break;
    case Tool::TRIANGLE:
        shape = new Triangle(point);
        break;
    case Tool::CONNTECTION_LINE:
        if(isConnectedWithShape(QPoint(event->x(), event->y()), firstID))
        {
            shape = new ConnectionLine(point);
            dynamic_cast<ConnectionLine*>(shape)->linkToShape(firstID, NULL);
        }
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

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(!shapes.empty())
    {
        if(tool==Tool::RECTAGLE || tool==Tool::ELLIPSE || tool == Tool::TRIANGLE && leftMouseIsDown)
            shapes.back()->updateCreate(lastPoint);

        else if(tool == Tool::CONNTECTION_LINE && leftMouseIsDown)
            if(dynamic_cast<ConnectionLine*>(shapes.back())!=nullptr) // if the last pushed element is a connection line.
                shapes.back()->updateCreate(lastPoint);            // it will work only if a connection line was created,
                                                                      // in other words isConnectedWithShape -> true (in mousePressEvent)

    }

    //lastX = event->x();
    //lastY = event->y();
    lastPoint.setX(event->x());
    lastPoint.setY(event->y());
    //QPoint lastPoint(lastX, lastY);
    moveSelectedShape(lastPoint);
    if(tool==Tool::MOVE && leftMouseIsDown)
    {
        point = lastPoint;
        //x = lastX;
        //y = lastY;
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

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(!shapes.empty() && tool == Tool::CONNTECTION_LINE)
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


    /*if(!shapes.empty())
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
    }*/


    firstID = 0;
    secondID = 0;

    leftMouseIsDown = false;

    //lastX = event->x();
    //lastY = event->y();
    lastPoint.setX(event->x());
    lastPoint.setY(event->y());

    //QPoint lastPoint(lastX, lastY);
    moveSelectedShape(lastPoint);
    update();

}


void MainWindow::paintEvent(QPaintEvent *event)
{
    // draw shapes from vector
    for(auto shape:shapes)
    {
        shape->draw(this);
    }
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
                dynamic_cast<AreaShape*>(shape)->update(point.x()-lastPoint.x(), point.y()-lastPoint.y());
}

void MainWindow::drawCenters(bool shouldDrawCenters)
{
    for(auto shape:shapes)
        if(dynamic_cast<AreaShape*>(shape)!=nullptr)
            if(shouldDrawCenters)
                dynamic_cast<AreaShape*>(shape)->drawCenter(true);
            else
                dynamic_cast<AreaShape*>(shape)->drawCenter(false);

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
    shapes.clear();
    Shape* shape = nullptr;
    int size{};
    QString filePath = QFileDialog::getOpenFileName(this, "Open a file", "", filter);

    QFile file(filePath);

    if(!file.open((QIODevice::ReadOnly)))
        return;

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_12);

    in>>size;
    for(int i = 0; i < size; i++)
    {
        shape = nullptr;
        QRect rect(0, 0, 0, 0);
        QPoint point(0, 0);
        unsigned short int type{};
        in >> type;

        switch(type)
        {
        case static_cast<unsigned short int>(Type::ELLIPSE):
            qDebug() << "case" << static_cast<unsigned short int>(Type::ELLIPSE);
            shape = new Ellipse(point);
            break;
        case static_cast<unsigned short int>(Type::RECTANGLE):
            qDebug() << "case" << static_cast<unsigned short int>(Type::RECTANGLE);
            shape = new Rectangle(point);
            break;
        case static_cast<unsigned short int>(Type::TRIANGLE):
            qDebug() << "case" << static_cast<unsigned short int>(Type::TRIANGLE);
            shape = new Triangle(point);
            break;
        case static_cast<unsigned short int>(Type::CONNECTION_LINE):
            shape = new ConnectionLine(point);
            break;
        }
        shape->load(in);
        shapes.push_back(shape);
    }

    file.close();

}

void MainWindow::safeFile()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save your file", "", filter);
    filePath.append(".qda");

    QFile file(filePath);
    if(!file.open((QIODevice::WriteOnly)))
        return;

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_12);
    out << (int)shapes.size();

    for(auto shape:shapes)
    {
        if(dynamic_cast<Ellipse*>(shape)!=nullptr)
        {
            out << static_cast<unsigned short int>(Type::ELLIPSE);
            qDebug() << static_cast<unsigned short int>(Type::ELLIPSE);
            shape->safe(out);
        }
        else if(dynamic_cast<Rectangle*>(shape)!=nullptr)
        {
            out <<  static_cast<unsigned short int>(Type::RECTANGLE);
            qDebug() << static_cast<unsigned short int>(Type::RECTANGLE);
            shape->safe(out);
        }
        else if(dynamic_cast<Triangle*>(shape)!=nullptr)
        {
            out << static_cast<unsigned short int>(Type::TRIANGLE);
            qDebug() << static_cast<unsigned short int>(Type::TRIANGLE);
            shape->safe(out);
        }
        else if(dynamic_cast<ConnectionLine*>(shape)!=nullptr)
        {
            out << static_cast<unsigned short int>(Type::CONNECTION_LINE);
            qDebug() << static_cast<unsigned short int>(Type::CONNECTION_LINE);
            shape->safe(out);
        }


    }

    file.flush();
    file.close();
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
    //tool = Tool::LOAD;
    loadFile();
    update();
    tool = Tool::MOVE;
}

void MainWindow::on_actionSave_triggered()
{
    //tool = Tool::SAFE;
    safeFile();
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
