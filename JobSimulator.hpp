/** 

 * 
 * @description Assignment 11 Priority queues and scheduling
 *   simulation of jobs with priorities.
 */

#include<iostream>
using namespace std;
#ifndef JOBSIMULATOR_HPP
#define JOBSIMULATOR_HPP


/** Job class
 * Class for job scheduling simulation.  A Job enters a system
 * at random intervals (determined by the JobSchedulerSimulator on
 * a random Poisson basis).  A job has a priority level and a serviceTime
 * which is the amount of system time it needs in order to complete
 * it task.  The main property to keep track of for jobs in a
 * simulation is how long they have to wait before they are selected
 * to be processed/run by the system.  Jobs keep track of their cost,
 * which can be used to measure a particular system's performance
 * (lower costs mean the system performed well, higher costs mean the
 * system performed more poorly).  For systems with priority based jobs,
 * the measure of the cost is determined of the function a job spent
 * waiting, and how high of a priority the job had.  We use the
 * simple calculation of cost = priority * waitTime to calculate
 * the cost for a job once it completes.
 *
 * @var nextListId A static int variable, used to assign unique ids
 *   when processes are created, for identification purposes.
 * @var id The actual unique id assigned to a job object.
 * @var priority This jobs priority level.  Higher numbers mean higher
 *   priority jobs in this simulation.
 * @var serviceTime The amount of system time this job needs in order to
 *   complete its task.
 * @var startTime The time when the job was created.  Also the time
 *   when the job began waiting in a queue to be selected to run.
 * @var endTime The time when the job finished waiting (when it was
 *   finally selected by the system to begin execution).  The difference
 *   between endTime - startTime determines the total waitTime for this
 *   process (calculated by getWaitTime() accessor method).
 */



/** JobSchedulerSimulator
 * This class organizes and executes simulations of job scheduling, using
 * different scheduling methods.  The simulations are goverend by a number
 * of system parameters, that are specified when a simulation is created.
 * When a simulation is run, various data is gathered that describes the
 * results of the simulation.  In general, the job scheduling being
 * simulated is simple.  The system runs for discrete time steps (total
 * number of which is goverened by simulationTime parameter).  At each step
 * we check for and simulate new job arrivals.  When jobs arrive, they
 * are placed on a single job queue.  We then check if the processor/executor
 * is busy or not, and if not and if the job queue has some jobs on it, we
 * simulate dispatching a job.  Differences in how jobs are organized on
 * a queue, and their effects on system performance (as a function of
 * total or average cost) can be explored with this simulator.
 *
 * These are parameters of the simulation, they govern properties of
 * job arrivals and characteristics when a simulation is run:
 *
 * @var simulatTime The total number of time steps a simulation will
 *   run.  Time steps will run from 1..simulationTime number of
 *   discrete steps.
 * @var jobArrivalProbability The Poisson probability that a job will
 *   arrive any any given discrete time interval.  This governs how
 *   often new jobs arrive and are created in the simulation.
 * @var [minPriority, maxPriority] The range of Job priority levels
 *   for jobs that arrive.  This simulation generates priorities for
 *   the jobs randomly with uniform probability within this range, and
 *   assigns them to new jobs that arrive.
 * @var [minServiceTime, maxServiceTime] The range of Job serviceTimes
 *   for jobs that arrive in the system simulation.  Service times are how
 *   long a job needs to execute, once it is selected to be processed.
 *   Service times are generated with uniform probability in this
 *   given range when new jobs arrive.
 *
 * These are resulting statistics of a simultion.  While a simulation is
 * being run, data is gathered about various performance characteristics, like
 * wait times and costs.  At the end of a simulation, these statistical results
 * are available for analysis of the system preformance.
 * 
 * @var description A description of the dispatching/queueing method used.
 * @var numJobsStarted The new number of jobs that entered and were
 *   started during the most recent simulation run.
 * @var numJobsCompleted The number of jobs that were successfully run during
 *   a simulation.
 * @var numJobsUnfinished The number of jobs left in the waiting queues when
 *   a simulation finished.
 * @var totalWaitTime The total amount of time spent waiting by jobs
 *   that completed in the simulation.  Mainly useful for calculating
 *   the averageWaitTime.
 * @var totalCost The total cost of all jobs that completed in the simulation.
 *   Also mainly useful for calculating averageCost statistic.
 * @var averageWaitTime The average waiting time for completed jobs of the
 *   most recent simulation.
 * @var averageCost The average system cost for completed jobs of the most
 *   recent simulation.
 */
struct JobSchedulerSimulator
{
private:
  // simulation parameters
  int simulationTime;
  double jobArrivalProbability;
  int minPriority;
  int maxPriority;
  int minServiceTime;
  int maxServiceTime;

  // simulation results
  string description;
  int numJobsStarted;
  int numJobsCompleted;
  int numJobsUnfinished;
  int totalWaitTime;
  int totalCost;
  double averageWaitTime;
  double averageCost;

  // private functions to support runSimulation(), mostly
  // for generating random times, priorities and poisson arrivals
  double randomUniform();
  int randomRange(int minValue, int maxValue);
  bool jobArrived();
  int generateRandomPriority();
  int generateRandomServiceTime();
  
public:
JobSchedulerSimulator();
 // JobSchedulerSimulator(int simulationTime = 10000,
	//		double jobArrivalProbability = 0.1,
		//	int minPriority = 1,
			//int maxPriority = 10,
//			int minServiceTime = 5,
	//		int maxServiceTime = 15);
  
  string summaryResultString();
  string csvResultString();

  // Assignment 11
  // You need to add a new method to the class definition of the
  // JobSchedulerSimulator named runSimulation() here.
  void runSimulation();
  friend ostream& operator<<(ostream& out, JobSchedulerSimulator& sim);
};




#endif
