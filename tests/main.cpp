#include <gtest/gtest.h>
#include "../inc/tmplInc/DynamicArray.hpp"
#include "../inc/tmplInc/LinkedList.hpp"
#include "../inc/tmplInc/ArraySequence.hpp"
#include "../inc/tmplInc/ListSequence.hpp"

// DynamicArray Tests
class DynamicArrayTest : public ::testing::Test {
protected:
    DynamicArray<int>* array;

    void SetUp() override {
        array = new DynamicArray<int>();
    }

    void TearDown() override {
        delete array;
    }
};

TEST_F(DynamicArrayTest, InitiallyEmpty) {
    EXPECT_TRUE(array->isEmpty());
    EXPECT_EQ(array->getSize(), 0);
}

TEST_F(DynamicArrayTest, AppendElements) {
    array->append(1);
    array->append(2);
    array->append(3);
    
    EXPECT_EQ(array->getSize(), 3);
    EXPECT_EQ((*array)[0], 1);
    EXPECT_EQ((*array)[1], 2);
    EXPECT_EQ((*array)[2], 3);
}

TEST_F(DynamicArrayTest, PrependElements) {
    array->prepend(1);
    array->prepend(2);
    
    EXPECT_EQ(array->getSize(), 2);
    EXPECT_EQ((*array)[0], 2);
    EXPECT_EQ((*array)[1], 1);
}

TEST_F(DynamicArrayTest, InsertAtPosition) {
    array->append(1);
    array->append(3);
    array->insertAt(2, 1);
    
    EXPECT_EQ(array->getSize(), 3);
    EXPECT_EQ((*array)[0], 1);
    EXPECT_EQ((*array)[1], 2);
    EXPECT_EQ((*array)[2], 3);
}

TEST_F(DynamicArrayTest, RemoveAtPosition) {
    array->append(1);
    array->append(2);
    array->append(3);
    array->removeAt(1);
    
    EXPECT_EQ(array->getSize(), 2);
    EXPECT_EQ((*array)[0], 1);
    EXPECT_EQ((*array)[1], 3);
}

TEST_F(DynamicArrayTest, SwapElements) {
    array->append(1);
    array->append(2);
    array->swap(0, 1);
    
    EXPECT_EQ((*array)[0], 2);
    EXPECT_EQ((*array)[1], 1);
}

TEST_F(DynamicArrayTest, SubArray) {
    array->append(1);
    array->append(2);
    array->append(3);
    array->append(4);
    
    DynamicArray<int>* sub = array->subArray(1, 3);
    EXPECT_EQ(sub->getSize(), 2);
    EXPECT_EQ((*sub)[0], 2);
    EXPECT_EQ((*sub)[1], 3);
    
    delete sub;
}

TEST_F(DynamicArrayTest, CopyConstructor) {
    array->append(1);
    array->append(2);
    
    DynamicArray<int> copy(*array);
    EXPECT_EQ(copy.getSize(), 2);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
    
    // Modify original, copy should remain unchanged
    array->append(3);
    EXPECT_EQ(copy.getSize(), 2);
}

TEST_F(DynamicArrayTest, IndexOutOfBounds) {
    array->append(1);
    EXPECT_THROW((*array)[1], Exception);
    EXPECT_THROW(array->removeAt(5), Exception);
    EXPECT_THROW(array->insertAt(10, -1), Exception);
    EXPECT_THROW(array->setAt(10, 5), Exception);
    EXPECT_THROW(array->swap(-1, 0), Exception);
    EXPECT_THROW(array->swap(0, 5), Exception);
}

TEST_F(DynamicArrayTest, SetAtPosition) {
    array->append(1);
    array->append(2);
    array->append(3);
    
    array->setAt(10, 1);
    EXPECT_EQ((*array)[1], 10);
    EXPECT_EQ(array->getSize(), 3); // Size should remain unchanged
}

TEST_F(DynamicArrayTest, SubArrayInvalidIndices) {
    array->append(1);
    array->append(2);
    
    EXPECT_THROW(array->subArray(-1, 1), Exception);
    EXPECT_THROW(array->subArray(0, 5), Exception);
    EXPECT_THROW(array->subArray(2, 1), Exception); // Start > end
}

// LinkedList Tests
class LinkedListTest : public ::testing::Test {
protected:
    LinkedList<int>* list;

    void SetUp() override {
        list = new LinkedList<int>();
    }

    void TearDown() override {
        delete list;
    }
};

TEST_F(LinkedListTest, InitiallyEmpty) {
    EXPECT_TRUE(list->isEmpty());
    EXPECT_EQ(list->getSize(), 0);
}

TEST_F(LinkedListTest, AppendElements) {
    list->append(1);
    list->append(2);
    
    EXPECT_EQ(list->getSize(), 2);
    EXPECT_EQ((*list)[0], 1);
    EXPECT_EQ((*list)[1], 2);
}

TEST_F(LinkedListTest, PrependElements) {
    list->prepend(1);
    list->prepend(2);
    
    EXPECT_EQ(list->getSize(), 2);
    EXPECT_EQ((*list)[0], 2);
    EXPECT_EQ((*list)[1], 1);
}

TEST_F(LinkedListTest, InsertAtPosition) {
    list->append(1);
    list->append(3);
    list->insertAt(2, 1);
    
    EXPECT_EQ(list->getSize(), 3);
    EXPECT_EQ((*list)[0], 1);
    EXPECT_EQ((*list)[1], 2);
    EXPECT_EQ((*list)[2], 3);
}

TEST_F(LinkedListTest, PopElement) {
    list->append(1);
    list->append(2);
    list->append(3);
    list->pop(1);
    
    EXPECT_EQ(list->getSize(), 2);
    EXPECT_EQ((*list)[0], 1);
    EXPECT_EQ((*list)[1], 3);
}

TEST_F(LinkedListTest, InvalidIndices) {
    list->append(1);
    
    EXPECT_THROW((*list)[1], Exception);
    EXPECT_THROW(list->pop(-1), Exception);
    EXPECT_THROW(list->pop(5), Exception);
    EXPECT_THROW(list->insertAt(10, -1), Exception);
    EXPECT_THROW(list->setAt(10, 5), Exception);
    EXPECT_THROW(list->swap(-1, 0), Exception);
    EXPECT_THROW(list->swap(0, 5), Exception);
}

TEST_F(LinkedListTest, SetAtPosition) {
    list->append(1);
    list->append(2);
    list->append(3);
    
    list->setAt(10, 1);
    EXPECT_EQ((*list)[1], 10);
    EXPECT_EQ(list->getSize(), 3); // Size should remain unchanged
}

TEST_F(LinkedListTest, SwapElements) {
    list->append(1);
    list->append(2);
    list->append(3);
    
    list->swap(0, 2);
    EXPECT_EQ((*list)[0], 3);
    EXPECT_EQ((*list)[1], 2);
    EXPECT_EQ((*list)[2], 1);
}

// ArraySequence Tests
class ArraySequenceTest : public ::testing::Test {
protected:
    ArraySequence<int>* seq;

    void SetUp() override {
        seq = new ArraySequence<int>();
    }

    void TearDown() override {
        delete seq;
    }
};

TEST_F(ArraySequenceTest, InitiallyEmpty) {
    EXPECT_TRUE(seq->isEmpty());
    EXPECT_EQ(seq->getSize(), 0);
}

TEST_F(ArraySequenceTest, AppendElements) {
    seq->append(1);
    seq->append(2);
    
    EXPECT_EQ(seq->getSize(), 2);
    EXPECT_EQ((*seq)[0], 1);
    EXPECT_EQ((*seq)[1], 2);
}

TEST_F(ArraySequenceTest, PrependElements) {
    seq->prepend(1);
    seq->prepend(2);
    
    EXPECT_EQ(seq->getSize(), 2);
    EXPECT_EQ((*seq)[0], 2);
    EXPECT_EQ((*seq)[1], 1);
}

TEST_F(ArraySequenceTest, GetSubSequence) {
    seq->append(1);
    seq->append(2);
    seq->append(3);
    seq->append(4);
    
    Sequence<int>* sub = seq->getSubSequence(1, 3);
    EXPECT_EQ(sub->getSize(), 2);
    EXPECT_EQ((*sub)[0], 2);
    EXPECT_EQ((*sub)[1], 3);
    
    delete sub;
}

TEST_F(ArraySequenceTest, InvalidIndices) {
    seq->append(1);
    
    EXPECT_THROW((*seq)[1], Exception);
    EXPECT_THROW(seq->removeAt(-1), Exception);
    EXPECT_THROW(seq->removeAt(5), Exception);
    EXPECT_THROW(seq->insertAt(10, -1), Exception);
    EXPECT_THROW(seq->setAt(10, 5), Exception);
    EXPECT_THROW(seq->swap(-1, 0), Exception);
    EXPECT_THROW(seq->swap(0, 5), Exception);
    EXPECT_THROW(seq->getSubSequence(-1, 1), Exception);
    EXPECT_THROW(seq->getSubSequence(0, 5), Exception);
    EXPECT_THROW(seq->getSubSequence(2, 1), Exception); // Start > end
}

TEST_F(ArraySequenceTest, SetAtAndSwap) {
    seq->append(1);
    seq->append(2);
    seq->append(3);
    
    seq->setAt(10, 1);
    EXPECT_EQ((*seq)[1], 10);
    
    seq->swap(0, 2);
    EXPECT_EQ((*seq)[0], 3);
    EXPECT_EQ((*seq)[1], 10);
    EXPECT_EQ((*seq)[2], 1);
}

// ListSequence Tests
class ListSequenceTest : public ::testing::Test {
protected:
    ListSequence<int>* seq;

    void SetUp() override {
        seq = new ListSequence<int>();
    }

    void TearDown() override {
        delete seq;
    }
};

TEST_F(ListSequenceTest, InitiallyEmpty) {
    EXPECT_TRUE(seq->isEmpty());
    EXPECT_EQ(seq->getSize(), 0);
}

TEST_F(ListSequenceTest, AppendElements) {
    seq->append(1);
    seq->append(2);
    
    EXPECT_EQ(seq->getSize(), 2);
    EXPECT_EQ((*seq)[0], 1);
    EXPECT_EQ((*seq)[1], 2);
}

TEST_F(ListSequenceTest, PrependElements) {
    seq->prepend(1);
    seq->prepend(2);
    
    EXPECT_EQ(seq->getSize(), 2);
    EXPECT_EQ((*seq)[0], 2);
    EXPECT_EQ((*seq)[1], 1);
}

TEST_F(ListSequenceTest, GetSubSequence) {
    seq->append(1);
    seq->append(2);
    seq->append(3);
    seq->append(4);
    
    Sequence<int>* sub = seq->getSubSequence(1, 3);
    EXPECT_EQ(sub->getSize(), 2);
    EXPECT_EQ((*sub)[0], 2);
    EXPECT_EQ((*sub)[1], 3);
    
    delete sub;
}

TEST_F(ListSequenceTest, InvalidIndices) {
    seq->append(1);
    
    EXPECT_THROW((*seq)[1], Exception);
    EXPECT_THROW(seq->removeAt(-1), Exception);
    EXPECT_THROW(seq->removeAt(5), Exception);
    EXPECT_THROW(seq->insertAt(10, -1), Exception);
    EXPECT_THROW(seq->setAt(10, 5), Exception);
    EXPECT_THROW(seq->swap(-1, 0), Exception);
    EXPECT_THROW(seq->swap(0, 5), Exception);
    EXPECT_THROW(seq->getSubSequence(-1, 1), Exception);
    EXPECT_THROW(seq->getSubSequence(0, 5), Exception);
    EXPECT_THROW(seq->getSubSequence(2, 1), Exception); // Start > end
}

TEST_F(ListSequenceTest, SetAtAndSwap) {
    seq->append(1);
    seq->append(2);
    seq->append(3);
    
    seq->setAt(10, 1);
    EXPECT_EQ((*seq)[1], 10);
    
    seq->swap(0, 2);
    EXPECT_EQ((*seq)[0], 3);
    EXPECT_EQ((*seq)[1], 10);
    EXPECT_EQ((*seq)[2], 1);
}

// Polymorphism Tests - Testing Sequence interface with different implementations
class SequencePolymorphismTest : public ::testing::Test {
protected:
    Sequence<int>* arraySeq;
    Sequence<int>* listSeq;

    void SetUp() override {
        arraySeq = new ArraySequence<int>();
        listSeq = new ListSequence<int>();
    }

    void TearDown() override {
        delete arraySeq;
        delete listSeq;
    }
};

TEST_F(SequencePolymorphismTest, AppendToSequence) {
    arraySeq->append(1);
    arraySeq->append(2);
    
    listSeq->append(1);
    listSeq->append(2);
    
    EXPECT_EQ(arraySeq->getSize(), 2);
    EXPECT_EQ(listSeq->getSize(), 2);
    
    EXPECT_EQ((*arraySeq)[0], 1);
    EXPECT_EQ((*listSeq)[0], 1);
}

TEST_F(SequencePolymorphismTest, ConcatSequences) {
    arraySeq->append(1);
    arraySeq->append(2);
    
    listSeq->append(3);
    listSeq->append(4);

    Sequence<int>* concatArray = arraySeq->concatImmutable(*listSeq);
    EXPECT_EQ(concatArray->getSize(), 4);
    EXPECT_EQ((*concatArray)[0], 1);
    EXPECT_EQ((*concatArray)[1], 2);
    EXPECT_EQ((*concatArray)[2], 3);
    EXPECT_EQ((*concatArray)[3], 4);
    
    Sequence<int>* concatList = listSeq->concatImmutable(*arraySeq);
    EXPECT_EQ(concatList->getSize(), 4);
    EXPECT_EQ((*concatList)[0], 3);
    EXPECT_EQ((*concatList)[1], 4);
    EXPECT_EQ((*concatList)[2], 1);
    EXPECT_EQ((*concatList)[3], 2);
    
    delete concatArray;
    delete concatList;
}

TEST_F(SequencePolymorphismTest, ImmutableOperations) {
    arraySeq->append(1);
    arraySeq->append(2);
    
    // Test appendImmutable
    Sequence<int>* newSeq = arraySeq->appendImmutable(3);
    EXPECT_EQ(arraySeq->getSize(), 2); // Original unchanged
    EXPECT_EQ(newSeq->getSize(), 3);
    EXPECT_EQ((*newSeq)[2], 3);
    delete newSeq;
    
    // Test prependImmutable
    newSeq = arraySeq->prependImmutable(0);
    EXPECT_EQ(arraySeq->getSize(), 2); // Original unchanged
    EXPECT_EQ(newSeq->getSize(), 3);
    EXPECT_EQ((*newSeq)[0], 0);
    delete newSeq;
    
    // Test setAtImmutable
    newSeq = arraySeq->setAtImmutable(10, 1);
    EXPECT_EQ((*arraySeq)[1], 2); // Original unchanged
    EXPECT_EQ((*newSeq)[1], 10);
    delete newSeq;
    
    // Test swapImmutable
    newSeq = arraySeq->swapImmutable(0, 1);
    EXPECT_EQ((*arraySeq)[0], 1); // Original unchanged
    EXPECT_EQ((*newSeq)[0], 2);
    EXPECT_EQ((*newSeq)[1], 1);
    delete newSeq;
}

// Main function
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}