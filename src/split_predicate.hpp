#pragma once

#ifndef DATASTRUCTURE_SPLIT_PREDICATE_HPP
#define DATASTRUCTURE_SPLIT_PREDICATE_HPP

#include "typedefs.hpp"

class TreapNode;

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

public:

    virtual bool operator()(const TreapNode &node) override;

    ExplicitKeySplit(ValueType key);

};

/*class AscendingSplit : public SplitPredicate {
public:

    virtual bool operator()(const TreapNode &node) override;

};

class DescendingSplit : public SplitPredicate {

    virtual bool operator()(const TreapNode &node) override;

};*/

#endif