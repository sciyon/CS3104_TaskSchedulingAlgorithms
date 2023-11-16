#include "process_management.h"

using namespace std;


//Function that will find process with smallest arrival time among available processes
int findNextProcessByArrivalTime(const vector<Process>& processes, int currentTime) 
{
   int nextProcess = -1;
   int smallestArrivalTime = INT_MAX;

   for(unsigned p = 0; p < processes.size(); p++) {
       // Check if the process has arrived and it has remaining work to be done
       if(processes[p].arrivalTime <= currentTime && processes[p].remainingBurstTime > 0) {
           // Check if the current process has an earlier arrival time
           if(processes[p].arrivalTime < smallestArrivalTime) {
               // Update the next process if an earlier arrival time is found
               nextProcess = p;
               smallestArrivalTime = processes[p].arrivalTime; // Update the smallest arrival time
           }
       }
   }

   return nextProcess;
}

// Function to find the process with the shortest remaining burst time among available processes
int findShortestRemainingTimeProcess(const vector<Process>& processes, int currentTime) 
{
    int shortestTime = INT_MAX;
    int nextProcess = -1;

    for(unsigned p = 0; p < processes.size(); p++) {
    	// Check if the process has arrived, its remaining burst time is shorter, and it has remaining work to be done
        if(processes[p].arrivalTime <= currentTime && processes[p].remainingBurstTime < shortestTime &&
		    processes[p].remainingBurstTime > 0) {
		    
		    // Check if the current process has a shorter burst time or if its arrival time is lower
		    if(processes[p].remainingBurstTime < shortestTime ||
		        (processes[p].remainingBurstTime == shortestTime && 
		        processes[p].arrivalTime < processes[nextProcess].arrivalTime)) {
		        
		        // Update the next process if a shorter burst time or lower arrival time is found
		        nextProcess = p;
		        shortestTime = processes[p].remainingBurstTime; // Update the shortest remaining burst time
		    }
		}
    }

    return nextProcess;
}

// Function to find the process with the highest priority among available processes
int findHighestPriorityProcess(const vector<Process>& processes, int currentTime)
{
	int highestPriority = INT_MAX;
	int nextProcess = -1;
	
	for(unsigned p = 0; p < processes.size(); p++) {
		// Check if the process has arrived, its priority is higher, and it has remaining work to be done
		if(processes[p].arrivalTime <= currentTime && processes[p].prioNum <= highestPriority &&
			processes[p].remainingBurstTime > 0) {
				
				// Check if the current process has a higher priority or if its burst time is lower and its arrival time is lower
				if(processes[p].prioNum < highestPriority ||
					(processes[p].prioNum == highestPriority &&
					processes[p].remainingBurstTime < processes[nextProcess].remainingBurstTime &&
					processes[p].arrivalTime < processes[nextProcess].arrivalTime)) {
						
						// Update the next process
						nextProcess = p;
						highestPriority = processes[p].prioNum;
					}
			}
	}
	
	return nextProcess;
}


// Function to handle the case when no process is ready to execute
void handleIdleTime(vector<Process>& processes, vector<pair<char, int>>& ganttChart, unsigned& currentTime) 
{
    int nextProcess = -1;

    // Finds the first process closest to the current time
    for(unsigned p = 0; p < processes.size(); p++) {
        if(processes[p].remainingBurstTime > 0) {
            if(nextProcess == -1 || processes[p].arrivalTime < processes[nextProcess].arrivalTime) {
                nextProcess = p;
            }
        }
    }
    ganttChart.push_back({'?', processes[nextProcess].arrivalTime - currentTime}); // Add an idle unit to the Gantt chart
    currentTime = processes[nextProcess].arrivalTime; // Jump to the arrival time of the next process
}
