#include "split_predicate.hpp"
#include "treap.hpp"

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