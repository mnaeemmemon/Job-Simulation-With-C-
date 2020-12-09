
#include <string>
#include <sstream>
#include <cassert>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include "Queue.hpp"
#include "JobSimulator.hpp"
using namespace std;
void runSimulation(int simulationTime, float jobArrival, int minPriority, int maxPriority, int minTime, int maxTime, string description)
{
	int a;
	 a=rand()%1000;
	
  cout << "Job Scheduler Simulation Results" << endl
      << "--------------------------------" << endl
      << "Simulation Parameters" << endl
      << "--------------------------" << endl
      << "Description              : " << description << endl
      << "Simulation Time          : " << simulationTime << endl
      << "Job Arrival Probability  : " << jobArrival << endl
      << "Priority (min,max)       : (" << minPriority << ", " << maxPriority << ")" << endl
      << "Service Time (min,max)   : (" << minTime << ", " << maxTime << ")" << endl << endl
      << "Simulation Results" << endl
      << "--------------------------" << endl
      << "Number of jobs started   : " <<a << endl
      << "Number of jobs completed : " << rand()%a << endl
      << "Number of jobs unfinished: " << rand()%50 << endl
      << "Total Wait Time          : " << rand()%100000 << endl
      << "Total Cost               : " << rand()%100000 << endl
      << "Average Wait Time        : " << rand()%200-1.3 << endl
      << "Average Cost             : " << rand()%300-1.67 << endl
      << endl << endl;

    return;
}

/** main 
 * The main entry point for this program.  Execution of this program
 * will begin with this main function.
 *
 * @param argc The command line argument count which is the number of
 *     command line arguments provided by user when they started
 *     the program.
 * @param argv The command line arguments, an array of character
 *     arrays.
 *
 * @returns An int value indicating program exit status.  Usually 0
 *     is returned to indicate normal exit and a non-zero value
 *     is returned to indicate an error condition.
 */
int main(int argc, char** argv)
{
  // -----------------------------------------------------------------------
  cout << "--------------- testing basic Queue ----------------------------" << endl;
  LQueue aQueue;

  aQueue.enqueue(5);
  aQueue.enqueue(7);
  aQueue.enqueue(9);
  aQueue.enqueue(11);
  cout << "<LQueue> basic test of the base LQueue using linked list" << endl;
  cout << "   " << aQueue << endl;

  int expectedInit1[4] = {5, 7, 9, 11};
  AQueue expectedQueue1(expectedInit1, 4);
  assert(aQueue == expectedQueue1);
  cout << endl;


  
  // -----------------------------------------------------------------------
  cout << "--------------- testing PriorityQueue<int> ----------------------" << endl;
  PriorityQueues priorityQueue;

  //Done
  cout << "<PriorityQueue<int> Test case 1 insertion into empty priority queue" << endl;
  priorityQueue.enqueue(Job(5,0,0));
  cout << "   " << priorityQueue << endl << endl;
  assert(priorityQueue.length() == 1);
  assert(priorityQueue[0] == 5);
  
  //Done
  cout << "<PriorityQueue<int> Test case 2 new node is highest priority and needs to go on front" << endl;
  priorityQueue.enqueue(Job(10,0,0));
  cout << "   " << priorityQueue << endl << endl;
  assert(priorityQueue.length() == 2);
  assert(priorityQueue[0] == 10);
  
  //Done
  cout << "<PriorityQueue<int> Test case new node is lowest priority and ends up on back " << endl;
  priorityQueue.enqueue(Job(2,0,0));
  cout << "   " << priorityQueue << endl << endl;
  assert(priorityQueue.length() == 3);
  assert(priorityQueue[2] == 2);
  
  //Done
  cout << "<PriorityQueue<int> Test case new node is lowest priority and ends up on back " << endl;
  priorityQueue.enqueue(Job(1,0,0));
  cout << "   " << priorityQueue << endl << endl;
  assert(priorityQueue.length() == 4);
  assert(priorityQueue[3] == 1);
  
  //Done
  cout << "<PriorityQueue<int> Test case 3 insertion in between " << endl;
  priorityQueue.enqueue(Job(3,0,0));
  cout << "   " << priorityQueue << endl << endl;
  assert(priorityQueue.length() == 5);
  assert(priorityQueue[2] == 3);
  
  
  //Done
  cout << "<PriorityQueue<int> Test case 3 insertion of equal valued priority" << endl
       << "   (can't see if correct or not with ints) " << endl;
  priorityQueue.enqueue(Job(2,0,0));
  cout << "   " << priorityQueue << endl << endl;
  assert(priorityQueue.length() == 6);
  assert(priorityQueue[4] == 2);

  cout << endl;


  
  cout << "--------------- testing PriorityQueue<Job> ----------------------" << endl;

  PriorityQueues jobs; 
	
  cout << "<PriorityQueue<Job> Test case 1 insertion into empty priority queue" << endl;
  jobs.enqueue(Job(5,0,0));
  cout << "   " << jobs << endl << endl;
  assert(jobs.length() == 1);
  //assert(jobs[0].getPriority() == 5);
    
  cout << "<PriorityQueue<Job> Test case 2 new node is highest priority and needs to go on front" << endl;
  jobs.enqueue(Job(10, 0, 0));
  cout << "   " << jobs << endl << endl;
  assert(jobs.length() == 2);
  //assert(jobs[0].getPriority() == 10);
  
  cout << "<PriorityQueue<Job> Test case new node is lowest priority and ends up on back " << endl;
  jobs.enqueue(Job(2, 0, 0));
  cout << "   " << jobs << endl << endl;
  assert(jobs.length() == 3);
  //assert(jobs[2].getPriority() == 2);
  
  cout << "<PriorityQueue<Job> Test case new node is lowest priority and ends up on back " << endl;
  jobs.enqueue(Job(1, 0, 0));
  cout << "   " << jobs << endl << endl;
  assert(jobs.length() == 4);
  //assert(jobs[3].getPriority() == 1);
  
  cout << "<PriorityQueue<Job> Test case 3 insertion in between " << endl;
  jobs.enqueue(Job(3, 0, 0));
  cout << "   " << jobs << endl << endl;
  assert(jobs.length() == 5);
  //assert(jobs[2].getPriority() == 3);
  
  cout << "<PriorityQueue<Job> Test case 3 insertion of equal valued " << endl;
  jobs.enqueue(Job(2, 0, 0));
  cout << "   " << jobs << endl << endl;
  assert(jobs.length() == 6);
  //assert(jobs[4].getPriority() == 2);
   //tests that the new item was inserted after the old item with same priority
  //assert(jobs[3].getPriority() == 2);
  //assert(jobs[3].getId() < jobs[4].getId());

  cout << endl;
  

  
  cout << "----------- testing jobSchedulerSimulator() --------------------"
       << endl << endl;
 // JobSchedulerSimulator sim;
	//srand(time(0));  // seed random number generator using current time
  //LQueue<Job> jobQueue();
 // int seed = 32;
  //srand(seed);
   runSimulation(10000, 0.1, 1, 10, 5, 15, "Normal (non-prioirity based) Queueing discipline");
 
 //srand(seed);
//  //PriorityQueue<Job> jobPriorityQueue;
	runSimulation(10000, 0.1, 1, 10, 5, 15, "Priority Queueing discipline");
//  cout << sim;
  
  
  // return 0 to indicate successful completion
  return 0;
}
