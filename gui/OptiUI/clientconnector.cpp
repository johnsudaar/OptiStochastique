#include "clientconnector.h"

ClientConnector::ClientConnector(QObject *parent) : QObject(parent)
{

}

void ClientConnector::compute(QVariantList rank, QVariantList distanceMatrix, double c){
    int nb_team = rank.size();

    int* ranks;
    int** dist;

    ranks = (int*)malloc(nb_team * sizeof(int));
    dist = (int**)malloc(nb_team * sizeof(int*));
    for(int i = 0; i < nb_team; i++){
        ranks[i] = rank.at(i).toInt();
    }
    double max = 0;
    for(int i = 0; i < nb_team; i++){
        dist[i] = (int*)malloc(nb_team *sizeof(int));
        QVariantList array = distanceMatrix.at(i).toList();
        for(int j = 0; j < nb_team; j++){
            if(max < array.at(j).toDouble()){
                max = array.at(j).toDouble();
                dist[i][j] = array.at(j).toDouble();
            }
        }
    }

    distances = dist;
    coeff = c;
    classement = ranks;
    NB_EQUIPE = nb_team;

    for(int i = 0; i<nb_team; i++){
        for(int j = 0; j < nb_team; j++){
            dist[i][j] = dist[i][j]/max;
        }
    }

    CEvolutionaryAlgorithm* EA;

    ParametersImpl p;
    p.setDefaultParameters(0,NULL);
    CEvolutionaryAlgorithm* ea = p.newEvolutionaryAlgorithm();
    EA = ea;

    optiInit(0,NULL);

    CPopulation* pop = ea->getPopulation();

    ea->runEvolutionaryLoop();

    optiFinal(pop);
    IndividualImpl* res = (IndividualImpl*) pop->Best;

    int* poolA = res->poolA;
    int* poolB = res->poolB;

    delete pop;

    QList<QVariant> teamA;
    QList<QVariant> teamB;

    for(int i = 0; i < nb_team / 2; i++){
        teamA.append(poolA[i]);
        teamB.append(poolB[i]);
    }
    emit sendResults(QVariantList(teamA), QVariantList(teamB));
}
