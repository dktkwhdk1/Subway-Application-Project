#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>

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
