template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  return List<T>::ListIterator(head_, tail_);
}


template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  if (tail_ == NULL) {
    return List<T>::ListIterator(NULL, NULL);
  }
  return List<T>::ListIterator(tail_->next, tail_);
}



template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  
  ListNode* curr = head_;
  while (curr != NULL) {
    ListNode* temp = curr->next;
    delete curr;
    curr = temp;
  }
  //delete head_;
  //delete tail_;
  head_ = NULL;
  tail_ = NULL;
}


template <typename T>
void List<T>::insertFront(T const & ndata) {
  ListNode * newNode = new ListNode(ndata);
  newNode->next = head_;
  newNode->prev = NULL;
  
  if (head_ != NULL) {
    head_->prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
    tail_->next = NULL;  // new
  }
  
  head_ = newNode;
  length_++;

}



template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode * node1 = new ListNode(ndata);
  
  //  handle null cases, do prev pointer too
  node1->prev = tail_;
  node1->next = NULL;
  if (head_ == NULL) {
    head_ = node1;
  }
  if (tail_ != NULL) {
    tail_->next = node1;
  }
  tail_ = node1;
  tail_->next = NULL; // new
  length_++;
}


template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  if (start == NULL || splitPoint <= 0) {
    return start;
  }
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) { // || curr != NULL
    curr = curr->next;
  }
  if (curr == NULL) {
    return NULL;
  }
  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}


template <typename T>
void List<T>::waterfall() {
  if (head_ == nullptr || head_->next == nullptr) {
    return;
  }
  
  ListNode * curr = head_->next;
  while (curr != NULL && curr->next != NULL) {
    ListNode* temp = curr->next;
    curr->prev->next = temp;
    temp->prev = curr->prev;
    tail_->next = curr;
    curr->prev = tail_;
    curr->next = NULL;
    tail_ = curr;
    curr = temp->next;
  }
  
}



template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  ListNode* temp = startPoint;
  ListNode* curr = startPoint;
  while (temp != endPoint) {
    temp = curr->next;
    curr->next = curr->prev;
    curr->prev = temp;
    curr = curr->prev;
  }
  // handles last node in list to process
  temp = curr->next;
  curr->next = curr->prev;
  curr->prev = temp;
  temp = startPoint;
  startPoint = curr;
  endPoint = temp;

}


template <typename T>
void List<T>::reverseNth(int n) {
  if (n >= length_) {
    reverse();
    return;
  } else {
    ListNode* start_node = head_;
    ListNode* prev_end_node = NULL;
    while (start_node != NULL) {
      ListNode* end_node = start_node;
      for (int i = 1; ((i < n) && (end_node->next != NULL)); i++) {
        end_node = end_node->next;
      }
      ListNode* next_start = end_node->next;
      reverse(start_node, end_node);
      if (prev_end_node == NULL) {
        head_ = start_node;
      } else {
        prev_end_node->next = start_node;
      }
      end_node->next = next_start;

      prev_end_node = end_node;
      start_node = next_start;
    }
    if (tail_ == start_node) {
      tail_ = prev_end_node;
    }
    ListNode* tmp = head_;
    while (tmp && tmp->next) {
      tmp = tmp->next;
    }
    tail_ = tmp;
  }
}



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


template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  ListNode* to_return = NULL;
  ListNode* curr = NULL;
  ListNode* first_temp = first;
  ListNode* second_temp = second;

  if (first_temp == NULL) {
    return second;
  }
  if (second_temp == NULL) {
    return first;
  }
  
  if (first_temp->data < second_temp->data) {
    to_return = first_temp;
    curr = first_temp;
    first_temp = first_temp->next;
  } else {
    to_return = second_temp;
    curr = second_temp;
    second_temp = second_temp->next;
  }

  while (first_temp != NULL && second_temp != NULL) {
    if (first_temp->data < second_temp->data) {
        //if (to_return == NULL) {
          //to_return = first;
          //curr = first;
        //} else {
        // logic
          curr->next = first_temp;
          first_temp->prev = curr;
          curr = first_temp;
        //}
      first_temp = first_temp->next;
    } else {
        //if (to_return == NULL) {
          //to_return = second;
          //curr = second;
        //} else {
        // logic
          curr->next = second_temp;
          second_temp->prev = curr;
          curr = second_temp;
        //}
      second_temp = second_temp->next;
    }
  }

  if (first_temp != NULL) {
    curr->next = first_temp;
    first_temp->prev = curr;
  } else if (second_temp != NULL) {
    curr->next = second_temp;
    second_temp->prev = curr;
  }



  
  // iterate through both lists
  // always link the lowest value element as to_return->next
  // link previous properly

  return to_return;
}


template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  
  if (chainLength <= 1) {
    return start;
  }
  int left = chainLength/2;
  int right = chainLength-left;
  ListNode* start2 = start;
  
  for (int i = 0; i < left-1; i++) {
    start2 = start2->next;
    
  }

  ListNode* tmp = start2;
  start2 = start2->next;
  tmp->next = nullptr;
  if (start2) {
    start2->prev = nullptr;
  }

  ListNode* list1 = mergesort(start, left);
  ListNode* list2 = mergesort(start2, right);
  return merge(list1, list2);
}
