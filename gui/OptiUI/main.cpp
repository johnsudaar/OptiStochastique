#include "mainwindow.h"
#include <QApplication>
#include <QWebEngineView>
#include <QWebEngineSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWebEngineView *webview = new QWebEngineView();

    QWebEngineSettings *defaultSettings = webview->settings();

    defaultSettings->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    defaultSettings->setAttribute(QWebEngineSettings::JavascriptEnabled,true);
    //defaultSettings->setOfflineWebApplicationCachePath(QDir::homePath()+"/xscreen");
    //defaultSettings->enablePersistentStorage(QDir::homePath()+"/xscreen");
    //defaultSettings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    webview->load(QUrl("qrc:/html/index.html"));

    QMainWindow *window = new QMainWindow();

    window->setCentralWidget(webview);
    window->setWindowTitle("Optimisation Stochastique");
    window->show();

    return a.exec();
}
