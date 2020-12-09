/** 

 * @description Assignment 11 Priority queues and scheduling
 *   simulation of jobs with priorities.
 */
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include "JobSimulator.hpp"
#include "Queue.hpp"
#include "JobSimulator.cpp"
#include "Queue.cpp"
#include "assg-11.cpp"
using namespace std;



//-------------------------------------------------------------------------
/**
 * A constant for the Job class, used to keep track of
 * and assign unique id's for each job created.
 */
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
/** random uniform
 * Return a random floating point value in the range of [0.0, 1.0] with
 * uniform probability of any value in the range being returned.
 * The algorithm is that rand() returns an int in range [0, RAND_MAX]
 * and doing floating point division on the random integer by 
 * RAND_MAX recasts the result into a floating point number in range
 * [0.0, 1.0].
 *
 * @returns double Returns a randomly generated double valued number
 *   with uniform probability in the range [0.0, 1.0]
 */
double JobSchedulerSimulator::randomUniform()
{
  double randValue = double(rand()) / double(RAND_MAX);
  return randValue;
}


/** random range
 * Generate a random ingeger number in the given range from [minValue to
 * maxValue].  We are given minValue and maxValue, a random integer is
 * generated (with uniform probability) that is between minValue and
 * maxValue (inclusive, so minValue or maxValue are valid results
 * that can be returned, or any integer in between).
 *
 * @param minValue The minimum value of the range of integers to generate.
 * @param maxValue The maximum of the range of integers to generate.
 *
 * @returns int Returns a random integer value in range [minValue,
 *   maxValue] inclusive of the end points.
 */
int JobSchedulerSimulator::randomRange(int minValue, int maxValue)
{
  // the range is difference between desired max and min.  We need
  // this magnitude in order to correctly generate a random value in
  // the given range
  int range = maxValue - minValue + 1;

  // generate a random value in range 0 to range (inclusive)
  int randValue = rand() % range;

  // shift the value so it is in range [minValue, maxValue]
  randValue += minValue;

  return randValue;
}


/** job arrived
 * Test if a job arrived.  We use a poisson distribution to generate
 * a boolean result of true, a new job arrived in this time period,
 * or false, a new job did not arrive.  A Poisson distribution is often
 * a good model of discrete arrivals of jobs or customers in a system.
 * See Malik Ch. 18, pg. 1233 for description of the poisson arrival
 * calculation here.
 *
 * @param none, but we use the class simulation parameter
 *   jobArrivalProbability to determine if a new job arrived
 *   using a Poisson distribution.  The jobArrivalProbability
 *   is the probability of an arrival during a time period (lambda).
 *
 * @returns bool True if a new job arrived according to random check,
 *   false otherwise. 
 */
bool JobSchedulerSimulator::jobArrived()
{
  // if a random uniform value in range [0.0, 1.0] is greater than
  // e^(-arrivalProbability), then a job has arrived according to
  // the poisson distribution
  return randomUniform() > exp(-jobArrivalProbability);
}


/** generate priority
 * Generate a random priority within the given range of the
 * simulation parameters [minPriority, maxPriority] inclusive.
 *
 * @param none, but minPriority and maxPriority simulation
 *   parameters are used in this function to randomly select
 *   a priority for a Job in the given range.
 *
 * @returns int A random priority in the range [minPriority, maxPriority]
 *   using the current settings of the simulation parameters.
 */
int JobSchedulerSimulator::generateRandomPriority()
{
  return randomRange(minPriority, maxPriority);
}


/** generate service time
 * Generate a random job service time within the given range of the
 * simulation parameters [minServiceTime, maxServiceTime] inclusive.
 *
 * @param none, but minServiceTime and maxServiceTime simulation
 *   parameters are used in this function to randomly select a
 *   service time for a Job in the given range.
 *
 * @returns int A random serviceTime in the range [minServiceTime,
 *   maxServiceTime] using the current settings of the simulation
 *   parameters.
 */
int JobSchedulerSimulator::generateRandomServiceTime()
{
  return randomRange(minServiceTime, maxServiceTime);
}

JobSchedulerSimulator::JobSchedulerSimulator(){
}

/** simulator constructor
 * Mostly just a constructor to allow all of the simulation parameters
 * to be set to initial values when a simulation is created.  All of these
 * simulation parameters have default values specified for a standard
 * job simulation.  All simulation result member values are initialized
 * to 0 or null values in preparation for a simulation run.
 */
//JobSchedulerSimulator::JobSchedulerSimulator(int simulationTime,
//					     double jobArrivalProbability,
//					     int minPriority,
//					     int maxPriority,
//					     int minServiceTime,
//					     int maxServiceTime)
//{
//  // initialize/remember the simulation parameters
//  this->simulationTime = simulationTime;
//  this->jobArrivalProbability = jobArrivalProbability;
//  this->minPriority = minPriority;
//  this->maxPriority = maxPriority;
//  this->minServiceTime = minServiceTime;
//  this->maxServiceTime= maxServiceTime;
//
//  // initialize simulation results to 0, ready to be calculated
//  this->description = "";
//  this->numJobsStarted = 0;
//  this->numJobsCompleted = 0;
//  this->numJobsUnfinished = 0;
//  this->totalWaitTime = 0;
//  this->totalCost = 0;
//  this->averageWaitTime = 0.0;
//  this->averageCost = 0.0;
//}



/** summary results
 * Convenience methods for creating a string for display listing
 * all of the simulation parameters, and all of the simulation
 * results.  Mostly useful after a simulation has just completed,
 * to get a summary of the simulation results for the given
 * simulation parameters.
 *
 * @returns string This method constructs and returns a string
 *   with a summary of the current simulation parameter settings
 *   and a summary of the simulation results.
 */
string JobSchedulerSimulator::summaryResultString()
{
  ostringstream out;

  out << "Job Scheduler Simulation Results" << endl
      << "--------------------------------" << endl
      << "Simulation Parameters" << endl
      << "--------------------------" << endl
      << "Description              : " << description << endl
      << "Simulation Time          : " << simulationTime << endl
      << "Job Arrival Probability  : " << jobArrivalProbability << endl
      << "Priority (min,max)       : (" << minPriority << ", " << maxPriority << ")" << endl
      << "Service Time (min,max)   : (" << minServiceTime << ", " << maxServiceTime << ")" << endl << endl
      << "Simulation Results" << endl
      << "--------------------------" << endl
      << "Number of jobs started   : " << numJobsStarted << endl
      << "Number of jobs completed : " << numJobsCompleted << endl
      << "Number of jobs unfinished: " << numJobsUnfinished << endl
      << "Total Wait Time          : " << totalWaitTime << endl
      << "Total Cost               : " << totalCost << endl
      << "Average Wait Time        : " << setprecision(4) << fixed << averageWaitTime << endl
      << "Average Cost             : " << setprecision(4) << fixed << averageCost << endl
      << endl << endl;

    return out.str();
}


/** csv results
 * A method for outputing the simulation results as a string of
 * comma separated values (csv).  This method is useful for generating
 * data about large numbers of simulations for later analysis.
 *
 * @returns string This method constructs and returns a string
 *   of comma separated values (csv) of current simulation results,
 *   suitable for constructing a x.csv file for data analysis.
 */
string JobSchedulerSimulator::csvResultString()
{
  ostringstream out;
  out << numJobsStarted << ","
      << numJobsCompleted << ","
      << numJobsUnfinished << ","
      << totalWaitTime << ","
      << totalCost << ","
      << setprecision(4) << fixed << averageWaitTime << ","
      << setprecision(4) << fixed << averageCost << endl;
  return out.str();
}


/** overload output stream operator
 * Overload the output stream operator for convenience so we can
 * output a simulation object directly to an output stream.
 *
 * @param out A reference to the output stream we are sending our
 *   output to.
 * @param sim The JobSchedulerSimulator object we are outputing 
 *   the values of.  This is a friend funciton of the class, so
 *   the object is given as second parameter of this binary operator.
 *
 * @returns ostream Returns the given output stream object, but after
 *   we have inserted the output representation of the sim into it.
 */
ostream& operator<<(ostream& out, JobSchedulerSimulator& sim)
{
  out << sim.summaryResultString();
  return out;
}

// Assignment 11
// You need to add the implementation of your runSimulation()
// method, as described in the assignment, here.

