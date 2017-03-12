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

    NodePair split(TreapNode *treap, int index);

    NodeTriplet split(TreapNode *treap, int leftIndex, int rightIndex);

public:

    DataStructure();

    ~DataStructure();

    void add(ValueType value, int index);

    void addOnSegment(ValueType value, int leftBound, int rightBound);

    void assignOnSegment(ValueType value, int leftBound, int rightBound);

    void remove(int index);

    ValueType getSum(int leftBound, int rightBound);

};

#endif