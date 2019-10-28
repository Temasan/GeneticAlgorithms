#ifndef GENALGSALESMAN_H
#define GENALGSALESMAN_H

//#include <math.h>
#include <QVector>
#include <QThread>
#include <QPair>
#include <QMutex>
#include <memory>
#include "names.h"

struct populationStr{
    double distance;
    QVector<int> gen;
};

class GenAlgSalesman : public QThread
{
    Q_OBJECT
public:
    GenAlgSalesman(std::pair<int, TownsCoords> towns, int sizePopu, int startTown, int numberIterations);
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
    /*!
     * \brief создать набор популяций
     */
    void createPopulation(int sizePop);
    /*!
     * \brief расчитать дистанцию
     */
    void calculateDistance();
    double calculateDistance(QVector<int> &vect);
    /*!
     * \brief произвести кроссинговер для генов m_populationVector
     */
    void crossingover();
    /*!
     * \brief Вернуть новый ген по двум переданным. Производит спаривание генов, в результате остаются два.
     * Возвращается наиболее валидный
     */
    QVector<int> makeChange(QVector<int> child, QVector<int> parent);
    /*!
     * \brief произвести мутации популяциям
     */
    void mutate();
private:
    QVector<int> m_defaultPopulation;
    QVector<populationStr> m_populationVector;
    std::unique_ptr<QMutex> m_mutex;
    TownsMass m_massDistanse;
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
