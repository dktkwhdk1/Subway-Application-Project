#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Subway.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    QString start = arg1;
}
*/

void MainWindow::on_pushButton_clicked()
{
    /*
    QString filename = "/home/dktkwhdk12/Subway_project/subway.txt";

    QFile subway(filename);

    if(!subway.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(0,"info",subway.errorString());
    }

    start = -1; end = -1;// 시작역과 도착역 초기화
    //int min; // 가장 시간이 짧은 도착역 저장
    Station* temp; // file에서 읽어온 역정보를 임시저장
    Station* virtual_temp; // 아무 정보도 없는 class.
    n = N;

    // class field init
    map = new Station[n]; // 지하철 망
    station_name = new string[n];
    check = new color[n];

    int n1, n2, time;
    string s1, s2;

    if(subway.open(IO_ReadOnly))
    {
        QTextStream in(&subway);
        while(!in.atEnd())
        {
            subway >> n1;
            subway >> n2;
            subway >> time;
            subway >> s1;
            subway >> s2;

            // 배열이 0부터 시작하기 떄문에 -1씩 빼준다.
            n1 -= 1;
            n2 -= 1;

            // temp의 n2인덱스에 저장될 역정보
            temp = new Station();
            temp->num = n2;
            temp->time = time;
            if (s1 == s2){
                temp->transfer = 1;
            }
            else {
                temp->transfer = 0;
            }

            // station끼리 연결, 인접리스트를 만드는 과정
            virtual_temp = &map[n1];
            while (virtual_temp->next != NULL)
            {
                virtual_temp = virtual_temp->next;
            }
            virtual_temp->next = temp;

            // temp의 n1인덱스에 저장될 역정보
            temp = new Station();
            temp->num = n1;
            temp->time = time;
            if (s1 == s2){
                temp->transfer = 1;
            }
            else {
                temp->transfer = 0;
            }

            // station끼리 연결, 인접리스트를 만드는 과정
            virtual_temp = &map[n2];
            while (virtual_temp->next != NULL)
            {
                virtual_temp = virtual_temp->next;
            }
            virtual_temp->next = temp;

            station_name[n1] = s1;
            station_name[n2] = s2;
        }
    }



    //ui->textBrowser->setText(in.readAll());

    subway.close();
    */
}

void MainWindow::on_pushButton_3_clicked()
{
    //QMessageBox::information(this, tr("최단시간 경로"), tr("HELLO"));
    QString filename = "/home/dktkwhdk12/Subway_project/subway.txt";

    QFile subway(filename);

    if(!subway.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(0,"info",subway.errorString());
    }
    QTextStream in(&subway);
    QString r = in.readAll();
    //ui->textBrowser->setText(r);
    QMessageBox::information(this, tr("최단시간 경로"), r);

    subway.close();
}

