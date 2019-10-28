#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "names.h"

GenAlgWindow::GenAlgWindow(std::pair<int, TownsCoords> towns, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_countsTown(towns.first+1)
{
    ui->setupUi(this);
    ui->textEdit->setEnabled(false);
    ui->textEdit_2->setEnabled(false);

    m_start_pause = ui->pushButton;
    m_stop = ui->pushButton_2;

    m_start_pause->connect(m_start_pause, SIGNAL(clicked(bool)), this, SLOT(changeStateStartPauseButton(bool)));

    setMassPoints(towns.second, towns.first);
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

GenAlgWindow::~GenAlgWindow()
{
    delete ui;
}

void GenAlgWindow::setMassPoints(TownsMass mass, int rows){
    //m_massPoints = new double*[rows];
    for(int i = 0; i < rows; i++){
        m_massPoints.push_back({mass[i][0],mass[i][1]});
    }
}

void GenAlgWindow::onDataChanges(QVector<int> vectorPoints, double distance){
    QVector<QCPCurveData> curPoints(m_countsTown);
    int index = 0;

    for(auto it = vectorPoints.begin(); it != vectorPoints.end(); it++){
        curPoints[index] = QCPCurveData(index,m_massPoints[*it][0],m_massPoints[*it][1]);
        index ++;
   }
    curve->data()->set(curPoints, true);
    curvePoints->data()->set(curPoints, true);

    ui->widget->replot();

    xCurDistance.push_back(m_countIter);
    yCurDistance.push_back(distance);

    ui->widget_2->graph(0)->setData(xCurDistance,yCurDistance);
    ui->widget_2->replot();

    ui->textEdit->setText(QVariant(m_countIter).toString());
    ui->textEdit_2->setText(QVariant(std::round(distance*100)/100).toString());

    m_countIter++;
}

void GenAlgWindow::changeStateStartPauseButton(bool state){
    if(state){
        m_start_pause->setText("Пауза");
    }
    else{
        m_start_pause->setText("Продолжить");
    }
}

void GenAlgWindow::resetDate(bool state){
    if(state)
    {
        ui->widget->clearPlottables();
        ui->widget_2->clearPlottables();
        m_countIter = 0;
        ui->textEdit->setText(QVariant(0).toString());
        ui->textEdit_2->setText(QVariant(0).toString());
    }
}
