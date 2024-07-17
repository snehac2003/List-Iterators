#pragma once
#include <iterator>
#include <iostream>
#include <algorithm>
using namespace std;


template <class T>
class List {
  private:
   
    class ListNode {
      public:
        
        ListNode();

        
        ListNode(const T & ndata);

        
        ListNode* next;

        
        ListNode* prev;

        
        const T data;
    };

  public:
    
    List();

    
    List(const List<T>& other);

    
    List<T>& operator=(const List<T>& rhs);

    
    int size() const;

    
    void print(ostream& os = std::cout) const;

    
    bool empty() const;

    
    ~List();

   
    void insertFront(const T& ndata);

   
    void insertBack(const T& ndata);

    
    void reverse();

    
    void reverseNth(int n);

    
    void waterfall();

    
    List<T> split(int splitPoint);

    
    void mergeWith(List<T>& otherList);

    
    void sort();

   
    #include "List-ListIterator.hpp"

    
    ListIterator begin() const;

   
    ListIterator end() const;

    // Iterator constructor
    template <class Iter>
    List(const Iter& start, const Iter& end);

  private:
    
    ListNode* head_;

    
    ListNode* tail_;

    
    int length_;

    void _copy(const List<T>& other); // implemented in List-given.hpp

    
    void _destroy();

   
    void reverse(ListNode*& startPoint, ListNode*& endPoint);

    
    ListNode* split(ListNode* start, int splitPoint);

   
    ListNode* merge(ListNode* first, ListNode* second);

    
    ListNode* mergesort(ListNode* start, int chainLength);
};

#include "List.hpp"


#include "List-given.hpp"
