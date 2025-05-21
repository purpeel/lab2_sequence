#ifndef UI_H
#define UI_H

#include <iostream>
#include <exception>
#include "Sequence.hpp"
#include "SequenceWrap.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "mainwindow.hpp"
#include "util.hpp"

template <typename T>
std::ostream& operator << ( std::ostream& os, const Sequence<T>& seq ) 
{
    for ( int index = 0; index < seq.getSize(); index ++ ) {
        os << seq[index] << ", ";
    }
    os << std::endl;
}

ICollection* createSequence( MainWindow::ContainerType ctype, MainWindow::VarType vtype ) {
    if ( vtype != MainWindow::VarType::Integer ) {
        throw Exception( Exception::ErrorCode::INVALID_TYPE );
    } else if ( ctype == MainWindow::ContainerType::Array ) {
        Sequence<int> *seq = new ArraySequence<int>(); 
        CollectionWrap<int> wrappedSeq = CollectionWrap<int>(seq);
        ICollection *collection = &wrappedSeq;
        return collection;
    } else if ( ctype == MainWindow::ContainerType::List ) {
        Sequence<int> *seq = new ListSequence<int>(); 
        CollectionWrap<int> wrappedSeq = CollectionWrap<int>(seq);
        ICollection *collection = &wrappedSeq;
        return collection;
    } else {
        throw Exception(-1);
    }
}

#endif // UI_H