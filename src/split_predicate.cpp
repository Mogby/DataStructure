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
    return node.getValue() > key_;
}

ExplicitKeySplit::ExplicitKeySplit(ValueType key) : key_(key) {}

/*bool AscendingSplit::operator()(const TreapNode &node) {
    if (!TreapNode::isAscending(node.getRightChild(), true) ||
            node.getValue() > TreapNode::getLeftmostValue(node.getRightChild(), node.getValue())) {
        return false;
    }

    return TreapNode::isAscending(node.getLeftChild(), true) &&
            TreapNode::getRightmostValue(node.getLeftChild(), node.getValue()) <= node.getValue();
}

bool DescendingSplit::operator()(const TreapNode &node) {
    if (!TreapNode::isDescending(node.getRightChild(), true) ||
            node.getValue() < TreapNode::getLeftmostValue(node.getRightChild(), node.getValue())) {
        return false;
    }

    return TreapNode::isDescending(node.getLeftChild(), false) &&

}*/