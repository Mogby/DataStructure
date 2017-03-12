#include "treap.hpp"

#include <cstdlib>

ValueType TreapNode::getSum(TreapNode *node) {
    return node ? node->sum_ : 0;
}

int TreapNode::getSize(TreapNode *node) {
    return node ? node->size_ : 0;
}

TreapNode::TreapNode() : TreapNode(0) {}

TreapNode::TreapNode(ValueType value, TreapNode *leftChild,
                     TreapNode *rightChild) : value_(value),
        leftChild_(leftChild), rightChild_(rightChild) {
    priority_ = rand() * (RAND_MAX + 1) + rand();

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

void TreapNode::assignLeftChild(TreapNode *newLeftChild) {
    leftChild_ = newLeftChild;
    update();
}

void TreapNode::assignRightChild(TreapNode *newRightChild) {
    rightChild_ = newRightChild;
    update();
}

ValueType TreapNode::getValue() {
    return value_;
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