/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num) {
    for(int i = 0; i < num; i++) {
        _elements.push_back(-1);
    }
    return;
}

int DisjointSets::find(int elem) {
    if(_elements[elem] < 0) {
        return elem;
    } else {
        int findRoot = find(_elements[elem]);
        _elements[elem] = findRoot;
        return findRoot;
    }
    return 0;
}

void DisjointSets::setunion(int A, int B) {
    int rootA = find(A);
    int rootB = find(B);
    if(rootA == rootB) {
        return;
    }
    int sizeA = _elements[rootA];
    int sizeB = _elements[rootB];
    int newUnionSize = sizeA + sizeB;
    if(sizeA <= sizeB) {
        _elements[rootB] = rootA;
        _elements[rootA] = newUnionSize;
    } else {
        _elements[rootA] = rootB;
        _elements[rootB] = newUnionSize;
    }
    return;
}

int DisjointSets::size(int elem) {
    int findRoot = find(elem);
    return (_elements[findRoot] * -1);
}