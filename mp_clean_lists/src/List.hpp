/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_, tail_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL, tail_);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * currNode = head_;
  while(currNode != NULL) {
    ListNode * holdNode = currNode;
    currNode = currNode->next;
    delete holdNode;
  }
  currNode = NULL;
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  newNode -> prev = tail_;
  newNode -> next = NULL;
  
  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  if (tail_ == NULL) {
    head_ = newNode;
  }
  tail_ = newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  
  ListNode * curr = start;
  if(curr == NULL) {
    return NULL;
  } else {
    for (int i = 0; i < splitPoint && curr != NULL; i++) {
      curr = curr->next;
    }

    if (curr != NULL) {
      if(curr->prev != NULL) {
        curr->prev->next = NULL;
      } else {
        curr->prev = NULL;
      }
    }
  }
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if(head_ == NULL || length_ < 3) {
    return;
  }
  int numIntervals = length_/3;
  // int currLen = 0;
  ListNode* curr = head_;
  head_ = curr->next;
  // ListNode * curr1 = head_;
  // ListNode * curr2 = head_->next;
  // ListNode * curr3 = head_->next->next;
  for(int i = 0; i < numIntervals; i++) {
    ListNode* holdOne = curr;
    ListNode* holdTwo = holdOne->next;
    ListNode* holdThree = holdTwo->next;
    ListNode* holdFour = holdThree->next;
    holdTwo->prev = holdOne->prev;
    if(holdOne->prev != NULL) {
      holdOne->prev->next = holdTwo;
    }
    holdOne->next = holdThree->next;
    if(holdFour != NULL) {
      holdFour->prev = holdOne;
    }
    holdOne->prev = holdThree;
    holdThree->next = holdOne;
    if(i==0) {
      head_ = holdTwo;
    }
    if(length_%3 == 0 && i == numIntervals - 1) {
      tail_ = holdOne;
    }
    curr = holdFour;
  }


  // head_ = curr2;
  // curr2->prev = NULL;
  // if(curr3->next == NULL && numIntervals == 1) {
  //   curr3->next = curr1;
  //   curr1->prev = curr3;
  //   curr1->next = NULL;
  //   return;
  // } else if (numIntervals == 1) {
  //   curr1->prev = curr3;
  //   curr1->next = curr3->next;
  //   curr3->next->prev = curr1;
  //   curr3->next = curr1;
  //   return;
  // } else if (numIntervals > 1) {
  //   curr1->prev = curr3;
  //   curr1->next = curr3->next;
  //   curr3->next->prev = curr1;
  //   curr3->next = curr1;
    
  //   curr1 = curr1->next;
  //   curr2 = curr1->next;
  //   curr3 = curr2->next;
  //   currLen += 3;

  //   for(int i = 1; i < numIntervals; i++) {
  //     if(curr3->next != NULL) {
  //       curr1->prev->next = curr2;
  //       curr2->prev = curr1->prev;
  //       curr1->prev = curr3;
  //       curr1->next = curr3->next;
  //       curr3->next->prev = curr1;
  //       curr3->next = curr1;
  //       currLen += 3;
  //     } else {
  //       curr1->prev->next = curr2;
  //       curr2->prev = curr1->prev;
  //       curr1->prev = curr3;
  //       curr1->next = NULL;
  //       curr3->next = curr1;
  //       return;
  //     }
  //     if (length_ - currLen < 3) {
  //       return;
  //     }
  //   }
  // }
  return;
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if(startPoint == endPoint || startPoint == NULL || endPoint == NULL) {
    return;
  } else {

    ListNode * temp = NULL;
    ListNode * holdStart = startPoint;
    ListNode * holdEnd = endPoint;
    ListNode * holdStartPrev = startPoint->prev;
    ListNode * holdEndNext = endPoint->next;
    ListNode * currNode = startPoint;

    if (holdStartPrev != NULL) {
      holdStartPrev->next = endPoint;
    } else {
      head_ = holdEnd;
    }
    if (holdEndNext != NULL) {
      holdEndNext->prev = startPoint;
    } else {
      tail_ = holdStart;
    }

    while (currNode != holdEnd) {
      temp = currNode->prev;
      currNode->prev = currNode->next;
      currNode->next = temp;
      currNode = currNode->prev;
    }

    temp = currNode->prev;
    endPoint = holdStart;
    startPoint = holdEnd;
    currNode->prev = holdStartPrev;
    currNode->next = temp;
    holdStart->next = holdEndNext;

    temp = NULL;
    holdStart = NULL;
    holdStartPrev = NULL;
    holdEnd = NULL;
    holdEndNext = NULL;

    return;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n > length_) {
    reverse(head_, tail_);
    return;
  } else if (length_ <= 1) {
    return;
  } else {

    ListNode * holdStart = head_;
    ListNode * holdEnd = head_;
    if(holdStart == NULL || holdEnd == NULL) {
      return;
    } else {
      while(holdEnd != NULL) {
        int i = 1;
        while(i < n) {
          if(holdEnd == tail_) {
            break;
          } else {
            if(holdEnd != NULL && holdEnd->next != NULL) {
              holdEnd = holdEnd->next;
            }
          }
          i++;
        }
        reverse(holdStart, holdEnd);
        holdStart = holdEnd->next;
        holdEnd = holdStart;
      }
    }
    return;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
  // set up the current list
  head_ = merge(head_, otherList.head_);
  tail_ = head_;

  // make sure there is a node in the new list
  if (tail_ != NULL) {
    while (tail_->next != NULL)
      tail_ = tail_->next;
  }
  length_ = length_ + otherList.length_;

  // empty out the parameter list
  otherList.head_ = NULL;
  otherList.tail_ = NULL;
  otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL) {
    return second;
  } else if (second == NULL) {
    return first;
  }

  ListNode * trackStart = NULL;
  ListNode * trackEnd = NULL;

  if (second->data < first->data) {
    trackStart = second;
    trackEnd = second;
    second = second->next;
  } else {
    trackStart = first;
    trackEnd = first;
    first = first->next;
  }

  while (first != NULL && second != NULL) {
    if(second->data < first->data) {
      trackEnd->next = second;
      trackEnd = second;
      second = second->next;
    } else {
      trackEnd->next = first;
      trackEnd = first;
      first = first->next;
    }
  }

  if(first == NULL) {
    trackEnd->next = second;
    second->prev = trackEnd;
  } else {
    trackEnd->next = first;
    first->prev = trackEnd;
  }

  return trackStart;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(start == NULL || start->next == NULL || chainLength == 0 || chainLength == 1) {
    return start;
  }
  int leftHalf = chainLength / 2;
  int rightHalf = chainLength - leftHalf;
  ListNode * left = start;
  ListNode * right = split(start, leftHalf);
  left = mergesort(left, leftHalf);
  right = mergesort(right, rightHalf);
  ListNode * sorted = merge(left, right);
  left = NULL;
  right = NULL;
  return sorted;
}