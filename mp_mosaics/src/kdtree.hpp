/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(curDim < 0 || curDim > Dim) {
      return false;
    }
    bool isSmaller = false;
    if(first[curDim] < second[curDim]) {
      isSmaller = true;
    } else if(first[curDim] == second[curDim]) {
      isSmaller = (first < second);
    }
    return isSmaller;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    bool isCloser = false;
    double curDist = distanceHelper(target, currentBest);
    double potDist = distanceHelper(target, potential);
    if(potDist < curDist) {
      isCloser = true;
    } else if(potDist == curDist) {
      isCloser = (potential < currentBest);
    }
    return isCloser;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if(!newPoints.empty()) {
      for(size_t i = 0; i < newPoints.size(); i++) {
        allPoints_.push_back(newPoints[i]);
      }
      root = helperConstructor(0, 0, allPoints_.size() - 1);
    } else {
      root = NULL;
    }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::helperConstructor(int dimension, int left, int right) {
  if(right < left) {
    return NULL;
  }
  if(left < 0 || right < 0 || allPoints_.empty()) {
    return NULL;
  }
  int median = ((left + right) / 2);
  quickSelectHelper(dimension, left, right, median);
  KDTreeNode* subroot = new KDTreeNode(allPoints_[median]);
  int nextDim = (dimension + 1) % Dim;
  subroot->left = helperConstructor(nextDim, left, median - 1);
  subroot->right = helperConstructor(nextDim, median + 1, right);
  return subroot;
}

template <int Dim>
void KDTree<Dim>::quickSelectHelper(int dimension, int left, int right, int k) {
  if(right < left) {
    return;
  }
  if(left < 0 || right < 0 || allPoints_.empty()) {
    return;
  }
  int pivotIndex = quickSelectPartition(dimension, left, right, k);
  if(k == pivotIndex) {
    return;
  } else if(k < pivotIndex) {
    quickSelectHelper(dimension, left, pivotIndex - 1, k);
  } else {
    quickSelectHelper(dimension, pivotIndex + 1, right, k);
  }
  return;
}

template <int Dim>
int KDTree<Dim>::quickSelectPartition(int dimension, int left, int right, int pivotIndex) {
  Point<Dim> pivotPoint = allPoints_[pivotIndex];
  Point<Dim> tempPoint = allPoints_[right];
  allPoints_[pivotIndex] = tempPoint;
  allPoints_[right] = pivotPoint;
  int holdIndex = left;
  for(int i = left; i < right; i++) {
    if(smallerDimVal(allPoints_[i], pivotPoint, dimension)) {
      tempPoint = allPoints_[holdIndex];
      allPoints_[holdIndex] = allPoints_[i];
      allPoints_[i] = tempPoint;
      holdIndex++;
    }
  }
  tempPoint = allPoints_[holdIndex];
  allPoints_[holdIndex] = allPoints_[right];
  allPoints_[right] = tempPoint;
  return holdIndex;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy(this->root, other.root);
  this->size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this != NULL) {
    clear(this->root);
  }
  copy(this->root, rhs.root);
  this->size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(this->root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestHelper(root, root->point, query, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestHelper(KDTreeNode* subroot, Point<Dim> currBest, const Point<Dim> target, int dimension) const{
  bool flag = false;
  if(subroot->left == NULL && subroot->right == NULL) {
    return subroot->point;
  }
  int nextDim = (dimension + 1) % Dim;
  if(smallerDimVal(target, subroot->point, dimension)) {
    if(subroot->left) {
      currBest = findNearestHelper(subroot->left, currBest, target, nextDim);
      flag = true;
    } else {
      currBest = findNearestHelper(subroot->right, currBest, target, nextDim);
    }
  } else {
    if(subroot->right) {
      currBest = findNearestHelper(subroot->right, currBest, target, nextDim);
    } else {
      currBest = findNearestHelper(subroot->left, currBest, target, nextDim);
      flag = true;
    }
  }

  if(shouldReplace(target, currBest, subroot->point)) {
    currBest = subroot->point;
  }
  double radius = distanceHelper(target, currBest);
  double partSplitDist = ((subroot->point)[dimension] - target[dimension]);
  double splitDist = (partSplitDist * partSplitDist);
  if(splitDist <= radius) {
    KDTreeNode* extraCheckNode = flag ? subroot->right : subroot->left;
    if(extraCheckNode) {
      Point<Dim> nearest = findNearestHelper(extraCheckNode, currBest, target, nextDim);
      if(shouldReplace(target, currBest, nearest)) {
        currBest = nearest;
      }
    }
  }
  return currBest;
}

template <int Dim>
double KDTree<Dim>::distanceHelper(const Point<Dim> &first, const Point<Dim> &second) const {
  double currDist = 0.0;
  for(int i = 0; i < Dim; i++) {
    double partDist = (first[i] - second[i]);
    currDist += (partDist * partDist);
  }
  return currDist;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* subroot) {
  if(subroot == NULL) {
    return;
  }
  if(subroot->right != NULL) {
    clear(subroot->right);
  }
  if(subroot->left != NULL) {
    clear(subroot->left);
  }
  delete subroot;
  subroot = NULL;
  return;
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode* subroot, KDTreeNode* otherSubroot) {
  subroot = new KDTreeNode();
  subroot->point = otherSubroot->point;
  copy(subroot->right, otherSubroot->right);
  copy(subroot->left, otherSubroot->left);
}