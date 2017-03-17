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
    return node.getValue() != key_ && (node.getValue() > key_ == ascendingTree_);
}

ExplicitKeySplit::ExplicitKeySplit(ValueType key, bool ascendingTree) : key_(key), ascendingTree_(ascendingTree) {}

bool AscendingSplit::operator()(const TreapNode &node) {
    if (alwaysFalse_) {
        return false;
    }

    if (!TreapNode::isAscending(node.getRightChild(), true) ||
        node.getValue() > TreapNode::getLeftmostValue(node.getRightChild(), node.getValue())) {
        return false;
    }

    if (TreapNode::getLeftmostValue(node.getLeftChild(), node.getValue()) > node.getValue()) {
        alwaysFalse_ = true;
    }

    return true;
}

bool DescendingSplit::operator()(const TreapNode &node) {
    if (alwaysFalse_) {
        return false;
    }

    if (!TreapNode::isDescending(node.getRightChild(), true) ||
        node.getValue() < TreapNode::getLeftmostValue(node.getRightChild(), node.getValue())) {
        return false;
    }

    if (TreapNode::getRightmostValue(node.getLeftChild(), node.getValue()) < node.getValue()) {
        alwaysFalse_ = true;
    }

    return true;

}