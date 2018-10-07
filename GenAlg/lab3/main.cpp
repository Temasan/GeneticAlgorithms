#include "mainwindow.h"
#include <QApplication>
#include <genalgsalesman.h>
#include <QObject>
#include <QPair>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <QUrl>
#include <QDebug>

std::pair<int, double **> getTownCoors(){
    int numberTowns = 0;
    double **coodrTown = new double*[100];

    QFile file(":/coords_town.txt");
    if(file.open(QFile::ReadOnly | QFile::Text)){
        std::string bufStr;
        while(!file.atEnd()){
            bufStr = file.readLine().toStdString();
            std::vector<std::string> results;
            coodrTown[numberTowns] = new double[2];

            boost::split(results, bufStr, [](char c){return c == ' ';});
            coodrTown[numberTowns][0] = std::atof(results[0].c_str());
            coodrTown[numberTowns][1] = std::atof(results[1].c_str());

            numberTowns ++;
        }
    }
    file.close();

    return std::make_pair(numberTowns,coodrTown);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int sizePop = 7000;
    int startTown = 0;
    int numberIterations = 100;
    std::pair<int, double **> towns = getTownCoors();
    GenAlgSalesman gas(&towns,sizePop,startTown,numberIterations);
    GenAlgWindow w(&towns);
    qRegisterMetaType<QVector<int> >("QVector<int>");
    QObject::connect(&gas, SIGNAL(dataChanges(QVector<int> , double)),
                     &w, SLOT(onDataChanges(QVector<int> , double)));

    QObject::connect(w.getStartPauseButton(), SIGNAL(clicked(bool)),&gas, SLOT(startPauseAlgoritm(bool)));
    QObject::connect(w.getStopButton(), SIGNAL(clicked(bool)),&gas, SLOT(resetAlgoritm(bool)));
    QObject::connect(&w, SIGNAL(destroyed(QObject*)),
                     &gas, SLOT(onDestroyed(QObject*)));
    w.show();
    //gas.start();

    return a.exec();
}



