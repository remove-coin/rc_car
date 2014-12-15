#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "main_window.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace Qtnode {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , qnode(argc,argv)
{
    ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

    QObject::connect(&qnode, SIGNAL(cbOut(QImage)), this, SLOT(vidUp(QImage)));
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

    QObject::connect(this, SIGNAL(startCam()), &qnode, SLOT(startCam()));
    QObject::connect(this, SIGNAL(stopCam()), &qnode, SLOT(stopCam()));

    //connects subscriber/publisher and starts spinning in qnode thread
    qnode.init();
    QImage image(640, 480, QImage::Format_RGB888);
    ui.label->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

/// ====================
void MainWindow::vidUp(QImage image) {
    //ROS_INFO("got new img");
    ui.label->clear();
    ui.label->setPixmap(QPixmap::fromImage(image));
}

/*****************************************************************************
** Implementation [ui triggers]
*****************************************************************************/
/// ====================
void MainWindow::on_startCam_pressed(){
    //rosservice call /camera/start_capture
    emit startCam();
}
/// ====================
void MainWindow::on_stopCam_pressed(){
    //rosservice call /camera/stop_capture
    emit stopCam();
}
/// ====================
void MainWindow::on_leftB_pressed(){
    if (qnode.call_car(1))    {
        printOut(QString("go left"));
    } else  {
        printOut(QString("Failed to call car_service"));
    }
}
/// ====================
void MainWindow::on_leftB_released(){
    if (qnode.call_car(-1))    {
        //printOut(QString("gone left"));
    } else  {
        printOut(QString("Failed to call car_service"));
    }
}
/// ====================
void MainWindow::on_rightB_pressed(){
    if (qnode.call_car(2))    {
        printOut(QString("go right"));
    } else  {
        printOut(QString("Failed to call car_service"));
    }
}
/// ====================
void MainWindow::on_rightB_released(){
    if (qnode.call_car(-2))    {
        //printOut(QString("gone right"));
    } else  {
        printOut(QString("Failed to call car_service"));
    }
}

/// ====================
void MainWindow::on_upB_pressed(){
    if (qnode.call_car(3))    {
        printOut(QString("speed"));
    } else  {
        printOut(QString("Failed to call car_service"));
    }
}
/// ====================
void MainWindow::on_upB_released(){
    if (qnode.call_car(-3))    {
        //printOut(QString("gone right"));
    } else  {
        printOut(QString("Failed to call car_service"));
    }
}

/// ====================
void MainWindow::on_downB_pressed(){
    if (qnode.call_car(4))    {
        printOut(QString("brake"));
    } else  {
        printOut(QString("Failed to call car_service"));
    }
}
/// ====================
void MainWindow::on_downB_released(){
    if (qnode.call_car(-4))    {
        //printOut(QString("gone right"));
    } else  {
        printOut(QString("Failed to call car_service"));
    }
}

/// ====================
void MainWindow::printOut(std::string _str) {
    QString str = _str.c_str();
    ui.output->append(str);
}

void MainWindow::printOut(QString _str) {
    ui.output->append(_str);
}

/****************/
/// ====================
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}

}  // namespace Qtnode

