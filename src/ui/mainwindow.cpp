#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <exception>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->seqList->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
    for (int i = 0; i < ui->seqList->count(); ++i) {
        auto* item = ui->seqList->item(i);
        auto tuple = item->data(Qt::UserRole).value<SequenceTuple>();
        delete tuple;
    }
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

            if (!ui->isImmutable->isChecked()) {
                if ( clct->typeId == VarType::INT ) { 

                    tuple->get<int>()->append( ui->valueInput->text().toInt() );
                    item->setText( QString::fromStdString( tuple->getCollection()->print()) );

                } else if ( clct->typeId == VarType::DOUBLE ) { 

                    tuple->get<double>()->append( ui->valueInput->text().toDouble() );
                    item->setText( QString::fromStdString( tuple->getCollection()->print()) );

                } else {
                    throw Exception( Exception::ErrorCode::INVALID_TYPE ); 
                }
            } else {
                ICollectionTuple<Sequence, int, double>* changedTuple;
                if ( clct->typeId == VarType::INT ) {

                    auto seq = tuple->get<int>()->appendImmutable( ui->valueInput->text().toInt() );
                    changedTuple = WrapFactory::enwrap<int>(seq);
                    addToList(*changedTuple);

                } else if ( clct->typeId == VarType::DOUBLE ) {

                    auto seq = tuple->get<double>()->appendImmutable( ui->valueInput->text().toDouble() );
                    changedTuple = WrapFactory::enwrap<double>(seq);
                    addToList(*changedTuple);

                } else {
                    throw Exception( Exception::ErrorCode::INVALID_TYPE ); 
                }
            }
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
            if (!ui->isImmutable->isChecked()) {
                if ( clct->typeId == VarType::INT ) { 

                    tuple->get<int>()->prepend( ui->valueInput->text().toInt() );
                    item->setText( QString::fromStdString( tuple->getCollection()->print()) );

                } else if ( clct->typeId == VarType::DOUBLE ) { 

                    tuple->get<double>()->prepend( ui->valueInput->text().toDouble() );
                    item->setText( QString::fromStdString( tuple->getCollection()->print()) );

                }
                else { throw Exception( Exception::ErrorCode::INVALID_TYPE ); }
            } else {
                ICollectionTuple<Sequence, int, double>* changedTuple;
                if ( clct->typeId == VarType::INT ) {

                    auto seq = tuple->get<int>()->prependImmutable( ui->valueInput->text().toInt() );
                    changedTuple = WrapFactory::enwrap<int>(seq);
                    addToList(*changedTuple);

                } else if ( clct->typeId == VarType::DOUBLE ) {

                    auto seq = tuple->get<double>()->prependImmutable( ui->valueInput->text().toDouble() );
                    changedTuple = WrapFactory::enwrap<double>(seq);
                    addToList(*changedTuple);

                } else {
                    throw Exception( Exception::ErrorCode::INVALID_TYPE ); 
                }
            }
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
            if (!ui->isImmutable->isChecked()) {
                if ( clct->typeId == VarType::INT ) { 

                    tuple->get<int>()->removeAt( ui->index1Input->text().toInt() );
                    item->setText( QString::fromStdString( tuple->getCollection()->print()) );

                } else if ( clct->typeId == VarType::DOUBLE ) { 

                    tuple->get<double>()->removeAt( ui->index1Input->text().toInt() );
                    item->setText( QString::fromStdString( tuple->getCollection()->print()) );

                } else { throw Exception( Exception::ErrorCode::INVALID_TYPE ); }
            } else {
                ICollectionTuple<Sequence, int, double>* changedTuple;
                if ( clct->typeId == VarType::INT ) {

                    auto seq = tuple->get<int>()->removeAtImmutable( ui->index1Input->text().toInt() );
                    changedTuple = WrapFactory::enwrap<int>(seq);
                    addToList(*changedTuple);

                } else if ( clct->typeId == VarType::DOUBLE ) {

                    auto seq = tuple->get<double>()->removeAtImmutable( ui->index2Input->text().toInt() );
                    changedTuple = WrapFactory::enwrap<double>(seq);
                    addToList(*changedTuple);

                } else {
                    throw Exception( Exception::ErrorCode::INVALID_TYPE ); 
                }
            }
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

            if (!ui->isImmutable->isChecked()) {
                if ( clct->typeId == VarType::INT ) { 

                    tuple->get<int>()->setAt( ui->valueInput->text().toInt(), ui->index1Input->text().toInt() );
                    item->setText( QString::fromStdString( tuple->getCollection()->print()) );

                } else if ( clct->typeId == VarType::DOUBLE ) { 

                    tuple->get<double>()->setAt( ui->valueInput->text().toDouble(), ui->index1Input->text().toInt() );
                    item->setText( QString::fromStdString( tuple->getCollection()->print()) );

                } else { throw Exception( Exception::ErrorCode::INVALID_TYPE ); }
            } else {
                ICollectionTuple<Sequence, int, double>* changedTuple;
                if ( clct->typeId == VarType::INT ) {

                    auto seq = tuple->get<int>()->setAtImmutable( ui->valueInput->text().toInt(), ui->index1Input->text().toInt() );;
                    changedTuple = WrapFactory::enwrap<int>(seq);
                    addToList(*changedTuple);

                } else if ( clct->typeId == VarType::DOUBLE ) {

                    auto seq = tuple->get<double>()->setAtImmutable( ui->valueInput->text().toDouble(), ui->index1Input->text().toInt() );
                    changedTuple = WrapFactory::enwrap<double>(seq);
                    addToList(*changedTuple);

                } else {
                    throw Exception( Exception::ErrorCode::INVALID_TYPE ); 
                }
            }
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

            if (!ui->isImmutable->isChecked()) {
                if ( clct->typeId == VarType::INT ) { 

                    tuple->get<int>()->insertAt( ui->valueInput->text().toInt(), ui->index1Input->text().toInt() );
                    item->setText( QString::fromStdString( tuple->getCollection()->print()) );

                } else if ( clct->typeId == VarType::DOUBLE ) { 

                    tuple->get<double>()->insertAt( ui->valueInput->text().toDouble(), ui->index1Input->text().toInt() );
                    item->setText( QString::fromStdString( tuple->getCollection()->print()) );

                } else { throw Exception( Exception::ErrorCode::INVALID_TYPE ); }
            } else {
                ICollectionTuple<Sequence, int, double>* changedTuple;
                if ( clct->typeId == VarType::INT ) {

                    auto seq = tuple->get<int>()->insertAtImmutable( ui->valueInput->text().toInt(), ui->index1Input->text().toInt() );;
                    changedTuple = WrapFactory::enwrap<int>(seq);
                    addToList(*changedTuple);

                } else if ( clct->typeId == VarType::DOUBLE ) {

                    auto seq = tuple->get<double>()->insertAtImmutable( ui->valueInput->text().toDouble(), ui->index1Input->text().toInt() );
                    changedTuple = WrapFactory::enwrap<double>(seq);
                    addToList(*changedTuple);

                } else {
                    throw Exception( Exception::ErrorCode::INVALID_TYPE ); 
                }
            }
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

            if (!ui->isImmutable->isChecked()) {
                if ( clct->typeId == VarType::INT ) { 

                    tuple->get<int>()->swap( ui->index1Input->text().toInt(), ui->index2Input->text().toInt() );
                    item->setText( QString::fromStdString( tuple->getCollection()->print()) );

                } else if ( clct->typeId == VarType::DOUBLE ) { 

                    tuple->get<double>()->swap( ui->index1Input->text().toInt(), ui->index2Input->text().toInt() );
                    item->setText( QString::fromStdString( tuple->getCollection()->print()) );

                } else { throw Exception( Exception::ErrorCode::INVALID_TYPE ); }
            } else {
                ICollectionTuple<Sequence, int, double>* changedTuple;
                if ( clct->typeId == VarType::INT ) {

                    auto seq = tuple->get<int>()->swapImmutable( ui->index1Input->text().toInt(), ui->index2Input->text().toInt() );
                    changedTuple = WrapFactory::enwrap<int>(seq);
                    addToList(*changedTuple);

                } else if ( clct->typeId == VarType::DOUBLE ) {

                    auto seq = tuple->get<double>()->swapImmutable( ui->index1Input->text().toInt(), ui->index2Input->text().toInt() );
                    changedTuple = WrapFactory::enwrap<double>(seq);
                    addToList(*changedTuple);

                } else {
                    throw Exception( Exception::ErrorCode::INVALID_TYPE ); 
                }
            }
        } else {
            throw Exception( Exception::ErrorCode::INVALID_SELECTION ) ;
        }
    } catch ( Exception &ex ) {
        showError(Exception(ex));
    }
}

void MainWindow::addToList( ICollectionTuple<Sequence, int, double>& tuple ) 
{
    QListWidgetItem* item = new QListWidgetItem( QString::fromStdString( tuple.getCollection()->print() ));
    item->setData(Qt::UserRole, QVariant::fromValue(&tuple));
    ui->seqList->addItem(item);
}

void MainWindow::on_copyBtn_clicked() 
{
    try {
        QListWidgetItem* item = ui->seqList->item(ui->seqList->currentRow());
        if (item) {
            auto tuple = item->data(Qt::UserRole).value<SequenceTuple>();
            auto clct = tuple->getCollection();

            ICollectionTuple<Sequence, int, double>* tupleCopy;
            if ( clct->typeId == VarType::INT ) {

                auto seq = tuple->get<int>()->clone();
                tupleCopy = WrapFactory::enwrap<int>(seq);
                addToList(*tupleCopy);

            } else if ( clct->typeId == VarType::DOUBLE ) {

                auto seq = tuple->get<double>()->clone();
                tupleCopy = WrapFactory::enwrap<double>(seq);
                addToList(*tupleCopy);

            } else {
                throw Exception( Exception::ErrorCode::INVALID_TYPE ); 
            }
        } else {
            throw Exception( Exception::ErrorCode::INVALID_SELECTION ) ;
        }
    } catch ( Exception &ex ) {
        showError(Exception(ex));
    }
}

void MainWindow::on_concatBtn_clicked()
{
    try {
        QList<QListWidgetItem*> selectedItems = ui->seqList->selectedItems();
        if ( selectedItems.size() != 2 ) {
            throw Exception( Exception::ErrorCode::INVALID_SELECTION ) ;
        } 
        QListWidgetItem* item1 = selectedItems[0];
        QListWidgetItem* item2 = selectedItems[1];

        if ( item1 && item2 ) {
            auto tuple1 = item1->data(Qt::UserRole).value<SequenceTuple>();
            auto tuple2 = item2->data(Qt::UserRole).value<SequenceTuple>();

            auto clct1 = tuple1->getCollection();
            auto clct2 = tuple2->getCollection();

            if (!ui->isImmutable->isChecked()) {
                if ( clct1->typeId != clct2->typeId ) {
                    throw Exception( Exception::ErrorCode::INVALID_TYPE );
                } else if ( clct1->typeId == VarType::INT ) {

                    auto seq = tuple1->get<int>()->concat(*tuple2->get<int>());
                    item1->setText( QString::fromStdString( tuple1->getCollection()->print()) );

                } else if ( clct1->typeId == VarType::DOUBLE ) {

                    auto seq = tuple1->get<double>()->concat(*tuple2->get<double>());
                    item1->setText( QString::fromStdString( tuple1->getCollection()->print()) );

                } else {
                    throw Exception( Exception::ErrorCode::INVALID_TYPE );
                }
            } else {
                ICollectionTuple<Sequence, int, double>* changedTuple;

                if ( clct1->typeId != clct2->typeId ) {
                    throw Exception( Exception::ErrorCode::INVALID_TYPE );
                } else if ( clct1->typeId == VarType::INT ) {

                    auto seq = tuple1->get<int>()->concat(*tuple2->get<int>());
                    changedTuple = WrapFactory::enwrap<int>(seq);
                    addToList(*changedTuple);

                } else if ( clct1->typeId == VarType::DOUBLE ) {

                    auto seq = tuple1->get<double>()->concat(*tuple2->get<double>());
                    changedTuple = WrapFactory::enwrap<double>(seq);
                    addToList(*changedTuple);  

                } else {
                    throw Exception( Exception::ErrorCode::INVALID_TYPE );
                }
            }
        } else {
            throw Exception( Exception::ErrorCode::INVALID_SELECTION ) ;
        }
    } catch ( Exception &ex ) {
        showError(Exception(ex));
    }
}

void MainWindow::on_subSeqBtn_clicked() 
{
    try {
        QListWidgetItem* item = ui->seqList->item(ui->seqList->currentRow());
        if (item) {
            auto tuple = item->data(Qt::UserRole).value<SequenceTuple>();
            auto clct = tuple->getCollection();

            if ( ui->index1Input->text().isEmpty() || ui->index2Input->text().isEmpty() ) {
                throw Exception( Exception::ErrorCode::EMPTY_INPUT );
            }

            ICollectionTuple<Sequence, int, double>* subTuple;

            if ( clct->typeId == VarType::INT ) {

                auto seq = tuple->get<int>()->getSubSequence( ui->index1Input->text().toInt(), ui->index2Input->text().toInt() );
                subTuple = WrapFactory::enwrap<int>(seq);
                addToList(*subTuple);

            } else if ( clct->typeId == VarType::DOUBLE ) {

                auto seq = tuple->get<double>()->getSubSequence( ui->index1Input->text().toInt(), ui->index2Input->text().toInt() );
                subTuple = WrapFactory::enwrap<double>(seq);
                addToList(*subTuple);

            } else {
                throw Exception( Exception::ErrorCode::INVALID_TYPE ); 
            }
        } else {
            throw Exception( Exception::ErrorCode::INVALID_SELECTION ) ;
        }
    } catch ( Exception &ex ) {
        showError(Exception(ex));
    }
}

//! lacks destructor for tuples in qwidgetlist; 