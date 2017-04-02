#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

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
        dataStructure.insert(rand(), rand() % (count + 1));
    }
}

TEST_F(DataStructureTest, GetSumTest) {
    srand(0451);

    ValueType sum = 0;
    ValueType newElement;
    for (int count = 0; count < TEST_SIZE; ++count) {
        newElement = rand();
        sum += newElement;
        dataStructure.insert(newElement, count);
    }

    EXPECT_EQ(sum, dataStructure.getSum(0, TEST_SIZE));
}

TEST_F(DataStructureTest, RemoveTest) {
    srand(0511);

    for (int count = 0; count < TEST_SIZE; ++count) {
        dataStructure.insert(rand(), count);
    }

    for (int count = TEST_SIZE; count > 0; --count) {
        dataStructure.erase(rand() % count);
    }
}

TEST_F(DataStructureTest, AssignOnSegmentTest) {
    srand(3);

    for (int count = 0; count < TEST_SIZE; ++count) {
        dataStructure.insert(0, 0);
    }

    int leftBound, rightBound;
    for (int count = 0; count < TEST_SIZE; ++count) {
        leftBound = rand() % TEST_SIZE;
        rightBound = rand() % TEST_SIZE;

        if (leftBound > rightBound) {
            std::swap(leftBound, rightBound);
        }

        dataStructure.assignOnSegment(rand(), leftBound, rightBound);
    }
}

TEST_F(DataStructureTest, AddOnSegmentTest) {
    srand(73);

    for (int count = 0; count < TEST_SIZE; ++count) {
        dataStructure.insert(0, 0);
    }

    int leftBound, rightBound;
    for (int count = 0; count < TEST_SIZE; ++count) {
        leftBound = rand() % TEST_SIZE;
        rightBound = rand() % TEST_SIZE;

        if (leftBound > rightBound) {
            std::swap(leftBound, rightBound);
        }

        dataStructure.addOnSegment(rand() - RAND_MAX / 2, leftBound, rightBound);
    }
}

TEST_F(DataStructureTest, ReverseOnSegmentTest) {
    srand(12509165);

    for (int count = 0; count < TEST_SIZE; ++count) {
        dataStructure.insert(0, 0);
    }

    int leftBound, rightBound;
    for (int count = 0; count < TEST_SIZE; ++count) {
        leftBound = rand() % TEST_SIZE;
        rightBound = rand() % TEST_SIZE;

        if (leftBound > rightBound) {
            std::swap(leftBound, rightBound);
        }

        dataStructure.reverseOnSegment(leftBound, rightBound);
    }
}

TEST_F(DataStructureTest, MovePermutationOnSegmentTest) {
    srand(9000);

    for (int count = 0; count < TEST_SIZE; ++count) {
        dataStructure.insert(rand(), count);
    }

    bool nextPermutation;
    int leftBound, size, iterations;
    for (int count = 0; count < TEST_SIZE; ++count) {
        leftBound = rand() % (TEST_SIZE - 6);
        size = rand() % 6 + 1;
        iterations = rand() % 10 + 1;

        nextPermutation = rand() & 1;
        for (int iterationsCount = 0; iterationsCount < iterations; ++iterationsCount) {
            dataStructure.movePermutationOnSegment(leftBound, leftBound + size - 1, nextPermutation);
        }
    }
}

TEST_F(DataStructureTest, AddCorrectness) {
    srand(420);

    ValueType newElement;
    int insertIndex;
    for (int count = 0; count < TEST_SIZE; ++count) {
        newElement = rand();
        insertIndex = rand() % (count + 1);

        dataStructure.insert(newElement, insertIndex);
        values.insert(values.begin() + insertIndex, newElement);
    }

    for (int index = 0; index < TEST_SIZE; ++index) {
        EXPECT_EQ(values[index], dataStructure.getSum(index, index));
    }
}

TEST_F(DataStructureTest, RemoveCorrectness) {
    srand(255);

    ValueType newElement;
    int insertIndex;
    for (int count = 0; count < TEST_SIZE; ++count) {
        newElement = rand();
        insertIndex = rand() % (count + 1);

        dataStructure.insert(newElement, insertIndex);
        values.insert(values.begin() + insertIndex, newElement);
    }

    int eraseIndex;
    for (int count = TEST_SIZE - 1; count > 0; --count) {
        eraseIndex = rand() % count;
        values.erase(values.begin() + eraseIndex);
        dataStructure.erase(eraseIndex);

        for (int index = 0; index < count; ++index) {
            EXPECT_EQ(values[index], dataStructure.getSum(index, index));
        }
    }
}

TEST_F(DataStructureTest, GetSumCorrectness) {
    srand(42);

    ValueType newElement;
    for (int count = 0; count < TEST_SIZE; ++count) {
        newElement = rand();

        values.push_back(newElement);
        if (count) {
            values[values.size() - 1] += values[values.size() - 2];
        }
        dataStructure.insert(newElement, count);
    }

    for (int leftBound = 0; leftBound < TEST_SIZE; ++leftBound) {
        for (int rightBound = leftBound; rightBound < TEST_SIZE; ++rightBound) {
            EXPECT_EQ(values[rightBound] - (leftBound ? values[leftBound-1] : 0),
                      dataStructure.getSum(leftBound, rightBound));
        }
    }
}

TEST_F(DataStructureTest, AssignOnSegmentCorrectness) {
    srand(3);

    for (int count = 0; count < TEST_SIZE; ++count) {
        dataStructure.insert(0, 0);
        values.push_back(0);
    }

    ValueType newValue;
    int leftBound, rightBound;
    for (int count = 0; count < TEST_SIZE; ++count) {
        leftBound = rand() % TEST_SIZE;
        rightBound = rand() % TEST_SIZE;

        if (leftBound > rightBound) {
            std::swap(leftBound, rightBound);
        }

        newValue = rand();
        dataStructure.assignOnSegment(newValue, leftBound, rightBound);
        for (int index = leftBound; index <= rightBound; ++index) {
            values[index] = newValue;
        }
    }

    for (int index = 0; index < TEST_SIZE; ++index) {
        EXPECT_EQ(values[index], dataStructure.getSum(index, index));
    }
}

TEST_F(DataStructureTest, AddOnSegmentCorrectness) {
    srand(73);

    for (int count = 0; count < TEST_SIZE; ++count) {
        dataStructure.insert(0, 0);
        values.push_back(0);
    }

    ValueType deltaValue;
    int leftBound, rightBound;
    for (int count = 0; count < TEST_SIZE; ++count) {
        leftBound = rand() % TEST_SIZE;
        rightBound = rand() % TEST_SIZE;

        if (leftBound > rightBound) {
            std::swap(leftBound, rightBound);
        }

        deltaValue = rand() - RAND_MAX / 2;
        dataStructure.addOnSegment(deltaValue, leftBound, rightBound);
        for (int index = leftBound; index <= rightBound; ++index) {
            values[index] += deltaValue;
        }
    }

    for (int index = 0; index < TEST_SIZE; ++index) {
        EXPECT_EQ(values[index], dataStructure.getSum(index, index));
    }
}

TEST_F(DataStructureTest, ReverseOnSegmentCorrectness) {
    srand(12509165);

    ValueType newElement;
    for (int count = 0; count < TEST_SIZE; ++count) {
        newElement = rand();
        dataStructure.insert(newElement, count);
        values.push_back(newElement);
    }

    int leftBound, rightBound;
    for (int count = 0; count < TEST_SIZE; ++count) {
        leftBound = rand() % TEST_SIZE;
        rightBound = rand() % TEST_SIZE;

        if (leftBound > rightBound) {
            std::swap(leftBound, rightBound);
        }

        dataStructure.reverseOnSegment(leftBound, rightBound);
        for (int index = leftBound; index < (leftBound + rightBound + 1) / 2; ++index) {
            std::swap(values[index], values[rightBound + leftBound - index]);
        }
    }

    for (int index = 0; index < TEST_SIZE; ++index) {
        EXPECT_EQ(values[index], dataStructure.getSum(index, index));
    }
}

TEST_F(DataStructureTest, CombinedCorrectness) {
    srand(73);

    ValueType newValue;
    for (int count = 0; count < TEST_SIZE; ++count) {
        newValue = rand();
        dataStructure.insert(newValue, count);
        values.push_back(newValue);
    }

    ValueType deltaValue;
    int leftBound, rightBound, operationType;
    for (int count = 0; count < TEST_SIZE; ++count) {
        leftBound = rand() % TEST_SIZE;
        rightBound = rand() % TEST_SIZE;
        operationType = rand() % 3;

        if (leftBound > rightBound) {
            std::swap(leftBound, rightBound);
        }

        if (operationType == 1) {
            deltaValue = rand() - RAND_MAX / 2;
            dataStructure.addOnSegment(deltaValue, leftBound, rightBound);
            for (int index = leftBound; index <= rightBound; ++index) {
                values[index] += deltaValue;
            }
        } else if (operationType == 2) {
            newValue = rand();
            dataStructure.assignOnSegment(newValue, leftBound, rightBound);
            for (int index = leftBound; index <= rightBound; ++index) {
                values[index] = newValue;
            }
        } else {
            dataStructure.reverseOnSegment(leftBound, rightBound);
            for (int index = leftBound; index < (leftBound + rightBound + 1) / 2; ++index) {
                std::swap(values[index], values[rightBound + leftBound - index]);
            }
        }
    }

    for (int index = 0; index < TEST_SIZE; ++index) {
        EXPECT_EQ(values[index], dataStructure.getSum(index, index));
    }
}

TEST_F(DataStructureTest, MovePermutationCorrectness) {
    int testSize = 6;
    int permutationsCount = 720;

    for (ValueType count = 0; count < testSize; ++count) {
        dataStructure.insert(count, static_cast<uint>(count));
        values.push_back(count);
    }

    for (int iteration = 0; iteration < permutationsCount; ++iteration) {
        dataStructure.movePermutationOnSegment(0, testSize - 1, true);

        std::next_permutation(values.begin(), values.end());

        for (int index = 0; index < testSize; ++index) {
            EXPECT_EQ(values[index], dataStructure.getSum(index, index));
        }
    }

    for (int iteration = 0; iteration < permutationsCount; ++iteration) {
        dataStructure.movePermutationOnSegment(0, testSize - 1, false);

        std::prev_permutation(values.begin(), values.end());

        for (int index = 0; index < testSize; ++index) {
            EXPECT_EQ(values[index], dataStructure.getSum(index, index));
        }
    }
}