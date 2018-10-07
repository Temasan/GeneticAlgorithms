#ifndef GENALGSALESMAN_H
#define GENALGSALESMAN_H

//#include <math.h>
#include <QVector>
#include <QThread>
#include <QPair>
#include <QMutex>

struct populationStr{
    double distance;
    QVector<int> gen;
};

class GenAlgSalesman : public QThread
{
    Q_OBJECT
public:
    GenAlgSalesman(std::pair<int, double **> *towns, int sizePopu, int startTown, int numberIterations);
    void run () override;

    ~GenAlgSalesman();

public slots:

    void onDestroyed(QObject *){
        terminate();
        //quit();
    }
    void resetAlgoritm(bool);
    void startPauseAlgoritm(bool state);

signals:
    void dataChanges(QVector<int> vectorPoints, double distance);
private:
    static bool SortPopulationByFitnessValue_comp(populationStr x, populationStr y){return (x.distance < y.distance);}
    void createPopulation(int sizePop);
    void calculateDistance();
    double calculateDistance(QVector<int> &vect);
    void crossingover();
    QVector<int> makeChange(QVector<int> child, QVector<int> parent);
    void mutate();


    QVector<int> m_defaultPopulation;
    QVector<populationStr> m_populationVector;
    QMutex *m_mutex;
    double **massDistanse = nullptr;
    int m_countsTown;
    int m_startTown;
    double m_elitNumb = 0.00001;
    double m_mutateNumb = 0.9;
    int m_numberIterations;
    int m_sizePopu;
    int m_inerations = 0;
    int m_pauseState = 0;
};

#endif // GENALGSALESMAN_H
