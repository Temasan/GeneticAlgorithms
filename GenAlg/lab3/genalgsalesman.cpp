#include "genalgsalesman.h"
#include <QDebug>
#include <math.h>

GenAlgSalesman::GenAlgSalesman(std::pair<int, TownsCoords  > towns, int sizePopu, int startTown, int numberIterations):
    m_countsTown(towns.first),
    m_startTown(startTown),
    m_numberIterations(numberIterations),
    m_sizePopu(sizePopu)
{
    srand(unsigned(time(NULL)));
    for(int i = 0; i< towns.first; i++){
        m_defaultPopulation.push_back(i);
        std::vector<double> fDist;
        for(int j = 0; j < m_countsTown; j++){
            double x1 = towns.second[i][0], x2 = towns.second[j][0];
            double y1 = towns.second[i][1], y2 = towns.second[j][1];
            double res = std::pow((x2 - x1), 2) + std::pow((y2-y1),2);

            fDist.push_back(res == 0? 0: std::sqrt(res));
     //       qDebug() << massDistanse[i][j];
        }
        m_massDistanse.push_back(fDist);

   //     qDebug() << "*****";
    }
    m_mutex.reset(new QMutex());
    createPopulation(m_sizePopu);

}
void GenAlgSalesman::run(){
    m_inerations = 0;
    for(int i = 0; i < m_numberIterations; i++){
        m_mutex->lock();
        if(m_pauseState != 0)
            m_mutex->lock();
        crossingover();
        mutate();
        calculateDistance();
        std::sort(m_populationVector.begin(), m_populationVector.end(), SortPopulationByFitnessValue_comp);
        emit dataChanges(m_populationVector[0].gen, m_populationVector[0].distance);
        m_inerations++;
        m_mutex->unlock();
    }

  //  qDebug() << "Расчет завершен. Лучшая дистанция - " << m_populationVector[0].distance;
}

GenAlgSalesman::~GenAlgSalesman(){
    m_numberIterations = 0;
    m_mutex->lock();
    terminate();
}

void GenAlgSalesman::createPopulation(int sizePop){
    for(int i = 0; i < sizePop; i++){
        QVector<int> bufDefPop (m_defaultPopulation);
        populationStr bufPop;
        bufPop.gen.push_back(m_startTown);
        // пока буфер не пустой
        while(!bufDefPop.empty()){
            // берем случайное число в размере буфера
            int m = random()%bufDefPop.count();
            // записываем его
            int town = bufDefPop.at(m);
            // и удаляем  из буфера
            bufDefPop.remove(m);
            // если в нашем векторе уже имеется (случай выпадения начального города)
            if(bufPop.gen.contains(town))
                continue; // то просто идем дальше
            // иначе записываем выпавший город
            bufPop.gen.push_back(town);
        }
        // добавляем в конец наш город
        bufPop.gen.push_back(m_startTown);
        m_populationVector.push_back(bufPop);
    }
}

void GenAlgSalesman::calculateDistance(){
    for(auto it = m_populationVector.begin(); it != m_populationVector.end(); it++){
        it->distance = calculateDistance(it->gen);
    }
}


double GenAlgSalesman::calculateDistance(QVector<int> &vect){
    double distance = 0;
    int lastTown = vect[0];
    for(int i: vect){
        distance += m_massDistanse[lastTown][i];
        lastTown = i;
    }
    return distance;
}

void GenAlgSalesman::crossingover(){
    //QVector<populationStr> popVecBuf = m_populationVector;
    for(int i = m_sizePopu*m_elitNumb; i < m_sizePopu; i++){
        int randParent = random()%(m_countsTown-2) + 1;
        //int randKrosDist = random();
        m_populationVector[i].gen = makeChange(m_populationVector[i].gen, m_populationVector[randParent].gen);
    }
}

QVector<int> GenAlgSalesman::makeChange(QVector<int> child, QVector<int> parent)
{
    int randNumb = random()%(m_countsTown-2) + 1;
    QVector<int> parent1,parent2, child1,child2;
    parent1.append(child);
    parent2.append(parent);
    // cтавим черту в рандомном месте
    // переписываем детям куски до этой линии от их родителей
    for(int i = 0; i < randNumb; i++){
        child1.push_back(parent1[0]);
        child2.push_back(parent2[0]);
        parent1.remove(0);
        parent2.remove(0);
    }
    // далее, после черты переписываем куски от вторых родителей
    // если встречается повторяющиеся, то тупо пропускаем
    for(int i = randNumb; i < m_countsTown; i++){
        if(!child1.contains(parent2[0])){
            child1.push_back(parent2[0]);
        }
        parent2.remove(0);
        if(!child2.contains(parent1[0])){
            child2.push_back(parent1[0]);
        }
        parent1.remove(0);
    }
    // переписав все части, дописываем недостающие в порядке следования генов

    // ребенок один от первого родителя, ребенок два от второго
    for(auto it = child.begin(); it != child.end(); it++){
        if(!child1.contains((*it))){
            child1.push_back((*it));
        }
    }
    child1.push_back(m_startTown);
    for(auto it = parent.begin(); it != parent.end(); it++){
        if(!child2.contains((*it))){
            child2.push_back((*it));
        }
    }
    child2.push_back(m_startTown);

    double dist1 = calculateDistance(child1),dist2 = calculateDistance(child2);

    if(dist1 > dist2){
        return child2;
    }
        return child1;
}
void GenAlgSalesman::mutate(){
    for(int i = m_sizePopu*m_elitNumb; i < m_sizePopu; i++){
        if (m_mutateNumb*10 - random()%10 >=0){
            int randTown1 = 0,randTown2 = 0;
            while(randTown1 == randTown2){
                randTown1 = random()%(m_countsTown-2) + 1;
                randTown2 = random()%(m_countsTown-2) + 1;
            }
            //int randKrosDist = random();
            QVector<int> buf = m_populationVector[i].gen;
            int numbTown1 = buf[randTown1];
            buf.replace(randTown1, buf.at(randTown2));
            buf.replace(randTown2, numbTown1);
            m_populationVector[i].gen = buf;
        }
    }
}

void GenAlgSalesman::resetAlgoritm(bool){
    terminate();
}

void GenAlgSalesman::startPauseAlgoritm(bool state){
    if(state){
        m_pauseState = 0;
        m_mutex->unlock();
        if(!m_inerations)
            start();
    }
    else{
        m_pauseState = 1;
    }
}

