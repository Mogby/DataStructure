#pragma once

#ifndef TESTS_HPP

#define TESTS_HPP

#include <cstdlib>
#include <vector>

#include <gtest/gtest.h>

#include "typedefs.hpp"
#include "data_structure.hpp"

const uint TEST_SIZE = 1000;

class DataStructureTest : public ::testing::Test {
protected:

    DataStructure dataStructure;

    std::vector<ValueType> values;

};

TEST_F(DataStructureTest, AddTest) {
    srand(1337);

    for (int count = 0; count < TEST_SIZE; ++count) {
        dataStructure.add(rand(), rand() % (count + 1));
    }
}

TEST_F(DataStructureTest, GetSumTest) {
    srand(0451);

    ValueType sum = 0;
    ValueType newElement;
    for (int count = 0; count < TEST_SIZE; ++count) {
        newElement = rand();
        sum += newElement;
        dataStructure.add(newElement, count);
    }

    EXPECT_EQ(sum, dataStructure.getSum(0, TEST_SIZE));
}

TEST_F(DataStructureTest, RemoveTest) {
    srand(0511);

    for (int count = 0; count < TEST_SIZE; ++count) {
        dataStructure.add(rand(), count);
    }

    for (int count = TEST_SIZE; count > 0; --count) {
        dataStructure.remove(rand() % count);
    }
}

TEST_F(DataStructureTest, AddCorrectness) {
    srand(420);

    ValueType newElement;
    int insertIndex;
    for (int count = 0; count < TEST_SIZE; ++count) {
        newElement = rand();
        insertIndex = rand() % (count + 1);

        dataStructure.add(newElement, insertIndex);
        values.insert(values.begin() + insertIndex, newElement);
    }

    for (int index = 0; index < TEST_SIZE; ++index) {
        EXPECT_EQ(values[index], dataStructure.getSum(index, index));
    }
}

#endif