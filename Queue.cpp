/**

 * @description A Queue ADT with two concrete impelementation
 *   examples: an array based queue implementaiton (AQueue), and
 *   a linked list based implementation (LQueue).
 */
 
#include "Queue.hpp" 
int Job::nextListId = 1;


/** Job default constructor
 * Default constructor for Job, needed because some Queue types
 * create an empty array of Job objects, so they need to get filled
 * with empty jobs.  We simply initialize everything to 0, as 
 * Job objects created this way, without a priority or service time,
 * can't be used as real jobs in a simulation.
 */
Job::Job()
{
  this->id = 0;
  this->priority = 0;
  this->serviceTime = 0;
  this->startTime = 0;
  this->endTime = 0;
}


/** Job constructor
 * The actual constructor that needs to be used for Jobs in a simulation.
 * The job is assigned a priority, serviceTime and we record the startTime
 * when the job arrived and began waiting on the system queue for processing.
 * 
 * @param priority Each job in our simulations has a priority level.  In this
 *   Job object and simulation, the higher the number, the higher the priority
 *   of the Job.
 * @param serviceTime This is the time that the job needs to run, once it is
 *   selected/scheduled by the system dispatcher to be executed.  This represents
 *   the time the system is busy processing this Job once it starts running.
 * @param startTime The system time at which this jobs was created.  Also will be
 *   the system time this job was added to a job queue in the system and began
 *   waiting to be executed.
 */
Job::Job(int priority, int serviceTime, int startTime)
{
  this->id = nextListId++;
  this->priority = priority;
  this->serviceTime = serviceTime;
  this->startTime = startTime;
  this->endTime = startTime;
}


/** endTime setter
 * Setter method to set the endTime of this Job.  This is actually the endTime
 * of when the job stoped waiting and began executing (not the time when the job
 * was finished).  The endTime - startTime gives the total waitTime this job
 * spent waiting.
 *
 * @param endTime The time when job stoped waiting on a queue and began executing.
 */
void Job::setEndTime(int endTime)
{
  this->endTime = endTime;
}


/** id getter
 * Getter method to return this Job's id.  Used for display purposes.
 *
 * @returns int The unique id of this Job is returned.
 */
int Job::getId() const
{
  return id;
}


/** service time getter
 * Getter method to return this Job's service time.  Service time
 * is the amount of time this job needs from the system to complete
 * its task.
 *
 * @returns int The serviceTime for this Job is returned.
 */
int Job::getServiceTime() const
{
  return serviceTime;
}


/** priority getter
 * Getter method to return this Job's priority level.  Priority
 * is a measure of the job importance.  In this simulation, higher
 * priority means higher importance.
 *
 * @returns int The priority level for this Job is returned.
 */
int Job::getPriority() const
{
  return priority;
}


/** waitTime getter
 * Getter method to return this Job's waitTime.  Wait time is
 * the difference from the endTime when the job stoped waiting
 * (and began executing) and startTime when the job was created
 * and began waiting to get access to the system for execution.
 *
 * @returns int The wait time for this Job is returned.  Wait time
 *   is not valid until after the job as exited the wait queue, and
 *   its endTime has been set.
 */
int Job::getWaitTime() const
{
  return endTime - startTime;
}


/** cost getter
 * Getter method to return this Job's cost.  Cost is a measure of
 * used to evaluate how well a particular system performs in
 * processing jobs.  In this simulation, we want to minimize time
 * high priority jobs spend waiting, and maximize high priority
 * job throughput.  Thus cost is a combination of priority and how
 * long the job spent waiting to be processed.  Since higher numbers
 * are used to mean higher priorities, multiplying the wait time 
 * times the priority scales the cost so that high priority jobs
 * that have to wait for long periods have high costs.  In the
 * system, we want to minimize cost as a measure of performance.
 *
 * @returns int The cost for this Job is returned.  Cost is a measure
 *   of performance with regards to this parcitular jobs.  Cost is
 *   measured in this system as the job priority times the time the
 *   job was forced to wait before it could start executing.
 */
int Job::getCost() const
{
  return priority * getWaitTime();
}


/** overload boolean equal comparison
 * Overload boolean comparison between jobs.  The main purpose of
 * providing boolean comparisons between jobs in this simulation is
 * so that priority based schedulers can order the jobs based on
 * priority level, from lowest priority to highest priority.  Thus
 * for a Job, jobs are equal when they have equal priorities.
 *
 * @param rhs The Job object on the right hand side of the boolean
 *   comparison.
 *
 * @returns bool True if the two jobs have equal priority, false
 *   otherwise.
 */
bool Job::operator==(const Job& rhs) const
{
  return this->priority == rhs.priority;
}


/** overload boolean less than
 * Overload boolean less than comparison between jobs.  The main
 * purpose of providing boolean comparisons between jobs in this
 * simulation is so that priority based schedulers can order the jobs
 * based on priority level, from lowest priority to highest priority.
 * Thus for a Job, a job is less than another job if its priority
 * is smaller.
 *
 * @param rhs The Job object on the right hand side of the boolean
 *   comparison.
 *
 * @returns bool True if this job has lower priority than the rhs
 *   job, false otherwise.
 */
bool Job::operator<(const Job& rhs) const
{
  return this->priority < rhs.priority;
}


/** overload boolean greater than
 * Overload boolean greater than comparison between jobs.  The main
 * purpose of providing boolean comparisons between jobs in this
 * simulation is so that priority based schedulers can order the jobs
 * based on priority level, from lowest priority to highest priority.
 * Thus for a Job, a job is greater than another job if its priority
 * is bigger.
 *
 * @param rhs The Job object on the right hand side of the boolean
 *   comparison.
 *
 * @returns bool True if this job has higher priority than the rhs
 *   job, false otherwise.
 */
bool Job::operator>(const Job& rhs) const
{
  return this->priority > rhs.priority;
}


/** overload boolean <=
 * Overload boolean less than or equal comparison between jobs.  The
 * main purpose of providing boolean comparisons between jobs in this
 * simulation is so that priority based schedulers can order the jobs
 * based on priority level, from lowest priority to highest priority.
 * Thus for a Job, a job is less than or equal another job if its
 * priority is smaller or the same.
 *
 * @param rhs The Job object on the right hand side of the boolean
 *   comparison.
 *
 * @returns bool True if this job has lower or equal priority than the
 *   rhs job, false otherwise.
 */
bool Job::operator<=(const Job& rhs) const
{
  return this->priority <= rhs.priority;
}


/** overload output stream operator 
 * Overload the output stream operator to provide a representation
 * of this Job suitable for display.  Mainly useful for displaying
 * queue contents and for debugging purposes.
 */
ostream& operator<<(ostream& out, const Job& aJob)
{
  // out << "[id: " << aJob.id
  //     << " priority: " << aJob.priority
  //     << " serviceTime: " << aJob.serviceTime
  //     << " startTime: " << aJob.startTime
  //     << " endTime: " << aJob.endTime
  //     << " waitTime: " << aJob.getWaitTime()
  //     << "]";
  out << "[id: " << aJob.id
      << " priority: " << aJob.priority
      << "]";
  return out;
}

//-------------------------------------------------------------------------
/** Queue equivalence
 * Compare two given queues to determine if they are equal or not.
 * stacks are equal if they are both of the same size, and each
 * corresponding item on each stack is equal at the same position on the
 * stack.  This function relies on overloaded operator[] to access
 * items on stack by index for the comparison.
 *
 * @param rhs The stack on the right hand side of the boolean comparison
 *   expression to compare this stack against to check for equivalence.
 *
 * @returns bool Returns true if the stacks are equal, and false otherwise.
 */
bool Queue::operator==(const Queue& rhs) const
{
  // if number of items on the stacks don't match, then they can't
  // be equivalent
  if (this->length() != rhs.length())
  {
    return false;
  }

  // otherwise need to check each item individually
  for (int index = 0; index < this->length(); index++)
  {
    if ((*this)[index] != rhs[index])
    {
      return false;
    }
  }

  // if we get to this point, all itmes checked were equivalent, so
  // we are done and the answer is yes the stacks are equal
  return true;
}


/** Queue output stream operator
 * Friend function for Queue ADT, overload output stream operator to allow
 * easy output of queue representation to an output stream.
 */
ostream& operator<<(ostream& out, const Queue& aQueue)
{
  out << aQueue.tostring();
  return out;
}



//-------------------------------------------------------------------------
/** queue (array) constructor
 * Constructor for queue.  Default to enough room for 100 items
 * NOTE: the front pointer points directly to the index of the front item, but
 * the backIndex pointer points to the index-1 of the item where next insertion
 * will happen.  
 * NOTE: we treat the items array as a circular buffer, so all increments of
 * indexes must be modulo current allocSize, to wrap backIndex around to beginning.
 *
 * @param initialAlloc Initial space to allocate for queue, defaults to
 *   100.
 */
AQueue::AQueue(int initialAlloc)
{
  allocSize = initialAlloc;
  numitems = 0;
  frontIndex = 0;
  backIndex = allocSize - 1; // back points to (x-1) % allocSize index
  items = new int[allocSize];
}


/** queue (array) constructor
 * Constructor for queue using an array initializer.
 * NOTE: the front pointer points directly to the index of the front item, but
 * the backIndex pointer points to the index-1 of the item where next insertion
 * will happen.  
 * NOTE: we treat the items array as a circular buffer, so all increments of
 * indexes must be modulo current allocSize, to wrap backIndex around to beginning.
 *
 * @param initialAlloc Initial space to allocate for queue, defaults to
 *   100.
 */
AQueue::AQueue(int initItems[], int numitems)
{
  this->allocSize = numitems;
  this->numitems = numitems;
  frontIndex = 0;
  items = new int[allocSize];

  // copy the initialize items into this queue
  for (int index = 0; index < numitems; index++)
  {
    items[index] = initItems[index];
  }

  // set up the back index
  backIndex = numitems - 1;
}


/** queue (array) destructor
 */
AQueue::~AQueue()
{
  // free up currently allocated memory
  delete [] items;
}


/** queue (array) clear
 * Function to initialize the queue back to an empty state.
 * Postcondition: frontIndex = 0; backIndex = allocSize-1; numitems=0; isEmpty() == true
 */
void AQueue::clear()
{
  frontIndex = 0;
  backIndex = allocSize - 1;
  numitems = 0;
}


/** queue (array) isEmpty
 * Determine whether queue is currently empty or not.
 *
 * @returns returns true if the queue is empty, otherwise
 *   returns false.
 */
bool AQueue::isEmpty() const
{
  return numitems == 0;
}


/** queue (array) isFull
 * Determine whether queue is currently full or not.
 *
 * @returns returns true if the queue is full, otherwise
 *   returns false.
 */
bool AQueue::isFull() const
{
  return numitems == allocSize;
}


/** queue (array) enqueue
 * Add newItem to the back of the queue.
 * Preconditon: The queue exists
 * Postcondition: The queue is changed and newItem is added to the back
 *   of the queue.
 * @param newItem The new item to add to the frontIndex of this queue.
 */
void AQueue::enqueue(const int& newItem)
{
  // if queue is full, grow it
  if (isFull())
  {
    // double the current size
    int newAllocSize = 2 * allocSize;

    // alloc the new space
    int* newItems = new int[newAllocSize];

    // and copy the queue to the new storage space
    // since we are copying anyway, we shift the items from the old
    // frontIndex back to index 0
    int oldIndex = frontIndex;
    for (int index = 0; index < numitems; index++)
    {
      newItems[index] = items[oldIndex];
      oldIndex = (oldIndex + 1) % allocSize;
    }
    frontIndex = 0;
    backIndex = numitems-1;

    // free up the old space, start using the new space
    delete [] items;
    items = newItems;
    allocSize = newAllocSize;
  }

  // add the item, and increment our top
  backIndex = (backIndex + 1) % allocSize;
  numitems++;
  items[backIndex] = newItem;
}


/** queue (array) front
 * Peek at and return the front element of the queue.
 * Preconditon: The queue exists and is not empty
 * Postcondition: If the queue is empty, we throw QueueEmpty 
 *   exception; otherwise, the front element of the queue is
 *   returned
 * @returns T The item of type T currently on the front of this
 *   queue.
 */
int AQueue::front() const
{
  //assert(topIndex != 0);
  if (isEmpty())
  {
    throw EmptyQueueException("AQueue<T>::front()");
  }
  else
  {
    return items[frontIndex];
  }
}


/** queue (array) dequeue
 * Remove the front element from the queue.  Some ADT combine dequeue
 * and front.  We have two separate operations in this ADT.
 * Preconditon: The queue exists and is not empty.
 * Postcondition: If the queue is empty, we throw QueueEmpty
 *   exception; otherwise the front element of the queue is removed
 *   from the queue.
 */
void AQueue::dequeue()
{
  // assert(topIndex != 0);
  if (isEmpty())
  {
    throw EmptyQueueException("Aqueue<T>::dequeue()");
  }
  else
  {
    numitems--;
    frontIndex = (frontIndex + 1) % allocSize;
  }
}


/** queue (array) length
 * Getter method to access the current queue length.
 *
 * @returns length Returns the current queue length.
 */
int AQueue::length() const
{
  return numitems;
}


/** queue (array) tostring
 * Represent this queue as a string.
 *
 * @returns string Returns the contents of queue as a string.
 */
string AQueue::tostring() const
{
  ostringstream out;
  
  out << "Front: ";
  int index = frontIndex;
  while (index != (backIndex + 1) % allocSize)
  {
    out << items[index] << " ";
    index++;
  }
  out << ":Back" << endl;
  
  return out.str();
}


/** Queue (array) indexing operator
 * Access internel elements of queue using indexing operator[].
 * This is not a normal queue operation, we use mainly for testing
 * so that we can compare if two queues are equal at each internal
 * element of the queue.  For this reason, this operator should 
 * probably be private to the Queue class.
 *
 * @param index The index of the item on the queue we want to access
 *   and return, where index 0 represents the front of the queue and
 *   index == numitems-1 is the back.
 * 
 * @returns T Returns the item at "index" on the queue.
 */
const int& AQueue::operator[](int index) const
{
  // bounds checking, we will throw our stack exception if fails
  if (index < 0 || index >= numitems)
  {
    throw InvalidIndexQueueException("AQueue<T>::operator[]");
  }
  // otherwise we can directly access the asked for item from our items array
  // our memory buffer is being treated as a circular buffer, so we
  // have to calculated the indicated index by hand
  else
  {
    return items[(frontIndex + index) % allocSize];
  }
}



//-------------------------------------------------------------------------
/** queue (list) constructor
 * Constructor for linked list version of queue.
 * An empty queue is indicated by both front and back
 * pointers pointing to null.
 */
LQueue::LQueue()
{
  queueFront = NULL;
  queueBack = NULL;
  numitems = 0;
}


/** queue (list) destructor
 * Destructor for linked list version of queue.
 */
LQueue::~LQueue()
{
  clear();
}


/** queue (list) clear
 * This will empty out the queue.  This method frees up all of the
 * dynamically allocated memory being used by the queue linked list
 * nodes.
 */
void LQueue::clear()
{
  Node* temp;

  // iterate through Nodes in queue, freeing them up
  // as we visit them
  while (queueFront != NULL)
  {
    temp = queueFront;
    queueFront = queueFront->link;

    // dellocate this Node memory
    delete temp;
  }

  // make sure all private members are cleard correctly
  queueBack = NULL;
  numitems = 0;
}


/** queue (list) isEmpty
 * Check if queue is empty or not.
 * 
 * @returns true if the queue is currently empty, or
 *   false otherwise.
 */
bool LQueue::isEmpty() const
{
  return queueFront == NULL;
  // return numitems == 0;
}


/** queue (list) enqueue
 * Add the indicated item onto the back of the queue.
 *
 * @param newItem The new item we will add to the back of
 *   this queue.
 */

void LQueue::enqueue(const int& newItem)
{
  // dynamically allocate space for the new Node to hold
  // this newItem
  Node* newNode = new Node;

  // initialize the node
  newNode->item = newItem;
  newNode->link = NULL;

  // if the queue is empty, then this new node is the
  // front and back node
  if (queueFront == NULL)
  {
    queueFront = newNode;
  }
  // otherwise, it gets added onto the back
  else
  {
    queueBack->link = newNode;
  }

  // the new node added is now the new back of the queue
  queueBack = newNode;
  numitems++;
}


/** queue (list) front
 * Return the front item from the queue.
 *
 * @returns T Returns the item currently at the front of
 *   this queue.
 */
int LQueue::front() const
{
  //assert(queueFront != NULL)
  if (isEmpty())
  {
    throw EmptyQueueException("LQueue<T>::front()");
  }
  else
  {
    return queueFront->item;
  }
}


/** queue (list) dequeue
 * This function actually removes the item at the front of the queue from
 * the queue.  It is undefined what happens if you try and dequeue() from
 * an empty queue.  This method throws an exception if dequeue is attempted
 * from an empty queue.
 */
void LQueue::dequeue()
{
  //assert(queueTop != NULL)
  if (isEmpty())
  {
    throw EmptyQueueException("LQueue<T>::dequeue()");
  }
  else
  {
    // keep track of the current front, so we can deallocate
    Node* temp;
    temp = queueFront;

    // remove the front item from the queue
    // if queue becomes empty, make sure both front and back
    // are NULL
    queueFront = queueFront->link;
    if (queueFront == NULL)
    {
      queueBack = NULL;
    }
    numitems--;
    
    // deallocate the old top now
    delete temp;
  }
}


/** queue (array) length
 * Accessor method to return the current length of this queue.
 *
 * @returns int The current queue length
 */
int LQueue::length() const
{
  return numitems;
}


/** queue (array) tostring
 * Represent this queue as a string.
 *
 * @returns string Returns the contents of queue as a string.
 */
string LQueue::tostring() const
{
  ostringstream out;
  Node* temp = queueFront;
  
  out << "Front: ";
  while (temp != NULL)
  {
    out << temp->item << " ";
    temp = temp->link;
  }
  out << ":Back" << endl;

  return out.str();
}


/** Queue (list) indexing operator
 * Access internel elements of queue using indexing operator[].
 * This is not a normal queue operation, we use mainly for testing
 * so that we can compare if two queues are equal at each internal
 * element of the queue.  For this reason, this operator should 
 * probably be private to the Queue class.
 *
 * @param index The index of the item on the queue we want to access
 *   and return, where index 0 represents the front of the queue and
 *   index == length-1 is the back.
 * 
 * @returns T Returns the item at "index" on the queue.
 */
const int& LQueue::operator[](int index) const
{
  // bounds checking, we will throw our stack exception if fails
  if (index < 0 || index >= numitems)
  {
    throw InvalidIndexQueueException("LQueue<T>::operator[]");
  }
  // otherwise we will have to search our list for the desired item
  // we will search from the queue front, which is considered
  // index 0
  else
  {
    int currentIndex = 0;
    Node* currentNode = queueFront;
    
    while (currentIndex != index)
    {
      currentIndex++;
      currentNode = currentNode->link;
    }

    return currentNode->item;
  }
}

//start// required code, priority queue::enqueue()
void PriorityQueues::enqueue(const Job& newItems)
{
  bool i=false;
  Node* newNode = new Node;
  Node* n = new Node;
  Node* n2 = new Node;
  int newItem = newItems.getPriority();

  newNode->item = newItem;
  newNode->link = NULL;
  
  if (LQueue::queueFront==NULL)
  {
    LQueue::queueFront = newNode;
  	LQueue::queueBack = newNode;
  }
  else if(newItem > LQueue::queueFront->item)
  {
  	newNode->link=LQueue::queueFront;
	LQueue::queueFront=newNode;
  }
  else 
  {
  	n=LQueue::queueFront;
  	n2=n->link;	
  	while(n2!=NULL)
  	{
  		if(n2->item < newItem)
  		{
  			n->link=newNode;
  			newNode->link=n2;
  			i=true;
  			break;
		}
		n=n->link;
		n2=n->link;	
	}	
	if(i!=true)
	{
		LQueue::queueBack->link=newNode;
	LQueue::queueBack=newNode;	
	}
  }
  LQueue::numitems++;
}
//end

//-------------------------------------------------------------------------

// Assignment 11
// You should add the implemenation of your PriorityQueue
// enqueue() method here.
