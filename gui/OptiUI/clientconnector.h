#ifndef CLIENTCONNECTOR_H
#define CLIENTCONNECTOR_H

#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QVariantList>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "COptionParser.h"
#include "CRandomGenerator.h"
#include "CEvolutionaryAlgorithm.h"
#include "global.h"
#include "easea/optiIndividual.hpp"

class ClientConnector : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnector(QObject *parent = 0);

signals:
    void sendResults(QVariantList teamA, QVariantList teamB);
public slots:
    void compute(QVariantList classement, QVariantList distanceMatrix, double coeff);
};

#endif // CLIENTCONNECTOR_H
