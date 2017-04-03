#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <utility>

typedef long long int ValueType;

typedef unsigned int uint;

class TreapNode;

class SplitPredicate;

class DataStructure {
private:

    struct NodePair {

        TreapNode *left;
        TreapNode *right;

        NodePair(TreapNode *leftNode = nullptr, TreapNode *rightNode = nullptr) :
                left(leftNode), right(rightNode) {}

    };

    struct NodeTriplet {
        TreapNode *left;
        TreapNode *middle;
        TreapNode *right;

        NodeTriplet(TreapNode *leftNode = nullptr, TreapNode *middleNode = nullptr,
                    TreapNode *rightNode = nullptr) : left(leftNode), middle(middleNode), right(rightNode) {}
    };

    TreapNode *treap_;

    TreapNode* merge(TreapNode *leftNode, TreapNode *rightNode);

    TreapNode* merge(TreapNode *leftNode, TreapNode *middleNode, TreapNode *rightNode);

    NodePair split(TreapNode *treap, SplitPredicate &predicate);

    NodePair split(TreapNode *treap, SplitPredicate &&predicate);

    NodeTriplet splitTwice(TreapNode *treap, int leftIndex, int rightIndex);

    void movePermutationOnSegment(int leftBound, int rightBound, bool nextPermutation);

public:

    DataStructure();

    ~DataStructure();

    void insert(ValueType value, int index);

    void addOnSegment(ValueType value, int leftBound, int rightBound);

    void assignOnSegment(ValueType value, int leftBound, int rightBound);

    void reverseOnSegment(int leftBound, int rightBound);

    void nextPermutationOnSegment(int leftBound, int rightBound);

    void previousPermutationOnSegment(int leftBound, int rightBound);

    void erase(int index);

    int getSize() const;

    ValueType getSum(int leftBound, int rightBound);

    void printSegment(std::ostream &output, int leftBound, int rightBound);
};

namespace Utility {

    bool checkUnstrictOrder(ValueType value1, ValueType value2, bool ascendingOrder);

}

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
    bool needReverse;

    int size_;

    TreapNode *leftChild_, *rightChild_;

    void addValue(TreapNode *node, ValueType value);

    void assignValue(TreapNode *node, ValueType value);

    void reverse(TreapNode *node);

    bool checkMonotonous(const TreapNode *leftNode, ValueType value, const TreapNode *rightNode) const;

public:

    static ValueType getSum(const TreapNode *node);

    static int getSize(const TreapNode *node);

    static ValueType getLeftmostValue(const TreapNode *node, ValueType defaultValue);

    static ValueType getRightmostValue(const TreapNode *node, ValueType defaultValue);

    static bool isMonotonous(const TreapNode *node, bool defaultValue, bool checkAscending);

    TreapNode();

    TreapNode(ValueType value, TreapNode *leftChild = nullptr,
              TreapNode *rightChild = nullptr);

    ~TreapNode();

    void update();

    void push();

    void addOnSubtree(ValueType value);

    void assignOnSubtree(ValueType value);

    void reverseSubtree();

    void assignLeftChild(TreapNode *newLeftChild);

    void assignRightChild(TreapNode *newRightChild);

    ValueType getValue() const;

    uint getPriority() const;

    TreapNode* getLeftChild();

    const TreapNode* getLeftChild() const;

    TreapNode* getRightChild();

    const TreapNode* getRightChild() const;
};

std::ostream& operator<<(std::ostream &output, const TreapNode &node);

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
    sum_ += value * size_;
    leftmostValue_ += value;
    rightmostValue_ += value;

    toAdd_ += value;
}

void TreapNode::assignOnSubtree(ValueType value) {
    value_ = value;
    sum_ = value * size_;
    leftmostValue_ = value;
    rightmostValue_ = value;

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

class SplitPredicate {
public:

    virtual bool operator()(const TreapNode &node) = 0;

    virtual void goLeft(const TreapNode &node) {};

    virtual void goRight(const TreapNode &node) {};

};

class ImplicitKeySplit : public SplitPredicate {
private:

    int key_;

public:

    virtual bool operator()(const TreapNode &node) override;

    virtual void goRight(const TreapNode &node) override;

    ImplicitKeySplit(int key);

};

class ExplicitKeySplit : public SplitPredicate {
private:

    ValueType key_;

    bool ascendingTree_;

public:

    virtual bool operator()(const TreapNode &node) override;

    ExplicitKeySplit(ValueType key, bool ascendingTree);

};

class MonotonousSplit : public SplitPredicate {
private:

    bool ascendingSplit_;
    bool alwaysFalse_;

public:

    MonotonousSplit(bool ascendingSplit) : ascendingSplit_(ascendingSplit), alwaysFalse_(false) {}

    virtual bool operator()(const TreapNode &node) override;

};

bool ImplicitKeySplit::operator()(const TreapNode &node) {
    return TreapNode::getSize(node.getLeftChild()) > key_;
}

void ImplicitKeySplit::goRight(const TreapNode &node) {
    key_ -= TreapNode::getSize(node.getLeftChild()) + 1;
}

ImplicitKeySplit::ImplicitKeySplit(int key) : key_(key) {}

bool ExplicitKeySplit::operator()(const TreapNode &node) {
    return !Utility::checkUnstrictOrder(node.getValue(), key_, ascendingTree_);
}

ExplicitKeySplit::ExplicitKeySplit(ValueType key, bool ascendingTree) : key_(key), ascendingTree_(ascendingTree) {}

bool MonotonousSplit::operator()(const TreapNode &node) {
    if (alwaysFalse_) {
        return false;
    }

    if (!TreapNode::isMonotonous(node.getRightChild(), true, ascendingSplit_) ||
        !Utility::checkUnstrictOrder(node.getValue(),
                                     TreapNode::getLeftmostValue(node.getRightChild(), node.getValue()),
                                     ascendingSplit_)) {
        return false;
    }

    if (!Utility::checkUnstrictOrder(TreapNode::getRightmostValue(node.getLeftChild(), node.getValue()),
                                     node.getValue(), ascendingSplit_)) {
        alwaysFalse_ = true;
    }

    return true;
}

TreapNode* DataStructure::merge(TreapNode *leftNode, TreapNode *rightNode) {
    if (leftNode) {
        leftNode->push();
    }
    if (rightNode) {
        rightNode->push();
    }

    if (!leftNode)
        return rightNode;

    if (!rightNode)
        return leftNode;;

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

enum EQueryType {
    QT_SUM = 1,
    QT_INSERT,
    QT_ERASE,
    QT_ASSIGN,
    QT_ADD,
    QT_NEXT_PERMUTATION,
    QT_PREVIOUS_PERMUTATION
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    using std::cin;
    using std::cout;

    int initialSize;
    cin >> initialSize;

    ValueType value;
    DataStructure collection;
    for (int index = 0; index < initialSize; ++index) {
        cin >> value;
        collection.insert(value, index);
    }

    int queryId;
    EQueryType queryType;
    int leftBound, rightBound;
    int position;

    int queriesNumber;
    cin >> queriesNumber;
    while (queriesNumber--) {
        cin >> queryId;
        queryType = static_cast<EQueryType>(queryId);

        switch (queryType) {
            case QT_SUM:

                cin >> leftBound >> rightBound;
                cout << collection.getSum(leftBound, rightBound) << '\n';
                break;

            case QT_INSERT:

                cin >> value >> position;
                collection.insert(value, position);
                break;

            case QT_ERASE:

                cin >> position;
                collection.erase(position);
                break;

            case QT_ASSIGN:

                cin >> value >> leftBound >> rightBound;
                collection.assignOnSegment(value, leftBound, rightBound);
                break;

            case QT_ADD:

                cin >> value >> leftBound >> rightBound;
                collection.addOnSegment(value, leftBound, rightBound);
                break;

            case QT_NEXT_PERMUTATION:

                cin >> leftBound >> rightBound;
                collection.nextPermutationOnSegment(leftBound, rightBound);
                break;

            case QT_PREVIOUS_PERMUTATION:

                cin >> leftBound >> rightBound;
                collection.previousPermutationOnSegment(leftBound, rightBound);
                break;

        }
    }

    collection.printSegment(cout, 0, collection.getSize() - 1);

    return 0;
}