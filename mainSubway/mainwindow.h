#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QMessageBox>
#include "Subway.h"
#include <iostream>
#include <fstream>
#include <stack> // 지하철 경로를 출력할때 필요
#include <string>
#include <QString>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    /*
    SubwayGraph station_name; // 역이름
    SubwayGraph map;
    SubwayGraph check;
    SubwayGraph n; // 지하철 역 갯수
    SubwayGraph start; // 시작역
    SubwayGraph end; // 도착역
    */
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    //void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    //void on_lineEdit_textEdited(const QString &arg1);

    void on_search1_clicked();

    void on_lineEdit_returnPressed();

    void on_lineEdit_2_returnPressed();

private:
    Ui::MainWindow *ui;
};

//extern MainWindow *theMainWindow;

#endif // MAINWINDOW_H
