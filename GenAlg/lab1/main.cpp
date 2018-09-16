#include <QCoreApplication>
#include <genalgsearchmaximum.h>
#include "ui_form.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QApplication app(argc, argv);
    GenAlgSearchMaximum genAlgSearchMaximum;
    Ui::Form ui;
    QWidget *widget = new QWidget;
    ui.setupUi(widget);

    ui.widget->clearGraphs();
    ui.widget_2->clearGraphs();

    ui.widget->addGraph();
    ui.widget_2->addGraph();
    //typedef std::vector<GenAlg_struct> GenAlg_vector;			// для краткости

    QVector<double> x = genAlgSearchMaximum.getXPoint(), y = genAlgSearchMaximum.getYPoint();

    QVector<double> xP = genAlgSearchMaximum.getXFistPopulation(), yP = genAlgSearchMaximum.getYFistPopulation();


    ui.widget->graph(0)->setData(x, y);
    ui.widget->xAxis->setLabel("x");
    ui.widget->yAxis->setLabel("y");

    ui.widget->xAxis->setRange(-10, 10);
    ui.widget->yAxis->setRange(-15, 15);

    ui.widget->addGraph();

    ui.widget->graph(1)->setData(xP, yP);
    ui.widget->graph(1)->setPen(QColor(50, 50, 50, 255));
    ui.widget->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

    ui.widget->graph(1)->setLineStyle(QCPGraph::lsNone);

    xP = genAlgSearchMaximum.getXPopulation(), yP = genAlgSearchMaximum.getYPopulation();

    ui.widget_2->graph(0)->setData(x, y);
    ui.widget_2->xAxis->setLabel("x");
    ui.widget_2->yAxis->setLabel("y");

    ui.widget_2->xAxis->setRange(-10, 10);
    ui.widget_2->yAxis->setRange(-15, 15);

    ui.widget_2->addGraph();

    ui.widget_2->graph(1)->setData(xP, yP);
    ui.widget_2->graph(1)->setPen(QColor(50, 50, 50, 255));
    ui.widget_2->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

    ui.widget_2->graph(1)->setLineStyle(QCPGraph::lsNone);

    widget->show();
    ui.widget->replot();

    return app.exec();
    //return 0;
}

