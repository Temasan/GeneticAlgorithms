#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::pair<int, double **> *towns, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_countsTown(towns->first+1)
{
    ui->setupUi(this);
    ui->textEdit->setEnabled(false);
    ui->textEdit_2->setEnabled(false);

    /*m_massPoints = new double* [m];
    for(int i = 0; i< m; i++){
        m_massPoints[i] = new double[2];
        for(int j = 0; j < 2; j++){
             m_massPoints[i][j] = towns[i][j];
        }
    }*/

    m_massPoints = towns->second;
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    ui->widget->xAxis->setRange(20000, 28000);
    ui->widget->yAxis->setRange(9000, 22000);

    ui->widget_2->xAxis->setLabel("x");
    ui->widget_2->yAxis->setLabel("y");

    ui->widget_2->xAxis->setRange(0, 200);
    ui->widget_2->yAxis->setRange(30000, 70000);
    ui->widget_2->clearGraphs();
    ui->widget_2->addGraph();

    curve = new QCPCurve(ui->widget->xAxis,ui->widget->yAxis);

    curvePoints = new QCPCurve(ui->widget->xAxis,ui->widget->yAxis);
    curvePoints->setPen(QColor(50, 50, 50, 255));
    curvePoints->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

  //  m_plot->graph(0)->setData(xCurPoints,yCurPoints);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete []m_massPoints;
}
void MainWindow::onDataChanges(QVector<int> vectorPoints, double distance){


    QVector<QCPCurveData> curPoints(m_countsTown);
    int index = 0;

 //   ui->widget->;

    for(auto it = vectorPoints.begin(); it != vectorPoints.end(); it++){
    //    qDebug() << *it;
        curPoints[index] = QCPCurveData(index,m_massPoints[*it][0],m_massPoints[*it][1]);
        index ++;
  //      ui->widget->graph(0)->addData(m_massPoints[*it][0],m_massPoints[*it][1]);
    }
    curve->data()->set(curPoints, true);
    curvePoints->data()->set(curPoints, true);

    //ui->widget->axisRect()->setupFullAxesBox();
   // ui->widget->rescaleAxes();
    ui->widget->replot();

    xCurDistance.push_back(m_countIter);
    yCurDistance.push_back(distance);

    ui->widget_2->graph(0)->setData(xCurDistance,yCurDistance);
    ui->widget_2->replot();

    ui->textEdit->setText(QVariant(m_countIter).toString());
    ui->textEdit_2->setText(QVariant(distance).toString());

    m_countIter++;
}
