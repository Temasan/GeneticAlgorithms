#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::pair<int, double **> *towns, QWidget *parent = 0);
    ~MainWindow();
public slots:
    void onDataChanges(QVector<int> vectorPoints, double distance);

private:
    Ui::MainWindow *ui;
    QCustomPlot *m_Area;
    QCustomPlot *m_plot;
    int m_countIter = 0;
    double **m_massPoints = nullptr;
    int m_countsTown;
    QVector<double> yCurDistance;
    QVector<double> xCurDistance;

    QVector<double> xCurPoints;
    QVector<double> yCurPoints;

    QCPCurve *curve;
    QCPCurve *curvePoints;
};

#endif // MAINWINDOW_H
