/**
 
 * @description A Queue ADT with two concrete impelementation
 *   examples: an array based queue implementaiton (AQueue), and
 *   a linked list based implementation (LQueue).
 */
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


#ifndef QUEUE_HPP
#define QUEUE_HPP


//-------------------------------------------------------------------------
/** queue (base class)
 * The basic definition of the Queue Abstract Data Type (ADT)
 * and queue operations.  All declared functions here are
 * virtual, they must be implemented by concrete derived
 * classes.
 */
class Queue
{
public:
  /** clear
   * Method to clear out or empty any items on queue,
   * put queue back to empty state.
   * Postcondition: Queue is empty.
   */
  virtual void clear() = 0;

  /** isEmpty
   * Function to determine whether the queue is empty.  Needed
   * because it is undefined to remove from empty queue.  This
   * function will not change the state of the queue (const).
   *
   * @returns bool true if queue is empty, false otherwise.
   */
  virtual bool isEmpty() const = 0;

  /** enqueue
   * Add a new item onto back of queue.  
   *
   * @param newItem The item of template type T to add on back of
   *   the current queue.
   */
  virtual void enqueue(const int& newItem) = 0;

  /** front
   * Return the front item from the queue.  Note in this ADT, peeking
   * at the front item does not remove the front item.  Some ADT combine
   * front() and dequeue() as one operation.  It is undefined to try and
   * peek at the front item of an empty queue.  Derived classes should
   * throw an exception if this is attempted.
   *
   * @returns T Returns the front item from queue.
   */
  virtual int front() const = 0;

  /** dequeue
   * Remove the item from the front of the queue.  It is undefined what
   * it means to try and dequeue from an empty queue.  Derived classes should
   * throw an exception if dequeue() from empty is attempted.
   */
  virtual void dequeue() = 0;

  /** length
   * Return the current length or number of item son the queue.
   *
   * @returns int The current length of this queue.
   */
  virtual int length() const = 0;
  
  /** tostring
   * Represent queue as a string
   */
  virtual string tostring() const = 0;


  // overload operators, mostly to support boolean comparison betwen
  // two queues for testing
  bool operator==(const Queue& rhs) const;
  virtual const int& operator[](int index) const = 0;
  
  // overload output stream operator for all queues using tostring()
  friend ostream& operator<<(ostream& out, const Queue& aQueue); 
};




//-------------------------------------------------------------------------
/** Empty queue exception
 * Class for empty queue exceptions
 */
class EmptyQueueException
{
private:
  string message;
  
public:
  EmptyQueueException()
  {
    message = "Error: operation on empty queue";
  }

  EmptyQueueException(string str)
  {
    message = "Error: " + str + " attempted on emtpy queue";
  }

  string what()
  {
    return message;
  }
};

class Job
{
public:
  static int nextListId;
  int id;
  int priority;
  int serviceTime;
  int startTime;
  int endTime;

  Job();
  Job(int priority, int serviceTime, int startTime);

  void setEndTime(int endTime);
  int getId() const;
  int getServiceTime() const;
  int getPriority() const;
  int getWaitTime() const;
  int getCost() const;
  
  bool operator==(const Job& rhs) const;
  bool operator<(const Job& rhs) const;
  bool operator>(const Job& rhs) const;
  bool operator<=(const Job& rhs) const;

  friend ostream& operator<<(ostream& out, const Job& aJob);
};
/** InvalidIndex queue exception
 * Class to be thrown when an invalid index is asked for when indexing
 * into a queue object.
 */
class InvalidIndexQueueException
{
private:
  string message;
  
public:
  InvalidIndexQueueException()
  {
    message = "Error: invalid index request for queue";
  }

  InvalidIndexQueueException(string str)
  {
    message = "Error: " + str + " invalid index request for queue";
  }

  string what()
  {
    return message;
  }
};



//-------------------------------------------------------------------------
/** queue (array implementation)
 * Implementation of the queue ADT as a fixed array.  This
 * implementation combines a circular buffer implementation, to make
 * sure that both enqueue() and dequeue() operations are O(1) constant
 * time.  However, it also uses dynamic memory allocation, and
 * demonstrates doubling the size of the allocated space as needed to
 * grow queue if/when the queue becomes full.
 *
 * @var allocSize The amount of memory currently allocated for this queue.
 * @var numitems The current length or number of items on the queue.
 * @var front A pointer to the index of the front item on the queue.
 * @var back A pointer to the back or last item on the queu.
 * @var items The items on the queue.  This is a dynamically allocated array that
 *   can grow if needed when queue exceeds current allocation.
 */
class AQueue : public Queue
{
private:
  int allocSize;  // amount of memory allocated
  int numitems;     // The current length of the queue
  int frontIndex; // index of the front item of the queue
  int backIndex;  // index of the last or rear item of the queue
  int* items; 

public:
  AQueue(int initialAlloc = 100); // constructor
  AQueue(int initItems[], int numitems);
  ~AQueue(); // destructor
  void clear();
  bool isEmpty() const;
  bool isFull() const;
  void enqueue(const int& newItem);
  int front() const;
  void dequeue();
  int length() const;
  string tostring() const;
  const int& operator[](int index) const;
};




//-------------------------------------------------------------------------
/** Node
 * A basic node contaning an item and a link to the next node in
 * the linked list.
 */
struct Node
{
  int item;
  Node* link;
};



//-------------------------------------------------------------------------
/** queue (linked list implementation)
 * Implementation of the queue ADT as a dynamic linked list.  This implementation
 * uses link nodes and grows (and shrinks) the nodes as items enqueued and dequeued
 * onto queue.
 *
 * @var queueFront a pointer to the node holding the front item of the queue.
 * @var queueBack a pointer to the node holding the back item of the queue.
 * @var numitems The length or number of items currently on the queue.
 */
class LQueue : public Queue
{
protected:
  Node* queueFront;
  Node* queueBack;
  int numitems; // the queue length
  
public:
  LQueue(); // default constructor
  ~LQueue(); // destructor
  void clear();
  bool isEmpty() const;
  void enqueue(const int& newItem);
  int front() const;
  void dequeue();
  int length() const;
  string tostring() const;
  const int& operator[](int index) const;
};



//-------------------------------------------------------------------------

// Assignment 11
// You should add your PriorityQueue definition here.  You class should
// be derived from the LQueue<T> class (using public inheritance).
// You only need to override and implement 1 method in your PriorityQueue
// class, the enqueue() method, which should insert new items into the
// linked list ordered by priority, rather than inserting at the end
// of the queue as is done by the basic enqueue() 

class PriorityQueues : public LQueue
{
	public:
	void enqueue(const Job& newItem);
};

// include the implementaiton of the class templates
#include "Queue.cpp"  

#endif
  
