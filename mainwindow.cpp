#include "mainwindow.h"
#include"textdep.h"
#include"textwidget.h"
#include"filewidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowIcon(QIcon(":/img/icon.png"));
    t = new QTabWidget(this);
    t->addTab(new textwidget(this),"Text");
    t->addTab(new filewidget(this),"FILE");


    setCentralWidget(t);
}

MainWindow::~MainWindow()
{
}

