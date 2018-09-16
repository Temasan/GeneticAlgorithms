#ifndef GENALGRASTRIGN_H
#define GENALGRASTRIGN_H

#include <string>
#include <algorithm>
#include <time.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <memory>
#include <QDebug>
#include <QObject>

  struct GenAlg_x_struct
   {
       int number;
       double X;
   };

  typedef std::vector<GenAlg_x_struct> GenAlg_vector;			// для краткости

  struct GenAlg_point_struct
   {
       GenAlg_vector x_coord;
       double Y;
       double fitness;
   };

  typedef std::vector<GenAlg_point_struct> GenAlg_points;			// для краткости


class GenAlgRastrign : public QObject
{
    Q_OBJECT
public:
    explicit GenAlgRastrign(std::uint32_t Popsize, int iterSize,int n,QObject *parent = 0);

    /*!
     * \brief InitPopulation первоначальная инициализация популяции
     * \param population
     */
    void InitPopulation(GenAlg_points *population, GenAlg_points *points);
    /*!
     * \brief CalcFitnessDifference рассчет финтес функции для значения
     * \param population
     */
    void CalcFitnessDifference(GenAlg_points &population);

    /*!
     * \brief SortPopulationByFitnessValue_comp компоратор сортировки
     * \param x
     * \param y
     * \return
     */
    static bool SortPopulationByFitnessValue_comp(GenAlg_point_struct x, GenAlg_point_struct y)
    {
        return (x.fitness < y.fitness);
    }
    /*!
     * \brief SortPopulationByFitnessValue сортировка генов по возрастающему финтесс значению
     * \param population
     */
    inline void SortPopulationByFitnessValue(GenAlg_points &population);

    /*!
     * \brief elitism переинициализация буфера
     * \param population
     * \param buffer
     * \param esize
     */

    void elitism(GenAlg_points &population,
                    GenAlg_points &buffer, int esize );

    /*!
     * \brief MutateGen производит мутацию гена
     * \param member структура гена
     * \param res показатель расположения нуля
     */
    void MutateGen(GenAlg_point_struct &member,double res);
    /*!
     * \brief getNumberValue возвращает аргумент функции
     * \param res пограничное значение между отрицательным и положительным числом
     * \param koef число от 0 до m_maxPopSize (32768)
     * \param maxPopSize
     * \return
     */

    double getNumberValue(double res, double koef, double mazPopSize);

    /*!
     * \brief mate производит кроссинговер генов
     * \param population
     */

    void mate(GenAlg_points &population);

    /*!
     * \brief getBest возврат лучшего гена
     * \param gav
     * \return
     */

    inline QString getBest(GenAlg_points &gav);

    /*!
     * \brief GenAlgRastrign::getBestY
     * \param gav
     * \return
     */
    inline double getBestY(GenAlg_points &gav);

    /*!
     * \brief getPopulation возврат текущей популяции
     * \return
     */

    GenAlg_points *getPopulation(){
        return m_population;
    }
    /*!
     * \brief getPoints возврат всех точек функции
     * \return
     */

    QVector<double> getBestXPopulation(){

        return m_xBestPoints;
    }

    QVector<double> getBestYPopulation(){
       /* QVector<double> buf;
        std::for_each(m_population->begin(), m_population->end(),[&buf](GenAlg_struct i){
            buf.push_back(i.X);
        });*/
        return m_yBestPoints;
    }

    int getN(){
        return m_n;
    }

    /*!
     * \brief getResultFunc возврат результата расчета функции
     * \param x
     * \return
     */

    double getResultFunc(GenAlg_vector point, int n);
private:
    /*!
     * \brief m_maxPopSize максимальный показатель популяции
     */
    double m_maxPopSize = 32768;
    /*!
     * \brief m_GA_POPSIZE текущий размер популяции
     */
    std::uint32_t m_GA_POPSIZE = 1200;
    /*!
     * \brief m_GA_MAXITER число итераций
     */
    int m_GA_MAXITER = 16;
    /*!
     * \brief m_GA_ELITRATE показатель элитарности - отсутпа от генов с наилучшим результатом
     */
    double m_GA_ELITRATE = 0.10f;
    /*!
     * \brief m_GA_MUTATIONRATE вероятность мутации
     */
    double m_GA_MUTATIONRATE = 0.25f;
    /*!
     * \brief m_GA_MUTATION - функция rand используется в задании фактора случайности, поэтому устанавливает предел.
     * Если случайное значение меньше этой величины, то происходит мутация
     */

    int m_GA_MUTATION = RAND_MAX * m_GA_MUTATIONRATE;
    /*!
     * \brief m_minArg пограничный показатель минимума аргумента
     * \brief m_maxArg пограничный показатель максимума аргумента
     */

    double m_minArg = -5.12, m_maxArg = 5.12;

    int m_bigSize = 1000000;
    /*!
     * \brief m_fintessValue эталонное значение
     */

    double m_fintessValue = 0;
    /*!
     * \brief m_population вектор популяции
     */

    GenAlg_points *m_population;

    /*!
     * \brief m_fistPopulation
     */

    GenAlg_points *m_fistPopulation;

    /*!
     * \brief m_points список всех точек x и y функции
     */

    GenAlg_points * m_points;

    /*!
     * \brief xBestPoints
     */

    QVector<double> m_xBestPoints;

    /*!
     * \brief yBestPoints
     */

    QVector<double> m_yBestPoints;

    int m_n = 2;


signals:

public slots:
};

#endif // GENALGRASTRIGN_H
