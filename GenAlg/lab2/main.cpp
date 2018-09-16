#include "widget.h"
#include <QApplication>
#include <genalgrastrign.h>
#include "ui_widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::uint32_t m_GA_POPSIZE = 270;

    int n = 4;

    int m_GA_MAXITER = 35;
    QWidget *widget = new QWidget;

    GenAlgRastrign gARast(m_GA_POPSIZE,m_GA_MAXITER,n);
    //Widget w(gARast.getPoints(),gARast.getFistPopulation(),gARast.getLastPopulation());
    Ui::Widget ui;
    ui.setupUi(widget);

    ui.widget->clearGraphs();

    ui.widget->addGraph();
    //typedef std::vector<GenAlg_struct> GenAlg_vector;			// для краткости

    QVector<double> x = gARast.getBestXPopulation(), y = gARast.getBestYPopulation();

    ui.widget->graph(0)->setData(x, y);
    ui.widget->xAxis->setLabel("Итерация");
    ui.widget->yAxis->setLabel("Фитнес значение наилучшего гена");

    ui.widget->xAxis->setRange(0, m_GA_MAXITER);
    ui.widget->yAxis->setRange(0, y[0]);

    ui.label_4->setText(QString::number(m_GA_POPSIZE));
    ui.label_5->setText(QString::number(m_GA_MAXITER));
    ui.label_6->setText(QString::number(n));
    ui.label_8->setText(QString::number(y.last()));

    widget->show();
    ui.widget->replot();

    return a.exec();
}
