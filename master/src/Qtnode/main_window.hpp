#ifndef Qtnode_MAIN_WINDOW_H
#define Qtnode_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace Qtnode {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(int argc, char** argv, QWidget *parent = 0);
    ~MainWindow();



    void closeEvent(QCloseEvent *event); // Overloaded function

signals:
    void startCam();
    void stopCam();

public slots:
    void vidUp(QImage);

protected slots:
    virtual void on_startCam_pressed();
    virtual void on_stopCam_pressed();
    virtual void on_leftB_pressed();
    virtual void on_leftB_released();
    virtual void on_rightB_pressed();
    virtual void on_rightB_released();
    void printOut(std::string);
    void printOut(QString);

private:
    Ui::MainWindowDesign ui;
    QNode qnode;
};

}  // namespace Qtnode

#endif // Qtnode_MAIN_WINDOW_H
