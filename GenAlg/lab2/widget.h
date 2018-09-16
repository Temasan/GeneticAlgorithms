#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <genalgrastrign.h>
#include <QVector>
#include <qcustomplot.h>
#include <QLayout>

typedef QVector<QVector<double>> vect_double_points;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(GenAlg_points *points,
                    GenAlg_points *firstPopulation, GenAlg_points *lastPopulation, QWidget *parent = 0);
    ~Widget();

private:
   // Ui::Widget *ui;

   // vect_double_points getDoublePoints(GenAlg_points &points, int n);

   // QGridLayout *grLay;
    //Qwt3D::SurfacePlot *surf;
};

#endif // WIDGET_H
