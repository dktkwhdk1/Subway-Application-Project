#define MAX_STATION 398

#include "mainwindow.h"
#include "Subway.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("SMART SUBWAY");
    w.show();

    SubwayGraph run_test;
    run_test.Subway("/home/dktkwhdk12/Subway_project/subway.txt", MAX_STATION);

    return a.exec();
}
