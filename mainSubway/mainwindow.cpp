#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

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

void MainWindow::on_pushButton_clicked()
{
    QString filename = "/home/dktkwhdk1/Subway_project/subway.txt";

    QFile subway(filename);

    if(!subway.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(0,"info",subway.errorString());
    }
    QTextStream in(&subway);

    ui->textBrowser->setText(in.readAll());

    subway.close();
}

void MainWindow::on_pushButton_3_clicked()
{
    //QMessageBox::information(this, tr("최단시간 경로"), tr("HELLO"));
    QString filename = "/home/dktkwhdk1/Subway_project/subway.txt";

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
