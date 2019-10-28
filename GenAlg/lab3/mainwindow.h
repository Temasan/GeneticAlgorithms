#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <QVector>
#include <QPushButton>
#include "names.h"

namespace Ui {
class MainWindow;
}

class GenAlgWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GenAlgWindow(std::pair<int, TownsCoords> towns, QWidget *parent = 0);
    QPushButton *getStartPauseButton(){
        return m_start_pause;
    }

    QPushButton *getStopButton(){
        return m_stop;
    }
    ~GenAlgWindow();
public slots:
    void onDataChanges(QVector<int> vectorPoints, double distance);

private:
    void setMassPoints(TownsMass mass, int rows);
    Ui::MainWindow *ui;
    QPushButton *m_start_pause;
    QPushButton *m_stop;

    int m_countIter = 0;
    TownsMass m_massPoints;
    int m_countsTown;
    QVector<double> yCurDistance;
    QVector<double> xCurDistance;

    QVector<double> xCurPoints;
    QVector<double> yCurPoints;

    QCPCurve *curve;
    QCPCurve *curvePoints;
private slots:
    void changeStateStartPauseButton(bool state);
    void resetDate(bool state);
};

#endif // MAINWINDOW_H
