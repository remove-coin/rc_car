#include <QtGui/QApplication>
#include "rc_car.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RC_Car w;
    w.show();

    return a.exec();
}
