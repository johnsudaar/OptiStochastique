#ifndef CLIENTCONNECTOR_H
#define CLIENTCONNECTOR_H

#include <QObject>
#include <QDebug>
#include <QJsonArray>
#include <QVariantList>

class ClientConnector : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnector(QObject *parent = 0);

signals:
    void sendResults(int i);
public slots:
    void compute(QVariantList classement, QVariantList distanceMatrix, double coeff);
};

#endif // CLIENTCONNECTOR_H
