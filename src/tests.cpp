#include <cstdlib>
#include <vector>
#include <utility>

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

TEST_F(DataStructureTest, AssignOnSegmentTest) {
    srand(3);

    for (int count = 0; count < TEST_SIZE; ++count) {
        dataStructure.add(0, 0);
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
        dataStructure.add(0, 0);
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
        dataStructure.add(0, 0);
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

TEST_F(DataStructureTest, RemoveCorrectness) {
    srand(255);

    ValueType newElement;
    int insertIndex;
    for (int count = 0; count < TEST_SIZE; ++count) {
        newElement = rand();
        insertIndex = rand() % (count + 1);

        dataStructure.add(newElement, insertIndex);
        values.insert(values.begin() + insertIndex, newElement);
    }

    int eraseIndex;
    for (int count = TEST_SIZE - 1; count > 0; --count) {
        eraseIndex = rand() % count;
        values.erase(values.begin() + eraseIndex);
        dataStructure.remove(eraseIndex);

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
        dataStructure.add(newElement, count);
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
        dataStructure.add(0, 0);
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
        dataStructure.add(0, 0);
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
        dataStructure.add(newElement, count);
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

TEST_F(DataStructureTest, CombinedTest) {
    srand(73);

    ValueType newValue;
    for (int count = 0; count < TEST_SIZE; ++count) {
        newValue = rand();
        dataStructure.add(newValue, count);
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