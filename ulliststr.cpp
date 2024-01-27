#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"
#include <iostream>

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

/**
* Returns a const reference to the back element
*   - MUST RUN in O(1)
*/
std::string const & ULListStr::back() const {
  return tail_->val[tail_->last - 1];
}

/**
* Returns a const reference to the front element
*   - MUST RUN in O(1)
*/
std::string const & ULListStr::front() const{
  return head_->val[head_->first];
}

/** 
* Returns a pointer to the item at index, loc,
*  if loc is valid and NULL otherwise
*   - MUST RUN in O(n) 
*/
std::string* ULListStr::getValAtLoc(size_t loc) const{
  // check if loc is valid and if there is even a list
  if (loc >= size_ || head_ == NULL) { 
    return NULL;
  }

  Item* temp = head_;
  size_t currloc = 0; // counter

  // iterate over the list until we find loc
  std::cout <<"temp last and first*: " << temp->last << " " << temp->first << std::endl;
  while(temp != NULL && loc >= currloc + (temp->last - temp->first)){
    // if(temp->next == NULL){
    //   break;
    // }
    std::cout <<"temp last and first: " << temp->last << " " << temp->first << std::endl;
    currloc += temp->last - temp->first;
    std::cout << "temp next is: " << temp->next << std::endl;
    temp = temp->next;
  }
  std::cout<<"currloc: " << currloc << std::endl;
  std::cout<<"temp: " << temp << std::endl;
  std::cout<<"tail last: " << tail_->last << std::endl;
  std::cout<<"tail first: " << tail_->first << std::endl;
  
  // check if loc is in the Item that we stopped at
  if(temp != NULL && loc >= currloc && loc < currloc + (temp->last - temp->first)){
    std::cout<<"im in! currloc: " << currloc << std::endl;
    size_t idx = loc - currloc + temp->first;
    return &temp->val[idx];
  } 

  // loc is not found
  return NULL;
}

/**
* Adds a new value to the back of the list
*   - MUST RUN in O(1)
*/
void ULListStr::push_back(const std::string& val){  
  // check if the tail exists or if it's full
  if (tail_ == NULL || tail_->last == ARRSIZE){
    // must create a new Item
    Item* newitem = new Item();
    newitem->prev = tail_;

    if(tail_ != NULL){ // if the list was not empty before this
      tail_->next = newitem;
    }

    // set tail to point to the new item
    tail_ = newitem;

    if(head_ == NULL){ // if the list was empty before this
      head_ = newitem;
    }
  }

  // actually adding the value to the new tail
  tail_->val[tail_->last] = val;
  tail_->last++;
  // increment size by 1 in all cases
  size_++;
}

/**
* Removes a value from the back of the list
*   - MUST RUN in O(1)
*/
void ULListStr::pop_back(){
  // check if the list is empty first
  if (size_ == 0){
    return;
  }
    
  // if there's only 1 thing in the tail's array, delete the tail
  if (tail_->last == 1){
    Item* temp = tail_;
    tail_ = tail_->prev;
    
    if (tail_ != NULL){
      tail_->next = NULL;
    } else {
      // in the case that the only thing in the only Item was popped
      head_ = NULL;
      tail_ = NULL;
    }
    delete temp;
  }
  // update size to decrement by 1 in all cases
  size_--;
}

/**
* Adds a new value to the front of the list.
* If there is room before the 'first' value in
* the head node add it there, otherwise, 
* allocate a new head node.
*   - MUST RUN in O(1)
*/
void ULListStr::push_front(const std::string& val){
  // check if the list is empty
  // note: my push front and back are different because i went slightly insane with push back
  // it didn't work at first so I made a new implementation, and didn't change push front to
  // reflect the new implementation because it already worked
  if(head_ == NULL){
    Item* newitem = new Item();
    newitem->val[ARRSIZE-1] = val;
    newitem->first = ARRSIZE-1;
    newitem->last = ARRSIZE;
    newitem->prev = NULL;
    newitem->next = head_;
    // set head to point to the new item at the front
    std::cout << "head before: " << head_ <<  "\n";
    head_ = newitem;
    std::cout << "head after: " << head_ <<  "\n";
    tail_ = newitem;
    tail_->next = NULL;
    std::cout << "pushed front by making new item\n";
  } else if (head_->first == 0){
    // if there is no more room in the first Item
    Item* newitem = new Item();
    newitem->val[ARRSIZE-1] = val;
    newitem->first = ARRSIZE-1;
    newitem->last = ARRSIZE;
    newitem->next = head_;
    newitem->prev = NULL;
    // reset head to reflect that there's a new item at the front
    head_ = newitem;
  } else {
    // getting here means the head item is not full
    // we can add val directly
    head_->val[head_->first - 1] = val;
    head_->first--;
  }
  // increment size by 1 in all cases
  size_++;
}

/**
* Removes a value from the front of the list
*   - MUST RUN in O(1)
*/
void ULListStr::pop_front(){
  // check if list is empty first
  if(size_ == 0){
    return;
  }
  // update first index to be one more than it was before
  head_->first++;

  // delete head if there was only 1 thing in the Item's array
  if (head_->first >= ARRSIZE){
    Item* temp = head_;
    head_ = head_->next;

    // check if anything will be left in the list at all after popping
    if (head_ != NULL){
      head_->prev = NULL;
    } else {
      tail_ = NULL;
    }
    delete temp;
  }
  // decrement size by 1 in all cases
  size_--;
}

// my implementations end here
// code below is not written by me
void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
