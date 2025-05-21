#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::on_createBtn_clicked()
{
    if ( ui->containerType->currentIndex() == ContainerType::LinkedList && ui->varType->currentIndex() == VarType::Int ) {
        
    }
}