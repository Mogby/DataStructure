#pragma once

#ifndef TREAP_HPP

#define TREAP_HPP

#include "typedefs.hpp"

class TreapNode {
private:

    ValueType value_;
    ValueType sum_;
    uint priority_;

    int size_;

    TreapNode *leftChild_, *rightChild_;

    ValueType getSum(TreapNode *node);

    int getSize(TreapNode *node);

public:

    TreapNode();

    TreapNode(ValueType value, TreapNode *leftChild = nullptr,
              TreapNode *rightChild = nullptr);

    ~TreapNode();

    void update();

    void assignLeftChild(TreapNode *newLeftChild);

    void assignRightChild(TreapNode *newRightChild);

    ValueType getValue();

    ValueType getSubtreeSum();

    uint getPriority();

    int getLeftChildSize();

    TreapNode* getLeftChild();

    TreapNode* getRightChild();

};

#endif