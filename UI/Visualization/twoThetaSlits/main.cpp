#include "twothetaslits.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TwoThetaSlits w;
    w.show();
    return a.exec();
}
