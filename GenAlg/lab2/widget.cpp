#include "widget.h"
#include "ui_widget.h"

Widget::Widget(GenAlg_points *points, GenAlg_points *firstPopulation, GenAlg_points *lastPopulation, QWidget *parent) :
    QWidget(parent)/*,
    ui(new Ui::Widget)*/
{
 /*   ui->widget->clearGraphs();
    ui->widget_2->clearGraphs();

    ui->widget->addGraph();
    ui->widget_2->addGraph();

    ui->setupUi(this);
    ui->mainToolBar->addAction(ui->actionRestore);
*/
}

/*vect_double_points Widget::getDoublePoints(GenAlg_points &points, int n){
  vect_double_points doublePoints;
    for(GenAlg_point_struct i: points){
        QVector<double> point;
        for(GenAlg_point_struct j: i.x_coord){
            point.push_back(j);
        }
        doublePoints.push_back(point);
    }
    return point;
}*/

Widget::~Widget()
{
    //delete ui;
}
