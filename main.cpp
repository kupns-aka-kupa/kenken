#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(data);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
