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
int SubwayGraph::min;
stack<int> SubwayGraph::s;

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
/*
    for (int i = 0; i < n; i++)
    {
        check[i] = white;
        map[i].num = -1;
        map[i].time = 99999999;
        map[i].transfer = 99999999;
    }

    // 시작점과 연결된 인접리스트의 시간과 환승횟수를 map에 넣는다.
    for (Station* p = map[start].next; p != NULL; p = p->next)
    {
        if (station_name[start] == station_name[p->num]) // 시작점이 곧 환승역일때

        {
            map[p->num].time = 0;
            map[p->num].transfer = 0;
        }
        else
        {
            map[p->num].time = p->time;
            map[p->num].transfer = p->transfer;
        }
    }
*/
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
            else // 최소환승 경로일때
            {
                if (map[minvalue_pos].transfer + p->transfer < map[p->num].transfer) // 환승횟수를 비교하여 업데이트
                {
                    map[p->num].time = map[minvalue_pos].time + p->time;
                    map[p->num].transfer = map[minvalue_pos].transfer + p->transfer;
                }
                else if (map[minvalue_pos].transfer + p->transfer == map[p->num].transfer) // 환승횟수가 같을 경우
                {
                    if (map[minvalue_pos].time + p->time < map[p->num].time) // 시간 비교
                    {
                        map[p->num].time = map[minvalue_pos].time + p->time;
                        map[p->num].transfer = map[minvalue_pos].transfer + p->transfer;
                    }
                }
            }
        }
    }
}

int SubwayGraph::ChooseSubwayPath(bool choose)
// choose = 1이면 최단시간을 가지는 역의
// index반환, choose = 0이면 최소환승을 가지는 역의 index반환
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

bool SubwayGraph::SubwayRoute(stack<int> &s, int start, int end) // stack에 지나간 지하철을 넣어주는 재귀함수
{
   s.push(start);

   if (start == end) // 종료조건
      return true;
   else{ // recursive
      for (Station* p = map[start].next; p != NULL; p = p->next) // 시작점에 연결된 엣지를 모두 조사한다
      {
         if (map[start].time + p->time == map[p->num].time && map[start].transfer + p->transfer == map[p->num].transfer)
         {
            if (this->SubwayRoute(s, p->num, end) == false)   s.pop();// 다음 경로가 존재하지 않을 경우
            else return true;
         }
      }
      return false;
   }
}

void MainWindow::on_search1_2_clicked() // 최단시간 클릭시
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
    for (int i = 0; i < SubwayGraph::n; i++)
    {
        SubwayGraph::check[i] = white;
        SubwayGraph::map[i].num = -1;
        SubwayGraph::map[i].time = 99999999;
        SubwayGraph::map[i].transfer = 99999999;
    }

    // 시작점과 연결된 인접리스트의 시간과 환승횟수를 map에 넣는다.
    for (Station* p = SubwayGraph::map[SubwayGraph::start].next; p != NULL; p = p->next)
    {
        if (SubwayGraph::station_name[SubwayGraph::start] == SubwayGraph::station_name[p->num]) // 시작점이 곧 환승역일때

        {
            SubwayGraph::map[p->num].time = 0;
            SubwayGraph::map[p->num].transfer = 0;
        }
        else
        {
            SubwayGraph::map[p->num].time = p->time;
            SubwayGraph::map[p->num].transfer = p->transfer;
        }
    }
    SubwayGraph subway;
    subway.Dijkstra(SubwayGraph::start, true);

    // 도착역 중에서 소요시간이 가장 작은 역의 index선택
    SubwayGraph::min = SubwayGraph::map[SubwayGraph::end].time;
    for (int i = 0; i < SubwayGraph::n; i++)
    {
        if (SubwayGraph::station_name[SubwayGraph::end] == SubwayGraph::station_name[i])
        {
            if (SubwayGraph::map[i].time < SubwayGraph::min)
            {
                SubwayGraph::min = SubwayGraph::map[i].time;
                SubwayGraph::end = i;
            }
        }
    }
    subway.SubwayRoute(SubwayGraph::s, SubwayGraph::start, SubwayGraph::end);
    stack<int> reverse_stack;
    int i, pre;
    QString station;

    while (!SubwayGraph::s.empty())
    {
       reverse_stack.push(SubwayGraph::s.top());
       SubwayGraph::s.pop();
    }

    // 경로 출력
    for (i = 0, pre = -1; !reverse_stack.empty(); i++)
    {
       if (pre != -1 && SubwayGraph::station_name[pre] == SubwayGraph::station_name[reverse_stack.top()])
       {
          if (SubwayGraph::station_name[reverse_stack.top()] != SubwayGraph::station_name[SubwayGraph::start])
            ui->textBrowser->setText("(환승)");

          i--;
          pre = reverse_stack.top();
          reverse_stack.pop();
       }
       else
       {
          if (i != 0)
          {
              ui->textBrowser->setText(" -> ");
              qDebug() << " -> ";
          }
          //MainWindow::ui->textBrowser->setText(SubwayGraph::station_name[reverse_stack.top()]);
          station = SubwayGraph::station_name[reverse_stack.top()];
          ui->textBrowser->setText(station);
          qDebug() << " " << station;
          pre = reverse_stack.top();
          reverse_stack.pop();

       }
    }

    int h = SubwayGraph::map[SubwayGraph::end].time / 60;
    int m = SubwayGraph::map[SubwayGraph::end].time % 60;
    //cout << endl << "@ 지나는 역의 수 @ : " << i - 1 << "개 " << endl;
    ui->textBrowser->setText("\n @ 지나는 역의 수 @ : ");
    ui->textBrowser->setText(QString::number(i - 1));
    ui->textBrowser->setText("개 ");
    ui->textBrowser->setText("\n");
    ui->textBrowser->setText("@ 소요시간 @ : ");
    //cout << "@ 소요시간 @ : ";
    if (SubwayGraph::map[SubwayGraph::end].time / 60 == 0){
       //cout << m << "분" << endl;
       ui->textBrowser->setText(QString::number(m));
       ui->textBrowser->setText("분");
       ui->textBrowser->setText("\n");
    }
    else{
       //cout << h << "시간 " << m << "분" << endl;
       ui->textBrowser->setText(QString::number(h));
       ui->textBrowser->setText("시간");
       ui->textBrowser->setText(QString::number(m));
       ui->textBrowser->setText("분");
       ui->textBrowser->setText("\n");
    }
    //cout << "@ 환승횟수 @ : " << map[end].transfer << "번" << endl;
    ui->textBrowser->setText("@ 환승횟수 @");
    ui->textBrowser->setText(QString::number(SubwayGraph::map[SubwayGraph::end].transfer));
    ui->textBrowser->setText("번");
    ui->textBrowser->setText("\n");
}
