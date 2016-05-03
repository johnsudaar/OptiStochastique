#-------------------------------------------------
#
# Project created by QtCreator 2016-05-01T03:09:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webenginewidgets websockets

TARGET = OptiUI
TEMPLATE = app


SOURCES += main.cpp \
    clientconnector.cpp \
    websocketclientwrapper.cpp \
    websockettransport.cpp

DISTFILES += \
    html/assets/fonts/photon-entypo.eot \
    html/assets/fonts/photon-entypo.woff \
    html/assets/fonts/photon-entypo.ttf \
    html/assets/fonts/photon-entypo.svg \
    html/assets/css/custom.css \
    html/assets/css/photon.css \
    html/assets/css/photon.min.css \
    html/index.html \
    html/assets/js/app.js \
    html/assets/js/jquery.min.js \
    html/assets/js/qwebchannel.js \
    html/assets/js/connector.js

RESOURCES += \
    html.qrc

HEADERS += \
    clientconnector.h \
    websocketclientwrapper.h \
    websockettransport.h
