#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QHBoxLayout *layout = new QHBoxLayout();
    QWebEngineView *view = new QWebEngineView(this);
    layout->addWidget(view);
    this->ui->centralWidget->setLayout(layout);
    view->load(QUrl("/home/john/Documents/Cours/Opti/Projet_UI/TestFlex/html/index.html"));
    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
