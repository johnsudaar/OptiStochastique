#ifndef CLIENTCONNECTOR_H
#define CLIENTCONNECTOR_H

#include <QObject>
#include <QDebug>

class ClientConnector : public QObject
{
    Q_OBJECT
public:
    explicit ClientConnector(QObject *parent = 0);

signals:
    void sendResults(int i);
public slots:
    void compute(int i);
};

#endif // CLIENTCONNECTOR_H
