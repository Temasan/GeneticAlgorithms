#include "genalgrastrign.h"
#include <bitset>

GenAlgRastrign::GenAlgRastrign(std::uint32_t Popsize, int iterSize,int n, QObject *parent) : QObject(parent),
    m_GA_POPSIZE(Popsize),m_GA_MAXITER(iterSize), m_n(n)
{

    srand(unsigned(time(NULL)));

        m_population = new GenAlg_points;
        m_points = new GenAlg_points;
        m_fistPopulation = new GenAlg_points;
        InitPopulation(m_population,m_points);

        for (int i=0; i<m_GA_MAXITER; i++) {
            CalcFitnessDifference(*m_population);
            SortPopulationByFitnessValue(*m_population);

            m_xBestPoints.push_back(i);

            m_yBestPoints.push_back(getBestY(*m_population));

            qDebug() << getBest(*m_population);

           // if ((*m_population)[0].fitness == 0) break;

            mate(*m_population);
         }
        qDebug() << "Рассчет окончен. Число особей - " << m_GA_POPSIZE<< ", количество итераций - "
                 << m_GA_MAXITER<< ", лучшая особь - " << getBest(*m_population);
}
void GenAlgRastrign::InitPopulation(GenAlg_points *population, GenAlg_points *points)
{
   // int tsize = m_GA_TARGET.size();

    double res = m_maxPopSize/2 + (m_maxArg + m_minArg)/(m_maxArg - m_minArg); // середина между полож и
    // отриц значением функции
    for (std::uint32_t i=0; i<m_GA_POPSIZE; i++) {
        GenAlg_point_struct vector_point;
        GenAlg_vector vector;
        for(int j = 0; j < m_n; j++){
            GenAlg_x_struct vector_x;
            //GenAlg_struct citizen;
            int koef = rand() % QVariant(m_maxPopSize).toInt();
            double m = getNumberValue(res,koef,m_maxPopSize);

            vector_x.number = (m_maxPopSize/m_GA_POPSIZE)* i;
            vector_x.X = m;

            vector.push_back(vector_x);
        }
        vector_point.x_coord = vector;
        vector_point.Y = getResultFunc(vector_point.x_coord, m_n);
        m_fistPopulation->push_back(vector_point);
        population->push_back(vector_point);
    }

    // рассчет эталонного значения
    res = m_bigSize/2 + (m_maxArg + m_minArg)/(m_maxArg - m_minArg);
  //  m_fintessValue = getResultFunc(getNumberValue(res,0,m_bigSize));

    for (int i = 0; i < m_bigSize; i++){
        GenAlg_point_struct vector_point;
        GenAlg_vector vector;
        for(int j = 0; j < m_n; j++){
            GenAlg_x_struct vector_x;

            int koef = rand() % QVariant(m_maxPopSize).toInt();
            double m = getNumberValue(res,koef,m_maxPopSize);

            vector_x.number = (m_bigSize/m_GA_POPSIZE)* i;
            vector_x.X = m;

            vector.push_back(vector_x);
        }
        vector_point.x_coord = vector;
        vector_point.Y = getResultFunc(vector_point.x_coord, m_n);
        points->push_back(vector_point);
    }
    qDebug() << "fitness value - " << m_fintessValue;

}

double GenAlgRastrign::getNumberValue(double res, double koef, double mazPopSize){
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

void GenAlgRastrign::CalcFitnessDifference(GenAlg_points &population)
{
    for (std::uint32_t i=0; i<m_GA_POPSIZE; i++) {
        population[i].fitness = population[i].Y - m_fintessValue;
    }
}


inline void GenAlgRastrign::SortPopulationByFitnessValue(GenAlg_points &population)
{ std::sort(population.begin(), population.end(), SortPopulationByFitnessValue_comp); }

void GenAlgRastrign::elitism(GenAlg_points &population,
                GenAlg_points &buffer, int esize )
{
    buffer.resize(esize);
    for (int i=0; i<esize; i++) {
        buffer[i].x_coord = population[i].x_coord;
        buffer[i].fitness = population[i].fitness;
        buffer[i].Y = population[i].Y;
    }
}

void GenAlgRastrign::MutateGen(GenAlg_point_struct &member, double res)
{
    const unsigned int tsize = 16;
    for(int i = 0; i < m_n; i++){
        int ipos = rand() % tsize;
        std::string st_num = std::bitset<tsize>(member.x_coord[i].number).to_string();
        if(st_num[ipos] == '1'){
            st_num[ipos] = '0';
        }
        else{
            st_num[ipos] = '1';
        }
        member.x_coord[i].number = std::stoi(st_num,nullptr,2);
        double m = getNumberValue(res,member.x_coord[i].number,m_maxPopSize);
        member.x_coord[i].X = m;
    }
    member.Y = getResultFunc(member.x_coord, m_n);
}

void GenAlgRastrign::mate(GenAlg_points &population)
{
    GenAlg_points buf;
    int esize = m_GA_POPSIZE * m_GA_ELITRATE;

    const unsigned long int tsize = 16;
    int spos, i1, i2;

    elitism(population, buf, m_GA_POPSIZE);

    double res = m_maxPopSize/2 + (m_maxArg + m_minArg)/(m_maxArg - m_minArg);
//    double k = m_GA_POPSIZE/m_maxPopSize;

    for (std::uint32_t i=esize; i<m_GA_POPSIZE; i++) {

        for(int j = 0; j < m_n; j++){
            i1 = rand() % (m_GA_POPSIZE / 2);
            i2 = rand() % (m_GA_POPSIZE / 2);
            spos = rand() % tsize;

            std::string newNumber1 = std::bitset<tsize>(population[i1].x_coord[j].number).to_string();
            std::string newNumber2 = std::bitset<tsize>(population[i2].x_coord[j].number).to_string();

            std::string newNumber3 = newNumber1.substr(0, spos) + newNumber2.substr(spos, tsize - spos);

            int numb = std::stoi(newNumber3,nullptr,2);
            buf[i].x_coord[j].number = numb;
            double m = getNumberValue(res,buf[i].x_coord[j].number,m_maxPopSize);
           // buf[i].Y = getResultFunc(m);
            buf[i].x_coord[j].X = m;

         //   qDebug() << buf[i].number << " " << buf[i].number/m_maxPopSize;

        }

        buf[i].Y = getResultFunc(buf[i].x_coord, m_n);

        if (rand() < m_GA_MUTATION) MutateGen(buf[i], res);
    }
    population = buf;
}

inline QString GenAlgRastrign::getBest(GenAlg_points &gav)
{
    return QString::number(gav[0].Y) + " (" + QString::number(gav[0].fitness) + ") ";
}
inline double GenAlgRastrign::getBestY(GenAlg_points &gav){
    return gav[0].Y;
}

double GenAlgRastrign::getResultFunc(GenAlg_vector point, int n){
    double s = 0;
    for(int i = 0; i < n; i++){
        s = s + pow(point[i].X, 2) -10*cos(2*M_PI*point[i].X);
    }
    return s + 10*n;
}
