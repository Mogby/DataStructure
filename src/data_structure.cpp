#include "data_structure.hpp"

#include "treap.hpp"

TreapNode* DataStructure::merge(TreapNode *leftNode, TreapNode *rightNode) {
    if (!leftNode)
        return rightNode;

    if (!rightNode)
        return leftNode;

    if (leftNode->getPriority() > rightNode->getPriority()) {
        leftNode->assignRightChild(merge(leftNode->getRightChild(),
                                         rightNode));
        return leftNode;
    } else {
        rightNode->assignLeftChild(merge(leftNode,
                                         rightNode->getLeftChild()));
        return rightNode;
    }
}

DataStructure::NodePair DataStructure::split(TreapNode *treap, int index) {
    if (!treap) {
        return NodePair();
    }

    NodePair cut;
    if (treap->getLeftChildSize() > index) {
        cut = split(treap->getLeftChild(), index);
        treap->assignLeftChild(cut.right);
        return NodePair(cut.left, treap);
    } else {
        cut = split(treap->getRightChild(), index - treap->getLeftChildSize() - 1);
        treap->assignRightChild(cut.left);
        return NodePair(treap, cut.right);
    }
}

DataStructure::DataStructure() : treap_(nullptr) {}

DataStructure::~DataStructure() {
    delete treap_;
}

void DataStructure::add(ValueType value, int index) {
    TreapNode *newNode = new TreapNode(value);

    NodePair cut = split(treap_, index - 1);
    treap_ = merge(cut.left, merge(newNode, cut.right));
}

void DataStructure::remove(int index) {
    NodePair firstCut = split(treap_, index);
    NodePair secondCut = split(firstCut.left, index - 1);

    delete secondCut.right;

    treap_ = merge(secondCut.left, firstCut.right);
}

ValueType DataStructure::getSum(int leftBound, int rightBound) {
    NodePair firstCut = split(treap_, rightBound);
    NodePair secondCut = split(firstCut.left, leftBound - 1);

    ValueType result = secondCut.right ? secondCut.right->getSubtreeSum() : 0;

    treap_ = merge(secondCut.left, merge(secondCut.right, firstCut.right));

    return result;
}