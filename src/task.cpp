#include <iostream>
#include <cstdio>
#include "typedefs.hpp"
#include "data_structure.hpp"

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
    using std::cin;
    using std::cout;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int initialSize;
    cin >> initialSize;

    ValueType value;
    DataStructure collection;
    for (int index = 0; index < initialSize; ++index) {
        cin >> value;
        collection.insert(value, index);
    }

    collection.printSegment(cout, 0, collection.getSize());
    cout << '\n';

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

        collection.printSegment(cout, 0, collection.getSize());
        cout << '\n';
    }

    return 0;
}