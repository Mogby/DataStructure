#pragma once

#ifndef TREAP_HPP

#define TREAP_HPP

#include "typedefs.hpp"

class TreapNode {
private:

    ValueType value_;
    ValueType sum_;
    uint priority_;

    bool isMonotonous_;

    ValueType leftmostValue_;
    ValueType rightmostValue_;

    ValueType toAdd_;
    ValueType toAssign_;
    bool needAssign;

    int size_;

    TreapNode *leftChild_, *rightChild_;

    void addValue(TreapNode *node, ValueType value);

    void assignValue(TreapNode *node, ValueType value);

    bool checkMonotonous(const TreapNode *leftNode, ValueType value, const TreapNode *rightNode) const;

public:

    static ValueType getSum(const TreapNode *node);

    static int getSize(const TreapNode *node);

    static ValueType getLeftmostValue(const TreapNode *node, ValueType defaultValue);

    static ValueType getRightmostValue(const TreapNode *node, ValueType defaultValue);

    static bool isAscending(const TreapNode *node, bool defaultValue);

    static bool isDescending(const TreapNode *node, bool defaultValue);

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

    ValueType getValue() const;

    uint getPriority() const;

    TreapNode* getLeftChild();

    const TreapNode* getLeftChild() const;

    TreapNode* getRightChild();

    const TreapNode* getRightChild() const;
};

#endif