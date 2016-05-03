#include "clientconnector.h"

ClientConnector::ClientConnector(QObject *parent) : QObject(parent)
{

}

void ClientConnector::compute(QVariantList classement, QVariantList distanceMatrix, double coeff){
    for(int i = 0; i < classement.size(); i++){
    }

    for(int i = 0; i < distanceMatrix.size(); i++){
        QVariantList array = distanceMatrix.at(i).toList();
        for(int j = 0; j < array.size(); j++){
        }
    }

    qDebug() << coeff;
    emit sendResults(0);
}
