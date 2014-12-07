#ifndef RC_CAR_H
#define RC_CAR_H

#include <QMainWindow>
#include <QWidget>
#include <QObject>
#include <QString>
#include <QTextBrowser>
#include <ros/ros.h>
#include <string>
#include <vector>

namespace Ui {
class RC_Car;
}

class RC_Car : public QMainWindow
{
    Q_OBJECT

public:
    explicit RC_Car(QWidget *parent = 0);
    ~RC_Car();

protected slots:
    virtual void goLeft();
    void printOut(std::string);
    void printOut(QString);
    
private:
    Ui::RC_Car *ui;
    ros::Subscriber subscriber_;
    int argc;
    char **argv;

};

#endif // RC_CAR_H
