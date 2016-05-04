#-------------------------------------------------
#
# Project created by QtCreator 2016-05-01T03:09:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webenginewidgets websockets

TARGET = OptiUI
TEMPLATE = app

INCLUDEPATH += /usr/local/easea/libeasea/include/
INCLUDEPATH += /usr/local/easea/boost
LIBS += /usr/local/easea/libeasea/libeasea.a
LIBS += /usr/local/easea/boost/program_options.a
LIBS += -lpthread -fopenmp

SOURCES += main.cpp \
    clientconnector.cpp \
    websocketclientwrapper.cpp \
    websockettransport.cpp \
    easea/optiIndividual.cpp

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
    html/assets/js/connector.js \
    html/assets/css/loading.css

RESOURCES += \
    html.qrc

HEADERS += \
    clientconnector.h \
    websocketclientwrapper.h \
    websockettransport.h \
    easea/optiIndividual.hpp
