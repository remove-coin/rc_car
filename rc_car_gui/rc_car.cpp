#include "rc_car.h"
#include "ui_rc_car.h"

#include "ros_pi/Rpi_car.h"

RC_Car::RC_Car(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RC_Car)
{
    ui->setupUi(this);
    ros::init(argc, argv, "rc_car");
    QObject::connect(ui->leftB, SIGNAL(pressed()), this, SLOT(goLeft()));
}

RC_Car::~RC_Car()
{
    subscriber_.shutdown();
    delete ui;
}

void RC_Car::goLeft(){
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<ros_pi::Rpi_car>("/car_service");
    ros_pi::Rpi_car srv;
    if (client.call(srv))
    {
        printOut(QString("Started"));
    }
    else
    {
        printOut(QString("Failed to call service recognizer/start"));
    }
}


void RC_Car::printOut(std::string _str) {
    QString str = _str.c_str();
    ui->output->append(str);
}

void RC_Car::printOut(QString _str) {
    ui->output->append(_str);
}
