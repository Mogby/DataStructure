#include "treap.hpp"

#include <utility>

bool Utility::checkUnstrictOrder(ValueType value1, ValueType value2, bool ascendingOrder) {
    return value1 == value2 || value1 < value2 == ascendingOrder;
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

void TreapNode::reverse(TreapNode *node) {
    if (node) {
        node->reverseSubtree();
    }
}

bool TreapNode::checkMonotonous(const TreapNode *leftNode, ValueType value, const TreapNode *rightNode) const {
    if (leftNode && !leftNode->isMonotonous_ || rightNode && !rightNode->isMonotonous_)
        return false;

    ValueType leftmostValue = TreapNode::getLeftmostValue(leftNode, value);
    ValueType leftValue = TreapNode::getRightmostValue(leftNode, value);
    ValueType rightValue = TreapNode::getLeftmostValue(rightNode, value);
    ValueType rightmostValue = TreapNode::getRightmostValue(rightNode, value);

    bool checkAscending = true;
    for (int testsCount = 0; testsCount < 2; ++testsCount) {
        if (Utility::checkUnstrictOrder(leftmostValue, leftValue, checkAscending) &&
                Utility::checkUnstrictOrder(leftValue, value, checkAscending) &&
                Utility::checkUnstrictOrder(value, rightValue, checkAscending) &&
                Utility::checkUnstrictOrder(rightValue, rightmostValue, checkAscending)) {
            return true;
        }
        checkAscending = !checkAscending;
    }

    return false;
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

bool TreapNode::isMonotonous(const TreapNode *node, bool defaultValue, bool checkAscending) {
    return node ? node->isMonotonous_ &&
            Utility::checkUnstrictOrder(node->leftmostValue_,
                                        node->rightmostValue_,
                                        checkAscending) : defaultValue;
}

TreapNode::TreapNode() : TreapNode(0) {}

TreapNode::TreapNode(ValueType value, TreapNode *leftChild,
                     TreapNode *rightChild) : value_(value),
        leftChild_(leftChild), rightChild_(rightChild) {
    priority_ = rand() * (RAND_MAX + 1) + rand();

    toAdd_ = 0;
    needAssign = false;
    needReverse = false;

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
    if (needReverse) {
        reverse(leftChild_);
        reverse(rightChild_);
        needReverse = false;
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

void TreapNode::reverseSubtree() {
    needReverse = !needReverse;
    std::swap(leftChild_, rightChild_);
    update();
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

std::ostream& operator<<(std::ostream &output, const TreapNode &node) {
    if (node.getLeftChild()) {
        output << *(node.getLeftChild());
    }
    output << node.getValue() << ' ';
    if (node.getRightChild()) {
        output << *(node.getRightChild());
    }
    return output;
}