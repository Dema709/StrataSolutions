#include "GraphWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphWidget w;
    w.show();
    return a.exec();
}
