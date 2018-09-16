#ifndef GENALGSEARCHMAXIMUM_H
#define GENALGSEARCHMAXIMUM_H

#include <string>
#include <algorithm>
#include <time.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <memory>
#include <QDebug>
#include <QObject>

  struct GenAlg_struct
   {
       double fitness;
       int number;
       double Y;
       double X;
   };

  typedef std::vector<GenAlg_struct> GenAlg_vector;			// для краткости

class GenAlgSearchMaximum : public QObject
{
    Q_OBJECT
public:
    explicit GenAlgSearchMaximum(QObject *parent = 0);

    /*!
     * \brief InitPopulation первоначальная инициализация популяции
     * \param population
     */
    void InitPopulation(GenAlg_vector *population, GenAlg_vector *points);
    /*!
     * \brief CalcFitnessDifference рассчет финтес функции для значения
     * \param population
     */
    void CalcFitnessDifference(GenAlg_vector &population);

    /*!
     * \brief SortPopulationByFitnessValue_comp компоратор сортировки
     * \param x
     * \param y
     * \return
     */
    static bool SortPopulationByFitnessValue_comp(GenAlg_struct x, GenAlg_struct y)
    {
        return (x.fitness < y.fitness);
    }
    /*!
     * \brief SortPopulationByFitnessValue сортировка генов по возрастающему финтесс значению
     * \param population
     */
    inline void SortPopulationByFitnessValue(GenAlg_vector &population);

    /*!
     * \brief elitism переинициализация буфера
     * \param population
     * \param buffer
     * \param esize
     */

    void elitism(GenAlg_vector &population,
                    GenAlg_vector &buffer, int esize );

    /*!
     * \brief MutateGen производит мутацию гена
     * \param member структура гена
     * \param res показатель расположения нуля
     */
    void MutateGen(GenAlg_struct &member,double res);
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

    void mate(GenAlg_vector &population);

    /*!
     * \brief getBest возврат лучшего гена
     * \param gav
     * \return
     */

    inline QString getBest(GenAlg_vector &gav);
    /*!
     * \brief getPopulation возврат текущей популяции
     * \return
     */

    GenAlg_vector *getPopulation(){
        return m_population;
    }
    /*!
     * \brief getPoints возврат всех точек функции
     * \return
     */

    GenAlg_vector *getPoints(){
        return m_points;
    }

    QVector<double> getXFistPopulation(){
        QVector<double> buf;
        std::for_each(m_fistPopulation->begin(), m_fistPopulation->end(),[&buf](GenAlg_struct i){
            buf.push_back(i.X);
        });
        return buf;
    }

    QVector<double> getYFistPopulation(){
        QVector<double> buf;
        std::for_each(m_fistPopulation->begin(), m_fistPopulation->end(),[&buf](GenAlg_struct i){
            buf.push_back(i.Y);
        });
        return buf;
    }



    QVector<double> getXPopulation(){
        QVector<double> buf;
        std::for_each(m_population->begin(), m_population->end(),[&buf](GenAlg_struct i){
            buf.push_back(i.X);
        });
        return buf;
    }

    QVector<double> getYPopulation(){
        QVector<double> buf;
        std::for_each(m_population->begin(), m_population->end(),[&buf](GenAlg_struct i){
            buf.push_back(i.Y);
        });
        return buf;
    }

    QVector<double> getXPoint(){
        QVector<double> buf;
        std::for_each(m_points->begin(), m_points->end(),[&buf](GenAlg_struct i){
            buf.push_back(i.X);
        });
        return buf;
    }

    QVector<double> getYPoint(){
        QVector<double> buf;
        std::for_each(m_points->begin(), m_points->end(),[&buf](GenAlg_struct i){
            buf.push_back(i.Y);
        });
        return buf;
    }

    /*!
     * \brief getResultFunc возврат результата расчета функции
     * \param x
     * \return
     */

    double getResultFunc(double x);
private:
    /*!
     * \brief m_maxPopSize максимальный показатель популяции
     */
    double m_maxPopSize = 32768;
    /*!
     * \brief m_GA_POPSIZE текущий размер популяции
     */
    std::uint32_t m_GA_POPSIZE = 90;
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

    int m_minArg = -10, m_maxArg = 10;

    int m_bigSize = 1000000;
    /*!
     * \brief m_fintessValue эталонное значение
     */

    double m_fintessValue = 0;
    /*!
     * \brief m_population вектор популяции
     */

    GenAlg_vector *m_population;

    /*!
     * \brief m_fistPopulation
     */

    std::unique_ptr<GenAlg_vector> m_fistPopulation;

    /*!
     * \brief m_points список всех точек x и y функции
     */

    GenAlg_vector * m_points;


signals:

public slots:
};

#endif // GENALGSEARCHMAXIMUM_H
