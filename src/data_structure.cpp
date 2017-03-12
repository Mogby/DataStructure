#include "data_structure.hpp"

#include "treap.hpp"

TreapNode* DataStructure::merge(TreapNode *leftNode, TreapNode *rightNode) {
    if (!leftNode)
        return rightNode;

    if (!rightNode)
        return leftNode;

    leftNode->push();
    rightNode->push();

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

TreapNode* DataStructure::merge(TreapNode *leftNode, TreapNode *middleNode, TreapNode *rightNode) {
    return merge(leftNode, merge(middleNode, rightNode));
}

DataStructure::NodePair DataStructure::split(TreapNode *treap, int index) {
    if (!treap) {
        return NodePair();
    }

    treap->push();

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

DataStructure::NodeTriplet DataStructure::split(TreapNode *treap, int leftIndex, int rightIndex) {
    NodePair firstCut = split(treap, rightIndex);
    NodePair secondCut = split(firstCut.left, leftIndex - 1);

    return NodeTriplet(secondCut.left, secondCut.right, firstCut.right);
}

DataStructure::DataStructure() : treap_(nullptr) {}

DataStructure::~DataStructure() {
    delete treap_;
}

void DataStructure::add(ValueType value, int index) {
    TreapNode *newNode = new TreapNode(value);

    NodePair cut = split(treap_, index - 1);
    treap_ = merge(cut.left, newNode, cut.right);
}

void DataStructure::addOnSegment(ValueType value, int leftBound, int rightBound) {
    NodeTriplet segments = split(treap_, leftBound, rightBound);

    segments.middle->addOnSubtree(value);

    treap_ = merge(segments.left, segments.middle, segments.right);
}

void DataStructure::assignOnSegment(ValueType value, int leftBound, int rightBound) {
    NodeTriplet segments = split(treap_, leftBound, rightBound);

    segments.middle->assignOnSubtree(value);

    treap_ = merge(segments.left, segments.middle, segments.right);
}

void DataStructure::remove(int index) {
    NodeTriplet segments = split(treap_, index, index);

    delete segments.middle;

    treap_ = merge(segments.left, segments.right);
}

ValueType DataStructure::getSum(int leftBound, int rightBound) {
    NodeTriplet segments = split(treap_, leftBound, rightBound);

    ValueType result = segments.middle ? segments.middle->getSubtreeSum() : 0;

    treap_ = merge(segments.left, segments.middle, segments.right);

    return result;
}