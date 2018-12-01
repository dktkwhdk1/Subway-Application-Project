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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.setWindowTitle("SMART SUBWAY");
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
