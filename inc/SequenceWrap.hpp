#ifndef ICOLLECTION_H
#define ICOLLECTION_H

#include "Sequence.hpp"

class ICollection
{
public:
    virtual ~ICollection() = default;

    virtual const int getSize() const = 0;
    virtual const bool isEmpty() const = 0;
};

template <typename T>
class CollectionWrap : public ICollection
{
private:
    Sequence<T> *seq;
public:
    CollectionWrap(Sequence<T>* seq) : seq(seq) {}
public:
    const int getSize() const override { return seq->getSize(); }
    const bool isEmpty() const override { return seq->isEmpty(); }
};

#endif // ICOLLECTION_H



