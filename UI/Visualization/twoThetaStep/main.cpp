#include "twothetastep.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TwoThetaStep w;
    w.show();
    return a.exec();
}
