#pragma once

#ifndef DATA_STRUCTURE_HPP

#define DATA_STRUCTURE_HPP

#include "typedefs.hpp"

class TreapNode;

class DataStructure {
private:

    struct NodePair {

        TreapNode *left;
        TreapNode *right;

        NodePair(TreapNode *leftNode = nullptr, TreapNode *rightNode = nullptr) :
            left(leftNode), right(rightNode) {}

    };

    TreapNode *treap_;

    TreapNode* merge(TreapNode *leftNode, TreapNode *rightNode);

    NodePair split(TreapNode *treap, int index);

public:

    DataStructure();

    ~DataStructure();

    void add(ValueType value, int index);

    void assignOnSubsegment(ValueType value, int leftBound, int rightBound);

    void remove(int index);

    ValueType getSum(int leftBound, int rightBound);

};

#endif