#pragma once

#ifndef TREAP_HPP

#define TREAP_HPP

#include "typedefs.hpp"

class TreapNode {
private:

    ValueType value_;
    ValueType sum_;
    uint priority_;

    ValueType toAdd_;
    ValueType toAssign_;
    bool needAssign;

    int size_;

    TreapNode *leftChild_, *rightChild_;

    ValueType getSum(TreapNode *node);

    int getSize(TreapNode *node);

    void addValue(TreapNode *node, ValueType value);

    void assignValue(TreapNode *node, ValueType value);

public:

    TreapNode();

    TreapNode(ValueType value, TreapNode *leftChild = nullptr,
              TreapNode *rightChild = nullptr);

    ~TreapNode();

    void update();

    void push();

    void addOnSubtree(ValueType value);

    void assignOnSubtree(ValueType value);

    void assignLeftChild(TreapNode *newLeftChild);

    void assignRightChild(TreapNode *newRightChild);

    ValueType getSubtreeSum();

    uint getPriority();

    int getLeftChildSize();

    TreapNode* getLeftChild();

    TreapNode* getRightChild();

};

#endif