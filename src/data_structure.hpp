#pragma once

#ifndef DATA_STRUCTURE_HPP

#define DATA_STRUCTURE_HPP

#include <ostream>
#include "typedefs.hpp"

class TreapNode;

class SplitPredicate;

class DataStructure {
private:

    struct NodePair {

        TreapNode *left;
        TreapNode *right;

        NodePair(TreapNode *leftNode = nullptr, TreapNode *rightNode = nullptr) :
            left(leftNode), right(rightNode) {}

    };

    struct NodeTriplet {
        TreapNode *left;
        TreapNode *middle;
        TreapNode *right;

        NodeTriplet(TreapNode *leftNode = nullptr, TreapNode *middleNode = nullptr,
                    TreapNode *rightNode = nullptr) : left(leftNode), middle(middleNode), right(rightNode) {}
    };

    TreapNode *treap_;

    TreapNode* merge(TreapNode *leftNode, TreapNode *rightNode);

    TreapNode* merge(TreapNode *leftNode, TreapNode *middleNode, TreapNode *rightNode);

    NodePair split(TreapNode *treap, SplitPredicate &predicate);

    NodePair split(TreapNode *treap, SplitPredicate &&predicate);

    NodeTriplet splitTwice(TreapNode *treap, int leftIndex, int rightIndex);

    void movePermutationOnSegment(int leftBound, int rightBound, bool nextPermutation);

public:

    DataStructure();

    ~DataStructure();

    void insert(ValueType value, int index);

    void addOnSegment(ValueType value, int leftBound, int rightBound);

    void assignOnSegment(ValueType value, int leftBound, int rightBound);

    void reverseOnSegment(int leftBound, int rightBound);

    void nextPermutationOnSegment(int leftBound, int rightBound);

    void previousPermutationOnSegment(int leftBound, int rightBound);

    void erase(int index);

    int getSize() const;

    ValueType getSum(int leftBound, int rightBound);

    void printSegment(std::ostream &output, int leftBound, int rightBound);
};

#endif