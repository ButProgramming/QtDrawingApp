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
    leftMouseIsDown = true;

    unselectShapes();

    if(event->button() == Qt::LeftButton)
    {
        point.setX(event->x());
        point.setY(event->y());

        // avoid false shape printing, when a new shape is creating
        lastPoint = point;
    }


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
        if(isConnectedWithShape(QPoint(event->x(), event->y()), IDs.first))
        {
            shape = new ConnectionLine(point);
            dynamic_cast<ConnectionLine*>(shape)->linkToShape(IDs.first, NULL);
        }
        else
            QMessageBox::information(this, "Wrong connection", "The line is not connected to a shape center");

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
    if(!shapes.empty() && leftMouseIsDown)
    {
        if(tool==Tool::RECTAGLE || tool==Tool::ELLIPSE || tool == Tool::TRIANGLE)
            shapes.back()->updateCreate(lastPoint);
        else if(tool == Tool::CONNTECTION_LINE)
            if(dynamic_cast<ConnectionLine*>(shapes.back())!=nullptr) // if the last pushed element is a connection line.
                shapes.back()->updateCreate(lastPoint);               // it will work only if a connection line was created,
                                                                      // in other words isConnectedWithShape -> true (in mousePressEvent)
    }

    // move the shape
    lastPoint.setX(event->x());
    lastPoint.setY(event->y());
    moveSelectedShape(lastPoint);
    if(tool==Tool::MOVE && leftMouseIsDown)
        point = lastPoint;


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
        checkLineConnection();

    IDs.first = 0;
    IDs.second = 0;

    leftMouseIsDown = false;

    lastPoint.setX(event->x());
    lastPoint.setY(event->y());

    moveSelectedShape(lastPoint);
    update();
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    for(const auto& shape:shapes)
        shape->draw(this);
}

void MainWindow::unselectShapes()
{
    for(const auto& shape:shapes)
        if(dynamic_cast<AreaShape*>(shape)!=nullptr)
            dynamic_cast<AreaShape*>(shape)->setSelected(false);
}

void MainWindow::moveSelectedShape(const QPoint &lastPoint)
{
    for(const auto& shape:shapes)
        if(dynamic_cast<AreaShape*>(shape)!=nullptr)
            if(dynamic_cast<AreaShape*>(shape)->isSelected())
                dynamic_cast<AreaShape*>(shape)->update(point - lastPoint);
}

void MainWindow::drawCenters(bool shouldDrawCenters)
{
    for(const auto& shape:shapes)
    {
        if(dynamic_cast<AreaShape*>(shape)!=nullptr)
        {
            if(shouldDrawCenters)
                dynamic_cast<AreaShape*>(shape)->drawCenter(true);
            else
                dynamic_cast<AreaShape*>(shape)->drawCenter(false);
        }
    }
}

bool MainWindow::isConnectedWithShape(QPoint point, int& IDConntectedWith)
{
    for(const auto& shape:shapes)
    {
        if(dynamic_cast<AreaShape*>(shape)!=nullptr)
        {
            if(dynamic_cast<AreaShape*>(shape)->containsCenter(point))
            {
                IDConntectedWith = dynamic_cast<AreaShape*>(shape)->getID();
                return true;
            }
        }
    }
    return false;
}

void MainWindow::loadFile()
{
    shapes.clear();
    IShape* shape = nullptr;
    int size{};
    int toolType{};
    QString filePath = QFileDialog::getOpenFileName(this, "Open a file", "", filter);

    QFile file(filePath);

    if(!file.open((QIODevice::ReadOnly)))
        return;

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_12);

    in>>size;
    in>>toolType;
    tool = static_cast<Tool>(toolType);

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
    out << static_cast<int>(shapes.size());
    out << static_cast<int>(tool);

    for(const auto& shape:shapes)
    {
        if(dynamic_cast<Ellipse*>(shape)!=nullptr)
            out << static_cast<unsigned short int>(Type::ELLIPSE);
        else if(dynamic_cast<Rectangle*>(shape)!=nullptr)
            out <<  static_cast<unsigned short int>(Type::RECTANGLE);
        else if(dynamic_cast<Triangle*>(shape)!=nullptr)
            out << static_cast<unsigned short int>(Type::TRIANGLE);
        else if(dynamic_cast<ConnectionLine*>(shape)!=nullptr)
            out << static_cast<unsigned short int>(Type::CONNECTION_LINE);

        shape->safe(out);
    }

    file.flush();
    file.close();
}

void MainWindow::checkLineConnection()
{
    if(!isConnectedWithShape(lastPoint, IDs.second) || IDs.first == IDs.second)
    {
        if(dynamic_cast<ConnectionLine*>(shapes.back())!=nullptr && // if the last pushed element is a connection line.
                shape!=nullptr) // we can't delete a connected line now because the line was not created (is equal to nullptr)
        {
            delete shapes.back();
            shapes.pop_back();
            QMessageBox::information(this, "Wrong connection", "The line is not connected to a shape center");
        }
    }
    else
    {
        dynamic_cast<ConnectionLine*>(shapes.back())->linkToShape(NULL, IDs.second);
        dynamic_cast<ConnectionLine*>(shapes.back())->updateConnection(shapes);
    }
}

void MainWindow::unsetActiveExept(const MainWindow::Tool &tool)
{
    if(Tool::ELLIPSE != tool)
    {
        ui->actionEllipse->setChecked(false);
    }
    if(Tool::RECTAGLE != tool)
    {
        ui->actionRectangle->setChecked(false);
    }
    if(Tool::TRIANGLE != tool)
    {
        ui->actionTriangle->setChecked(false);
    }
    if(Tool::CONNTECTION_LINE != tool)
    {
        ui->actionConnect->setChecked(false);
    }
    if(Tool::MOVE != tool)
    {
        ui->actionMove->setChecked(false);
    }

}

void MainWindow::setActive(const MainWindow::Tool &tool)
{
    switch(tool)
    {
    case Tool::ELLIPSE:
        ui->actionEllipse->setChecked(true);
        break;
    case Tool::RECTAGLE:
        ui->actionRectangle->setChecked(true);
        break;
    case Tool::TRIANGLE:
        ui->actionTriangle->setChecked(true);
        break;
    case Tool::CONNTECTION_LINE:
        ui->actionConnect->setChecked(true);
        break;
    case Tool::MOVE:
        ui->actionMove->setChecked(true);
        break;
    default:
        break;
    }
}

void MainWindow::selectShape(QMouseEvent *event)
{
    for(int i = shapes.size() - 1; i>=0; i--)
    {
        if(dynamic_cast<AreaShape*>(shapes[i])!=nullptr)
        {
            if(dynamic_cast<AreaShape*>(shapes[i])->contains(QPoint(event->x(), event->y())))
            {
                dynamic_cast<AreaShape*>(shapes[i])->setSelected(true);
                return;
            }
        }
    }
}

void MainWindow::on_actionLoad_triggered()
{
    loadFile();
    update();
    unsetActiveExept(tool);
    setActive(tool);
}

void MainWindow::on_actionSave_triggered()
{
    safeFile();
}

void MainWindow::on_actionEllipse_triggered()
{
    tool = Tool::ELLIPSE;
    unselectShapes();
    unsetActiveExept(Tool::ELLIPSE);
    drawCenters(false);
    update();
}

void MainWindow::on_actionTriangle_triggered()
{
    tool = Tool::TRIANGLE;
    unselectShapes();
    unsetActiveExept(Tool::TRIANGLE);
    drawCenters(false);
    update();
}

void MainWindow::on_actionRectangle_triggered()
{
    tool = Tool::RECTAGLE;
    unselectShapes();
    unsetActiveExept(Tool::RECTAGLE);
    drawCenters(false);
    update();
}

void MainWindow::on_actionConnect_triggered()
{
    tool = Tool::CONNTECTION_LINE;
    unselectShapes();
    unsetActiveExept(Tool::CONNTECTION_LINE);
    drawCenters(true);
    update();
}

void MainWindow::on_actionMove_triggered()
{
    tool = Tool::MOVE;
    unsetActiveExept(Tool::MOVE);
    drawCenters(false);
    update();
}
