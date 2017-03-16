#include "treap.hpp"

#include <cstdlib>

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

bool TreapNode::checkMonotonous(const TreapNode *leftNode, ValueType value, const TreapNode *rightNode) const {
    if (leftNode && !leftNode->isMonotonous_ || rightNode && !rightNode->isMonotonous_)
        return false;

    ValueType leftmostValue = TreapNode::getLeftmostValue(leftNode, value_);
    ValueType leftValue = TreapNode::getRightmostValue(leftNode, value_);
    ValueType rightValue = TreapNode::getLeftmostValue(rightNode, value_);
    ValueType rightmostValue = TreapNode::getRightmostValue(rightNode, value_);

    return leftmostValue <= leftValue && leftValue <= value && value <= rightValue && rightValue <= rightmostValue ||
           leftmostValue >= leftValue && leftValue >= value && value >= rightValue && rightValue >= rightmostValue;
}

ValueType TreapNode::getSum(const TreapNode *node) {
    return node ? node->sum_ : 0;
}

int TreapNode::getSize(const TreapNode *node) {
    return node ? node->size_ : 0;
}

ValueType TreapNode::getLeftmostValue(const TreapNode *node, ValueType defaultValue) {
    return node ? node->leftmostValue_ : defaultValue;
}

ValueType TreapNode::getRightmostValue(const TreapNode *node, ValueType defaultValue) {
    return node ? node->rightmostValue_ : defaultValue;
}

bool TreapNode::isAscending(const TreapNode *node, bool defaultValue) {
    return node ? node->isMonotonous_ && node->leftmostValue_ <= node->rightmostValue_ : defaultValue;
}

bool TreapNode::isDescending(const TreapNode *node, bool defaultValue) {
    return node ? node->isMonotonous_ && node->leftmostValue_ >= node->rightmostValue_ : defaultValue;
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

    leftmostValue_ = TreapNode::getLeftmostValue(leftChild_, value_);
    rightmostValue_ = TreapNode::getRightmostValue(rightChild_, value_);

    isMonotonous_ = checkMonotonous(leftChild_, value_, rightChild_);
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

ValueType TreapNode::getValue() const {
    return value_;
}

uint TreapNode::getPriority() const {
    return priority_;
}

TreapNode* TreapNode::getLeftChild() {
    return leftChild_;
}

const TreapNode* TreapNode::getLeftChild() const {
    return leftChild_;
}

TreapNode* TreapNode::getRightChild() {
    return rightChild_;
}

const TreapNode* TreapNode::getRightChild() const {
    return rightChild_;
}