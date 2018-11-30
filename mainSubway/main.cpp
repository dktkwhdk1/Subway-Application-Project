#define MAX_STATION 398

#include "mainwindow.h"
#include "Subway.h"
#include <QApplication>
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>
#include <QStringData>

void SubwayGraph::Subway(const char* name, int N)
{
    QFile subway(name);

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
    QString station_name = new QString[n];
    check = new color[n];

    int n1, n2, time;
    QString s1, s2;

    subway.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!subway.atEnd())
    {
        QTextStream in(&subway);
        /*
        subway.readLine(0) >> n1;
        subway.readLine(1) >> n2;
        subway.readLine(2) >> time;
        subway.readLine(3) >> s1;
        subway.readLine(4) >> s2;
        */
        /*
        n1=(int *)in.readLine();
        n2=(int *)in.readLine();
        time=(int *)in.readLine();
        s1=(string *)in.readLine();
        s2=(string *)in.readLine();
        */
        in >> n1;
        in >> n2;
        in >> time;
        in >> s1;
        in >> s2;

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



    //ui->textBrowser->setText(in.readAll());

    subway.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("SMART SUBWAY");
    SubwayGraph run_test;
    run_test.Subway("subway.txt", MAX_STATION);
    w.show();

    /*
    QString mFilename = "/home/dktkwhdk12/Subway_project/subway.txt";

    QFile mFile(mFilename);

    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "could not open file for reading";
        return 0;
    }
    QTextStream in(&mFile);
    QString mText = in.readAll();

    qDebug() << mText;

    mFile.close();
    */
    return a.exec();
}
