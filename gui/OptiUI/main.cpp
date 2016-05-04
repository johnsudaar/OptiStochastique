#include "websocketclientwrapper.h"
#include "websockettransport.h"
#include "clientconnector.h"
#include <QApplication>
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QWebSocketServer>
#include <QWebChannel>
#include <QMainWindow>
#include <QFile>
#include <QSslConfiguration>
#include <QSslKey>
#include <QSslCertificate>
#include <QDebug>

CIndividual** pPopulation = NULL;
CIndividual*  bBest = NULL;
float* pEZ_MUT_PROB = NULL;
float* pEZ_XOVER_PROB = NULL;
unsigned *EZ_NB_GEN;
unsigned *EZ_current_generation;
int EZ_POP_SIZE;
int OFFSPRING_SIZE;
int coeff;
double **distances;
int *classement;
int NB_EQUIPE;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    /* ---- WEBSOCKET SERVER ---- */

    QWebSocketServer server(QStringLiteral("Optimisation Server"), QWebSocketServer::NonSecureMode);

    if(!server.listen(QHostAddress::LocalHost, 1337)){
        qFatal("Cannot open WebSocket server");
        return 1;
    }

    WebSocketClientWrapper clientWrapper(&server);
    QWebChannel channel;

    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected, &channel, &QWebChannel::connectTo);
    ClientConnector connector;
    channel.registerObject(QStringLiteral("connector"),&connector);

    /* ---- WEB VIEW ---- */

    QWebEngineView *webview = new QWebEngineView();

    QWebEngineSettings *defaultSettings = webview->settings();

    defaultSettings->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    defaultSettings->setAttribute(QWebEngineSettings::JavascriptEnabled,true);
    //defaultSettings->setOfflineWebApplicationCachePath(QDir::homePath()+"/xscreen");
    //defaultSettings->enablePersistentStorage(QDir::homePath()+"/xscreen");
    //defaultSettings->setAttribute(QWebEngineSettings::, true);

    webview->load(QUrl("qrc:/html/index.html"));

    QMainWindow *window = new QMainWindow();

    window->setCentralWidget(webview);
    window->setWindowTitle("Optimisation Stochastique");
    window->show();

    return a.exec();
}
