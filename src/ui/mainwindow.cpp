#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <exception>
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

void MainWindow::showError( const std::exception &ex ) {
    QString message = QString( ex.what() );
    statusBar()->showMessage( message, 5000 );
}

void MainWindow::on_createBtn_clicked()
{
    try {
        ICollectionTuple<Sequence, int, double>* tuple;

        if ( ui->containerType->currentIndex() == SequenceType::ARRAY ) {

            if ( ui->varType->currentIndex() == VarType::INT ) {
                tuple = WrapFactory::enwrap<int, ArraySequence>();
            } else if ( ui->varType->currentIndex() == VarType::DOUBLE ) {
                tuple = WrapFactory::enwrap<double, ArraySequence>();
            } else {
                throw Exception( Exception::ErrorCode::INVALID_TYPE );
            }

        } else if ( ui->containerType->currentIndex() == SequenceType::LIST ) {

            if ( ui->varType->currentIndex() == VarType::INT ) {
                tuple = WrapFactory::enwrap<int, ListSequence>();
            } else if ( ui->varType->currentIndex() == VarType::DOUBLE ) {
                tuple = WrapFactory::enwrap<double, ListSequence>();
            } else {
                throw Exception( Exception::ErrorCode::INVALID_TYPE );
            }

        } else {
            throw Exception( Exception::ErrorCode::INVALID_TYPE);
        }
        QListWidgetItem* item = new QListWidgetItem( QString::fromStdString( tuple->getCollection()->print() ));
        item->setData(Qt::UserRole, QVariant::fromValue(tuple));
        ui->seqList->addItem(item);
    } catch ( std::exception &ex ) {
        showError(Exception(ex));
    }
}

void MainWindow::on_deleteBtn_clicked()
{
    try {
        QListWidgetItem* item = ui->seqList->takeItem(ui->seqList->currentRow());
        if (item) {
            auto tuple = item->data(Qt::UserRole).value<SequenceTuple>();
            auto clct = tuple->getCollection();
            delete tuple;
            delete item;
        } else {
            throw Exception( Exception::ErrorCode::INVALID_SELECTION ) ;
        }
    } catch ( Exception &ex ) {
        showError(Exception(ex));
    }
}

void MainWindow::on_appendBtn_clicked()
{
    try {
        QListWidgetItem* item = ui->seqList->item(ui->seqList->currentRow());
        if (item) {
            auto tuple = item->data(Qt::UserRole).value<SequenceTuple>();
            auto clct = tuple->getCollection();

            if ( ui->valueInput->text().isEmpty() ) {
                throw Exception( Exception::ErrorCode::EMPTY_INPUT );
            }

            if ( clct->typeId == VarType::INT ) { 
                tuple->get<int>()->append( ui->valueInput->text().toInt() );
                item->setText( QString::fromStdString( tuple->getCollection()->print()) );
            } else if ( clct->typeId == VarType::DOUBLE ) { 
                tuple->get<double>()->append( ui->valueInput->text().toDouble() );
                item->setText( QString::fromStdString( tuple->getCollection()->print()) );
            }
            else { throw Exception( Exception::ErrorCode::INVALID_TYPE ); }
        } else {
            throw Exception( Exception::ErrorCode::INVALID_SELECTION ) ;
        }
    } catch ( Exception &ex ) {
        showError(Exception(ex));
    }
}

void MainWindow::on_prependBtn_clicked()
{
    try {
        QListWidgetItem* item = ui->seqList->item(ui->seqList->currentRow());
        if (item) {
            auto tuple = item->data(Qt::UserRole).value<SequenceTuple>();
            auto clct = tuple->getCollection();

            if ( ui->valueInput->text().isEmpty() ) {
                throw Exception( Exception::ErrorCode::EMPTY_INPUT );
            }

            if ( clct->typeId == VarType::INT ) { 
                tuple->get<int>()->prepend( ui->valueInput->text().toInt() );
                item->setText( QString::fromStdString( tuple->getCollection()->print()) );
            } else if ( clct->typeId == VarType::DOUBLE ) { 
                tuple->get<double>()->prepend( ui->valueInput->text().toDouble() );
                item->setText( QString::fromStdString( tuple->getCollection()->print()) );
            }
            else { throw Exception( Exception::ErrorCode::INVALID_TYPE ); }
        } else {
            throw Exception( Exception::ErrorCode::INVALID_SELECTION ) ;
        }
    } catch ( Exception &ex ) {
        showError(Exception(ex));
    }
}

void MainWindow::on_removeAtBtn_clicked()
{
    try {
        QListWidgetItem* item = ui->seqList->item(ui->seqList->currentRow());
        if (item) {
            auto tuple = item->data(Qt::UserRole).value<SequenceTuple>();
            auto clct = tuple->getCollection();

            if ( ui->index1Input->text().isEmpty() ) {
                throw Exception( Exception::ErrorCode::EMPTY_INPUT );
            }

            if ( clct->typeId == VarType::INT ) { 
                tuple->get<int>()->removeAt( ui->index1Input->text().toInt() );
                item->setText( QString::fromStdString( tuple->getCollection()->print()) );
            } else if ( clct->typeId == VarType::DOUBLE ) { 
                tuple->get<double>()->removeAt( ui->index1Input->text().toInt() );
                item->setText( QString::fromStdString( tuple->getCollection()->print()) );
            } else { throw Exception( Exception::ErrorCode::INVALID_TYPE ); }
        } else {
            throw Exception( Exception::ErrorCode::INVALID_SELECTION ) ;
        }
    } catch ( Exception &ex ) {
        showError(Exception(ex));
    }
}

void MainWindow::on_setAtBtn_clicked()
{
    try {
        QListWidgetItem* item = ui->seqList->item(ui->seqList->currentRow());
        if (item) {
            auto tuple = item->data(Qt::UserRole).value<SequenceTuple>();
            auto clct = tuple->getCollection();

            if ( ui->index1Input->text().isEmpty() || ui->valueInput->text().isEmpty() ) {
                throw Exception( Exception::ErrorCode::EMPTY_INPUT );
            }

            if ( clct->typeId == VarType::INT ) { 

                tuple->get<int>()->setAt( ui->valueInput->text().toInt(), ui->index1Input->text().toInt() );
                item->setText( QString::fromStdString( tuple->getCollection()->print()) );

            } else if ( clct->typeId == VarType::DOUBLE ) { 

                tuple->get<double>()->setAt( ui->valueInput->text().toDouble(), ui->index1Input->text().toInt() );
                item->setText( QString::fromStdString( tuple->getCollection()->print()) );

            } else { throw Exception( Exception::ErrorCode::INVALID_TYPE ); }
        } else {
            throw Exception( Exception::ErrorCode::INVALID_SELECTION ) ;
        }
    } catch ( Exception &ex ) {
        showError(Exception(ex));
    }
}

void MainWindow::on_insertAtBtn_clicked()
{
    try {
        QListWidgetItem* item = ui->seqList->item(ui->seqList->currentRow());
        if (item) {
            auto tuple = item->data(Qt::UserRole).value<SequenceTuple>();
            auto clct = tuple->getCollection();

            if ( ui->index1Input->text().isEmpty() || ui->valueInput->text().isEmpty() ) {
                throw Exception( Exception::ErrorCode::EMPTY_INPUT );
            }

            if ( clct->typeId == VarType::INT ) { 

                tuple->get<int>()->insertAt( ui->valueInput->text().toInt(), ui->index1Input->text().toInt() );
                item->setText( QString::fromStdString( tuple->getCollection()->print()) );

            } else if ( clct->typeId == VarType::DOUBLE ) { 

                tuple->get<double>()->insertAt( ui->valueInput->text().toDouble(), ui->index1Input->text().toInt() );
                item->setText( QString::fromStdString( tuple->getCollection()->print()) );

            } else { throw Exception( Exception::ErrorCode::INVALID_TYPE ); }
        } else {
            throw Exception( Exception::ErrorCode::INVALID_SELECTION ) ;
        }
    } catch ( Exception &ex ) {
        showError(Exception(ex));
    }
}

void MainWindow::on_swapBtn_clicked() 
{
    try {
        QListWidgetItem* item = ui->seqList->item(ui->seqList->currentRow());
        if (item) {
            auto tuple = item->data(Qt::UserRole).value<SequenceTuple>();
            auto clct = tuple->getCollection();

            if ( ui->index1Input->text().isEmpty() || ui->index2Input->text().isEmpty() ) {
                throw Exception( Exception::ErrorCode::EMPTY_INPUT );
            }

            if ( clct->typeId == VarType::INT ) { 

                tuple->get<int>()->swap( ui->index1Input->text().toInt(), ui->index2Input->text().toInt() );
                item->setText( QString::fromStdString( tuple->getCollection()->print()) );

            } else if ( clct->typeId == VarType::DOUBLE ) { 

                tuple->get<double>()->insertAt( ui->index1Input->text().toInt(), ui->index2Input->text().toInt() );
                item->setText( QString::fromStdString( tuple->getCollection()->print()) );

            } else { throw Exception( Exception::ErrorCode::INVALID_TYPE ); }
        } else {
            throw Exception( Exception::ErrorCode::INVALID_SELECTION ) ;
        }
    } catch ( Exception &ex ) {
        showError(Exception(ex));
    }
}

