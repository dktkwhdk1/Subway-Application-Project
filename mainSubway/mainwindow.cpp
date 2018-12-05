#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Subway.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QString>
#include <QApplication>
#include <QIODevice>
#include <QDebug>
#include <QStringList>
#include <QStringData>

#define MAX_STATION 398

using namespace std;

QString* SubwayGraph::station_name; // 역이름
Station* SubwayGraph::map;
color* SubwayGraph::check;
int SubwayGraph::n; // 지하철 역 갯수
int SubwayGraph::start; // 시작역
int SubwayGraph::end; // 도착역

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

void SubwayGraph::Subway(const char* name, int N)
{
    QFile subway(name);

    if(!subway.open(QIODevice::ReadOnly | QIODevice::Text))
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
    station_name = new QString[n];
    check = new color[n];

    int n1 = 0;
    int n2 = 0;
    int time = 0;
    QString s1, s2;

    QTextStream in(&subway);

    while(!in.atEnd())
    {
        in >> n1;
        if(n1 == 0)
        {
            break;  // 디버깅의 중요성, 마지막에 0을 받아서 배열에 넣으려고 해서 에러가났음
        }
        //qDebug() << " " << n1;
        in >> n2;
        //qDebug() << " " << n2;
        in >> time;
        //qDebug() << " " << time;
        in >> s1;
        //qDebug() << " " << s1;
        in >> s2;
        //qDebug() << " " << s2;

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
    subway.close();
}
void SubwayGraph::Dijkstra(int start, bool choose) // 다익스트라 알고리즘 사용
{
    int minvalue_pos;
    check[start] = gray;

    // 시작점 초기화
    map[start].time = 0;
    map[start].transfer = 0;

    for (int i = 0; i < n - 2; i++)
    {
        minvalue_pos = ChooseSubwayPath(choose);
        check[minvalue_pos] = gray;

        for (Station* p = map[minvalue_pos].next; p != NULL; p = p->next)
        {
            if (choose) // 최단시간 경로일때
            {
                if (map[minvalue_pos].time + p->time < map[p->num].time) // 시간을 비교하여 업데이트
                {
                    map[p->num].time = map[minvalue_pos].time + p->time;
                    map[p->num].transfer = map[minvalue_pos].transfer + p->transfer;
                }
                else if (map[minvalue_pos].time + p->time == map[p->num].time) // 시간이 같을 경우
                {
                    if (map[minvalue_pos].transfer + p->transfer < map[p->num].transfer) // 환승횟수 비교
                    {
                        map[p->num].time = map[minvalue_pos].time + p->time;
                        map[p->num].transfer = map[minvalue_pos].transfer + p->transfer;
                    }
                }
            }

        }
    }

}

int SubwayGraph::ChooseSubwayPath(bool choose) // choose = 1이면 최단시간을 가지는 역의

//index반환, choose = 0이면 최소환승을 가지는 역의 index반환
{
    int min_time = 99999999;
    int min_transfer = 99999999;
    int pos = -1;
    if (choose) // 최단시간
    {
        for (int i = 0; i < n; i++)
        {
            if (check[i] == white)
            {
                if (map[i].time < min_time)
                {
                    min_time = map[i].time;
                    min_transfer = map[i].transfer;
                    pos = i;
                }
                else if (map[i].time == min_time)
                {
                    if (map[i].transfer < min_transfer)
                    {
                        min_time = map[i].time;
                        min_transfer = map[i].transfer;
                        pos = i;
                    }
                }
            }
        }

    }
    else // 최소환승
    {

        for (int i = 0; i < n; i++)
        {
            if (check[i] == white)
            {
                if (map[i].transfer < min_transfer) // 환승 횟수가 작은 인접리스트 선택
                {
                    min_time = map[i].time;
                    min_transfer = map[i].transfer;
                    pos = i;
                }
                else if (map[i].transfer == min_transfer) // 환>승 횟수가 같으면
                {
                    if (map[i].time < min_time) // 시간이 덜드는 인접리스트 선택
                    {
                        min_time = map[i].time;
                        min_transfer = map[i].transfer;
                        pos = i;
                    }
                }
            }
        }

    }
    return pos; // 인덱스 반환
}


void MainWindow::on_lineEdit_2_returnPressed()
{

}

void MainWindow::on_search1_clicked()
{
    QString input_station;
    QString k = "존재하는 역이 아닙니다";
    QString k2 = "출발역과 도착역이 같습니다";

    while(SubwayGraph::start == SubwayGraph::end)
    {
        while(SubwayGraph::start == -1)
        {
            input_station = ui->lineEdit->text();

            for(int i = 0; i < SubwayGraph::n; i++)
            {
                if(SubwayGraph::station_name[i] == input_station)
                {
                    SubwayGraph::start = i;
                    break;
                }
            }

            if(SubwayGraph::start == -1)
            {
                QMessageBox::information(0,"info",k);

                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
                break;
            }
        }
        while(SubwayGraph::end == -1)
        {
            input_station = ui->lineEdit_2->text();

            for(int i = 0; i < SubwayGraph::n; i++)
            {
                if(SubwayGraph::station_name[i] == input_station)
                {
                    SubwayGraph::end = i;
                    break;
                }
            }

            if(SubwayGraph::end == -1)
            {
                QMessageBox::information(0,"info",k);
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
                break;
            }
        }

        if(SubwayGraph::start == SubwayGraph::end)
        {
            SubwayGraph::start = SubwayGraph::end = -1;
            QMessageBox::information(0,"info",k2);
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            break;
        }
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    /*
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
    */
    ui->textBrowser->setText("hello");
}
