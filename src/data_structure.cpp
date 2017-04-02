#include "data_structure.hpp"

#include "treap.hpp"
#include "split_predicate.hpp"

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

DataStructure::NodePair DataStructure::split(TreapNode *treap, SplitPredicate &predicate) {
    if (!treap) {
        return NodePair();
    }

    treap->push();

    NodePair cut;
    if (predicate(*treap)) {
        predicate.goLeft(*treap);
        cut = split(treap->getLeftChild(), predicate);
        treap->assignLeftChild(cut.right);
        return NodePair(cut.left, treap);
    } else {
        predicate.goRight(*treap);
        cut = split(treap->getRightChild(), predicate);
        treap->assignRightChild(cut.left);
        return NodePair(treap, cut.right);
    }
}

DataStructure::NodePair DataStructure::split(TreapNode *treap, SplitPredicate &&predicate) {
    return split(treap, predicate);
}

DataStructure::NodeTriplet DataStructure::splitTwice(TreapNode *treap, int leftIndex, int rightIndex) {
    NodePair firstCut = split(treap, ImplicitKeySplit(rightIndex));
    NodePair secondCut = split(firstCut.left, ImplicitKeySplit(leftIndex - 1));

    return NodeTriplet(secondCut.left, secondCut.right, firstCut.right);
}

void DataStructure::movePermutationOnSegment(int leftBound, int rightBound, bool nextPermutation) {
    NodeTriplet segments = splitTwice(treap_, leftBound, rightBound);

    if (!TreapNode::isMonotonous(segments.middle, true, !nextPermutation)) {
        NodePair segmentParts = split(segments.middle, MonotonousSplit(!nextPermutation));
        NodePair swapFrom = split(segmentParts.left, ImplicitKeySplit(TreapNode::getSize(segmentParts.left) - 2));
        NodePair swapTo = split(segmentParts.right,
                                ExplicitKeySplit(swapFrom.right->getValue() + (nextPermutation ? 1 : -1),
                                                 !nextPermutation));
        NodePair newElement = split(swapTo.left, ImplicitKeySplit(TreapNode::getSize(swapTo.left) - 2));

        segments.middle = merge(newElement.left, swapFrom.right, swapTo.right);
        segments.middle->reverseSubtree();
        segments.middle = merge(swapFrom.left, newElement.right, segments.middle);
    } else {
        segments.middle->reverseSubtree();
    }

    treap_ = merge(segments.left, segments.middle, segments.right);
}

DataStructure::DataStructure() : treap_(nullptr) {}

DataStructure::~DataStructure() {
    delete treap_;
}

void DataStructure::insert(ValueType value, int index) {
    TreapNode *newNode = new TreapNode(value);

    NodePair cut = split(treap_, ImplicitKeySplit(index - 1));
    treap_ = merge(cut.left, newNode, cut.right);
}

void DataStructure::addOnSegment(ValueType value, int leftBound, int rightBound) {
    NodeTriplet segments = splitTwice(treap_, leftBound, rightBound);

    segments.middle->addOnSubtree(value);

    treap_ = merge(segments.left, segments.middle, segments.right);
}

void DataStructure::assignOnSegment(ValueType value, int leftBound, int rightBound) {
    NodeTriplet segments = splitTwice(treap_, leftBound, rightBound);

    segments.middle->assignOnSubtree(value);

    treap_ = merge(segments.left, segments.middle, segments.right);
}

void DataStructure::reverseOnSegment(int leftBound, int rightBound) {
    NodeTriplet segments = splitTwice(treap_, leftBound, rightBound);

    segments.middle->reverseSubtree();

    treap_ = merge(segments.left, segments.middle, segments.right);
}

void DataStructure::nextPermutationOnSegment(int leftBound, int rightBound) {
    movePermutationOnSegment(leftBound, rightBound, true);
}

void DataStructure::previousPermutationOnSegment(int leftBound, int rightBound) {
    movePermutationOnSegment(leftBound, rightBound, false);
}

void printNode(TreapNode *node) {
    if (node) {
        std::cout << *node << "; ";
    } else {
        std::cout << "---; ";
    }
}

void DataStructure::erase(int index) {
    NodeTriplet segments = splitTwice(treap_, index, index);

    delete segments.middle;

    treap_ = merge(segments.left, segments.right);
}

int DataStructure::getSize() const {
    return TreapNode::getSize(treap_);
}

ValueType DataStructure::getSum(int leftBound, int rightBound) {
    NodeTriplet segments = splitTwice(treap_, leftBound, rightBound);

    ValueType result = TreapNode::getSum(segments.middle);

    treap_ = merge(segments.left, segments.middle, segments.right);

    return result;
}

void DataStructure::printSegment(std::ostream &output, int leftBound, int rightBound) {
    NodeTriplet segments = splitTwice(treap_, leftBound, rightBound);

    output << *segments.middle;

    treap_ = merge(segments.left, segments.middle, segments.right);
}