#include "treap.hpp"

#include <cstdlib>

ValueType TreapNode::getSum(TreapNode *node) {
    return node ? node->sum_ : 0;
}

int TreapNode::getSize(TreapNode *node) {
    return node ? node->size_ : 0;
}

void TreapNode::addValue(TreapNode *node, ValueType value) {
    if (node) {
        node->addOnSubtree(value);
    }
}

void TreapNode::assignValue(TreapNode *node, ValueType value) {
    if (node) {
        node->assignOnSubtree(value);
    }
}

TreapNode::TreapNode() : TreapNode(0) {}

TreapNode::TreapNode(ValueType value, TreapNode *leftChild,
                     TreapNode *rightChild) : value_(value),
        leftChild_(leftChild), rightChild_(rightChild) {
    priority_ = rand() * (RAND_MAX + 1) + rand();

    toAdd_ = 0;
    needAssign = false;

    update();
}

TreapNode::~TreapNode() {
    if (leftChild_)
        delete leftChild_;

    if (rightChild_)
        delete rightChild_;
}

void TreapNode::update() {
    sum_ = value_ + getSum(leftChild_) + getSum(rightChild_);
    size_ = 1 + getSize(leftChild_) + getSize(rightChild_);
}

void TreapNode::push() {
    if (needAssign) {
        assignValue(leftChild_, toAssign_);
        assignValue(rightChild_, toAssign_);
        needAssign = false;
    }
    if (toAdd_) {
        addValue(leftChild_, toAdd_);
        addValue(rightChild_, toAdd_);
        toAdd_ = 0;
    }
}

void TreapNode::addOnSubtree(ValueType value) {
    value_ += value;
    toAdd_ += value;
}

void TreapNode::assignOnSubtree(ValueType value) {
    value_ = value;
    toAssign_ = value;
    needAssign = true;
    toAdd_ = 0;
}

void TreapNode::assignLeftChild(TreapNode *newLeftChild) {
    leftChild_ = newLeftChild;
    update();
}

void TreapNode::assignRightChild(TreapNode *newRightChild) {
    rightChild_ = newRightChild;
    update();
}

ValueType TreapNode::getSubtreeSum() {
    return sum_;
}

uint TreapNode::getPriority() {
    return priority_;
}

int TreapNode::getLeftChildSize() {
    return getSize(leftChild_);
}

TreapNode* TreapNode::getLeftChild() {
    return leftChild_;
}

TreapNode* TreapNode::getRightChild() {
    return rightChild_;
}