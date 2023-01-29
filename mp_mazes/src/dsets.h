/* Your code here! */
#pragma once
#include <vector>

class DisjointSets {
  private:
    std::vector<int> _elements;
  public:
    void addelements(int num);
    int find(int elem);
    void setunion(int A, int B);
    int size(int elem);
};