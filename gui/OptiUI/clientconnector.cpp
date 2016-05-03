#include "clientconnector.h"

ClientConnector::ClientConnector(QObject *parent) : QObject(parent)
{

}

void ClientConnector::compute(int i){
    qDebug() << i;
    emit sendResults(i+1);
}
