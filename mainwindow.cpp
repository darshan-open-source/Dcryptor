#include "mainwindow.h"
#include"textwidget.h"
#include"filewidget.h"
#include"About_Decryptor.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowIcon(QIcon(":/img/icon.png"));
    t = new QTabWidget(this);
    t->addTab(new textwidget(this),"Text");
    t->addTab(new filewidget(this),"File");
    t->addTab(new About_Decryptor(this), "About");
    t->tabBar()->setDocumentMode(true);
    t->setStyleSheet("QTabBar::tab {background-color: #f2f2f2;color: #333333;padding: 8px;}QTabBar::tab:selected{ background-color: #007bff;color: white;border-radius: 4px;border-radius: 4px;} QTabWidget::pane{background:transparent};");
    t->tabBar()->setExpanding(true);
    setCentralWidget(t);
}

MainWindow::~MainWindow()
{
}

