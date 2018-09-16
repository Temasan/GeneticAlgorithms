#include "genalgsearchmaximum.h"
#include <bitset>

GenAlgSearchMaximum::GenAlgSearchMaximum(QObject *parent) : QObject(parent)
{
    srand(unsigned(time(NULL)));

        m_population = new GenAlg_vector;
        m_points = new GenAlg_vector;
        m_fistPopulation = std::unique_ptr<GenAlg_vector>(new GenAlg_vector());
        InitPopulation(m_population,m_points);

        for (int i=0; i<m_GA_MAXITER; i++) {
            CalcFitnessDifference(*m_population);
            SortPopulationByFitnessValue(*m_population);
            qDebug() << getBest(*m_population);

            if ((*m_population)[0].fitness == 0) break;

            mate(*m_population);
         }
        qDebug() << "Рассчет окончен. Число особей - " << m_GA_POPSIZE<< ", количество итераций - "
                 << m_GA_MAXITER<< ", лучшая особь - " << getBest(*m_population);
}
void GenAlgSearchMaximum::InitPopulation(GenAlg_vector *population, GenAlg_vector *points)
{
   // int tsize = m_GA_TARGET.size();

    double res = m_maxPopSize/2 + (m_maxArg + m_minArg)/(m_maxArg - m_minArg); // середина между полож и
    // отриц значением функции
    double k = m_maxPopSize/m_GA_POPSIZE;
    for (std::uint32_t i=0; i<m_GA_POPSIZE; i++) {
        GenAlg_struct citizen;
        int koef = k*i;
        double m = getNumberValue(res,koef,m_maxPopSize);

        citizen.number = (m_maxPopSize/m_GA_POPSIZE)* i;
        citizen.Y = getResultFunc(m);
        citizen.X = m;

        population->push_back(citizen);
        m_fistPopulation->push_back(citizen);
    }

    // рассчет эталонного значения
    res = m_bigSize/2 + (m_maxArg + m_minArg)/(m_maxArg - m_minArg);
    m_fintessValue = getResultFunc(getNumberValue(res,0,m_bigSize));

    for (int i = 0; i < m_bigSize; i++){
        GenAlg_struct citizen;
        citizen.X = getNumberValue(res,i,m_bigSize);

        double promVal = getResultFunc(getNumberValue(res,i,m_bigSize));
        citizen.Y = promVal;
        if(m_fintessValue < promVal){
            m_fintessValue = promVal;
        }
        points->push_back(citizen);
    }
    qDebug() << "fitness value - " << m_fintessValue;

}

double GenAlgSearchMaximum::getNumberValue(double res, double koef, double mazPopSize){
    double m = 0;
    if(res >=0 && res <= mazPopSize){
        if(koef >= res){
            m = (koef - res) *m_maxArg/res;
        }
        else{
            m = (res - koef) *m_minArg/res;
        }
    }
    return m;
}

void GenAlgSearchMaximum::CalcFitnessDifference(GenAlg_vector &population)
{
    for (std::uint32_t i=0; i<m_GA_POPSIZE; i++) {
        population[i].fitness = m_fintessValue - population[i].Y;
    }
}


inline void GenAlgSearchMaximum::SortPopulationByFitnessValue(GenAlg_vector &population)
{ std::sort(population.begin(), population.end(), SortPopulationByFitnessValue_comp); }

void GenAlgSearchMaximum::elitism(GenAlg_vector &population,
                GenAlg_vector &buffer, int esize )
{
    buffer.resize(esize);
    for (int i=0; i<esize; i++) {
        buffer[i].number = population[i].number;
        buffer[i].fitness = population[i].fitness;
        buffer[i].X = population[i].X;
        buffer[i].Y = population[i].Y;
    }
}

void GenAlgSearchMaximum::MutateGen(GenAlg_struct &member, double res)
{
    const unsigned int tsize = 16;
    int ipos = rand() % tsize;
    std::string st_num = std::bitset<tsize>(member.number).to_string();
    for(int i = 1; i < 16; i++){
        if(i == ipos){
            if(st_num[i] == '1'){
                st_num[i] = '0';
            }
            else{
                st_num[i] = '1';
            }
            break;
        }
    }
    member.number = std::stoi(st_num,nullptr,2);
    double m = getNumberValue(res,member.number,m_maxPopSize);
    member.X = m;
    member.Y = getResultFunc(m);
}

void GenAlgSearchMaximum::mate(GenAlg_vector &population)
{
    GenAlg_vector buf;
    int esize = m_GA_POPSIZE * m_GA_ELITRATE;

    const unsigned long int tsize = 16;
    int spos, i1, i2;

    elitism(population, buf, m_GA_POPSIZE);

    double res = m_maxPopSize/2 + (m_maxArg + m_minArg)/(m_maxArg - m_minArg);
//    double k = m_GA_POPSIZE/m_maxPopSize;

    for (std::uint32_t i=esize; i<m_GA_POPSIZE; i++) {

        i1 = rand() % (m_GA_POPSIZE / 2);
        i2 = rand() % (m_GA_POPSIZE / 2);
        spos = rand() % tsize;

        std::string newNumber1 = std::bitset<tsize>(population[i1].number).to_string();
        std::string newNumber2 = std::bitset<tsize>(population[i2].number).to_string();

        std::string newNumber3 = newNumber1.substr(0, spos) + newNumber2.substr(spos, tsize - spos);

        int numb = std::stoi(newNumber3,nullptr,2);
        buf[i].number = numb;
        double m = getNumberValue(res,buf[i].number,m_maxPopSize);

        buf[i].Y = getResultFunc(m);
        buf[i].X = m;

        if (rand() < m_GA_MUTATION) MutateGen(buf[i], res);
     //   qDebug() << buf[i].number << " " << buf[i].number/m_maxPopSize;

    }
    population = buf;
}

inline QString GenAlgSearchMaximum::getBest(GenAlg_vector &gav)
{
    return QString::number(gav[0].number) + ", value " + QString::number(gav[0].Y) + " (" + QString::number(gav[0].fitness) + ") ";
}

double GenAlgSearchMaximum::getResultFunc(double x){
    return (x-1)*cos(3*x-15);
}
