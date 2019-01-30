#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initChartView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showValue(QPointF pt, bool bflag)
{
    qDebug()<<"pt = "<<pt;
}

void MainWindow::initChartView()
{
    chart = new QChart();

    QLineSeries *series = new QLineSeries();
    *series << QPointF(1.0, 1.0) << QPointF(2.0, 73.0) << QPointF(3.0, 268.0) << QPointF(4.0, 17.0)
            << QPointF(5.0, 4325.0) << QPointF(6.0, 723.0);



    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle("Logarithmic axis example");

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Data point");
    axisX->setLabelFormat("%im");
    axisX->setTickCount(series->count());
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QLogValueAxis *axisY = new QLogValueAxis();
    axisY->setTitleText("Values");
    axisY->setLabelFormat("%gkg");
    axisY->setBase(8);
    //axisY->setMinorTickCount(-1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    connect(series,&QLineSeries::hovered,this,&MainWindow::showValue);

    this->setCentralWidget(chartView);
}
