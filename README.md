# DataStructure

Just another homework project.

This one provides an implementation of a data structure, that, 
given an array of __N__ elements, can do the following in _O(log n)_:

1. Find the sum of all elements on a segment __[l..r]__
2. Insert element __x__ on position __i__
3. Erase element on position __i__
4. Assign the value of __x__ to all elements on a segment __[l..r]__
5. Add the value of __x__ to all elements on a segment __[l..r]__
6. Perform __next_permutation__ on a segment __[l..r]__
7. Perform __prev_permutation__ on a segment __[l..r]__

## Building

Create project file with cmake and then build it with your favorite
build system. 

You can build the whole project with tests or just the library 
(the data\_structure target).

__MOST LIKELY YOU'LL HAVE TO REBUILD GOOGLE TEST
FOR YOUR SYSTEM AND EDIT CMakeLists.txt TO MATCH NEW FILES__
