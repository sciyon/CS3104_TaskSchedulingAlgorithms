#include "menu.h"
#include "scheduler.h"
#include "process_management.h"
#include "helper.h"

using namespace std;

//First Come First Serve (FCFS) Algorithm
void FCFS(vector<Process>& processes, vector<pair<char, int>>& ganttChart) 
{
    unsigned currentTime = 0;
    unsigned completedProcesses = 0;
	
    while(completedProcesses < processes.size()) {
    	// Find the next process with the shortest remaining burst time among available processes
        int nextProcess = findNextProcessByArrivalTime(processes, currentTime);

        // If a process has been found
        if(nextProcess != -1) {
            // Add the executed process to the Gantt chart
            ganttChart.push_back({processes[nextProcess].label, processes[nextProcess].remainingBurstTime});
            currentTime += processes[nextProcess].remainingBurstTime; // Update the current time
            processes[nextProcess].remainingBurstTime = 0; // Mark the process as completed

            completedProcesses++; // Increment the count of completed processes

            // Records and calculates the rest of the information
            processes[nextProcess].endTime = currentTime;
            processes[nextProcess].turnaroundTime = processes[nextProcess].endTime - processes[nextProcess].arrivalTime;
            processes[nextProcess].waitTime = processes[nextProcess].turnaroundTime - processes[nextProcess].burstTime;
        }
        
        // If no process is ready to execute
		else {
			// Find the next available process with the highest priority (i.e., the earliest arrival time)
        	handleIdleTime(processes, ganttChart, currentTime);
		}
    }
}

// Shortest Job First (SJF) Algorithm
void SJF(vector<Process>& processes, vector<pair<char, int>>& ganttChart) 
{
    unsigned currentTime = 0;
    unsigned completedProcesses = 0;

    while(completedProcesses < processes.size()) {
    	// Find the next process with the shortest remaining burst time among available processes
        int nextProcess = findShortestRemainingTimeProcess(processes, currentTime);

        // If a process has been found
        if(nextProcess != -1) {
            // Add the executed process to the Gantt chart
            ganttChart.push_back({processes[nextProcess].label, processes[nextProcess].remainingBurstTime});
            currentTime += processes[nextProcess].remainingBurstTime; // Update the current time
            processes[nextProcess].remainingBurstTime = 0; // Mark the process as completed

            completedProcesses++; // Increment the count of completed processes

            // Records and calculates the rest of the information
            processes[nextProcess].endTime = currentTime;
            processes[nextProcess].turnaroundTime = processes[nextProcess].endTime - processes[nextProcess].arrivalTime;
            processes[nextProcess].waitTime = processes[nextProcess].turnaroundTime - processes[nextProcess].burstTime;
        }
        
        // If no process is ready to execute
		else {
			// Find the next available process with the highest priority (i.e., the earliest arrival time)
        	handleIdleTime(processes, ganttChart, currentTime);
		}
    }
}

// Non-preemptive Priority Based Scheduling Algorithm
void NPPB(vector<Process>& processes, vector<pair<char, int>>& ganttChart)
{
    unsigned currentTime = 0;
    unsigned completedProcesses = 0;
    
    while(completedProcesses < processes.size()) {
    	// Find the next process with the highest priority among available processes
    	int nextProcess = findHighestPriorityProcess(processes, currentTime);
    	
    	// If a process has been found
    	if(nextProcess != -1) {
    		ganttChart.push_back({processes[nextProcess].label, processes[nextProcess].remainingBurstTime});
            currentTime += processes[nextProcess].remainingBurstTime; // Update the current time
            processes[nextProcess].remainingBurstTime = 0; // Mark the process as completed

            completedProcesses++; // Increment the count of completed processes

            // Records and calculates the rest of the information
            processes[nextProcess].endTime = currentTime;
            processes[nextProcess].turnaroundTime = processes[nextProcess].endTime - processes[nextProcess].arrivalTime;
            processes[nextProcess].waitTime = processes[nextProcess].turnaroundTime - processes[nextProcess].burstTime;
		} 
		
		// If no process is ready to execute
		else {
			// Find the next available process with the highest priority (i.e., the earliest arrival time)
        	handleIdleTime(processes, ganttChart, currentTime);
		}
	}
}

// Preemptive Priority Based Scheduling Algorithm
void PPB(vector<Process>& processes, vector<pair<char, int>>& ganttChart)
{
    unsigned currentTime = 0;
    unsigned completedProcesses = 0;
    
    while(completedProcesses < processes.size()) {
    	// Find the next process with the highest priority among available processes
    	int nextProcess = findHighestPriorityProcess(processes, currentTime);
    	
    	// If a process has been found
    	if(nextProcess != -1) {
    		processes[nextProcess].remainingBurstTime--;
    		ganttChart.push_back({processes[nextProcess].label, 1});
    		currentTime++;
    		
    		// If process has completed execution
    		if(processes[nextProcess].remainingBurstTime == 0) {
    			completedProcesses++;
    			// Record and calculate information for the completed process
    			processes[nextProcess].endTime = currentTime;
                processes[nextProcess].turnaroundTime = processes[nextProcess].endTime - processes[nextProcess].arrivalTime;
                processes[nextProcess].waitTime = processes[nextProcess].turnaroundTime - processes[nextProcess].burstTime;
			}
		} 
		
		// If no process is ready to execute
		else {
			// Find the next available process with the highest priority (i.e., the earliest arrival time)
        	handleIdleTime(processes, ganttChart, currentTime);
		}
	}
}

bool isInQueue(std::queue<int>& processQueue, unsigned int value) {
   std::queue<int> tempQueue = processQueue;
   while (!tempQueue.empty()) {
       if (tempQueue.front() == value) {
           return true;
       }
       tempQueue.pop();
   }
   return false;
}

// Round Robin Algorithm
void RR(vector<Process>& processes, vector<pair<char, int>>& ganttChart, int timeQuantum) {
    queue<int> processQueue;  
    unsigned currentTime = 0; 
    unsigned completedProcesses = 0; 
		unsigned x = 0;
		
    while(completedProcesses < processes.size()) {
        // Search for first process with smallest arrival time
        for(unsigned p = 0; p < processes.size() && x == 0; p++) {
            if(processes[p].arrivalTime <= currentTime && processes[p].remainingBurstTime > 0) {
                processQueue.push(p);
            }
        }
        
        if(!processQueue.empty()) {
					x = 1;
				}else{
					x= 0;
				}
				
        // If there are processes in the queue, execute the next process
        if(!processQueue.empty()) {
          int currentProcess = processQueue.front();
          processQueue.pop();

          // Determine the execution time for the current process based on the time quantum
          int executionTime = min(timeQuantum, processes[currentProcess].remainingBurstTime);
          
					// Executes process incrementally
					for(int p = 0; p < executionTime; p++) {
						processes[currentProcess].remainingBurstTime--;
		    		ganttChart.push_back({processes[currentProcess].label, 1});
		    		currentTime++;
		    		// Check for arriving processes at currentTime increase
		    		for(unsigned q = 0; q < processes.size(); q++) {
	            if(q != currentProcess && !isInQueue(processQueue, q) && processes[q].arrivalTime <= currentTime && processes[q].remainingBurstTime > 0) {
	              processQueue.push(q);
	            }
			      }
					}
			
						// If process has completed execution
          if(processes[currentProcess].remainingBurstTime == 0) {
              completedProcesses++;
              processes[currentProcess].endTime = currentTime;
              processes[currentProcess].turnaroundTime = processes[currentProcess].endTime - processes[currentProcess].arrivalTime;
              processes[currentProcess].waitTime = processes[currentProcess].turnaroundTime - processes[currentProcess].burstTime;
          }else {// Else, add the process back to the queue if it has remaining burst time
              processQueue.push(currentProcess);  
          }
          
        }else {// If no process is ready to execute
            // Find the next available process with the highest priority (i.e., the earliest arrival time)
            handleIdleTime(processes, ganttChart, currentTime);
		    		currentTime++;
        }
    }
}



// Shortest Remaining Time First (SRTF) Scheduling Algorithm
void SRTF(vector<Process>& processes, vector<pair<char, int>>& ganttChart) 
{
    unsigned currentTime = 0;
    unsigned completedProcesses = 0;

    while(completedProcesses < processes.size()) {
    	// Find the next process with the shortest remaining burst time among available processes
        int nextProcess = findShortestRemainingTimeProcess(processes, currentTime);
		        
		// If a process has been found
		if(nextProcess != -1) {
            // Execute the next process for one time unit
            processes[nextProcess].remainingBurstTime--;
            ganttChart.push_back({processes[nextProcess].label, 1});
            currentTime++;

            // If process has completed execution
            if(processes[nextProcess].remainingBurstTime == 0) {
                completedProcesses++;
                // Record and calculate information for the completed process
                processes[nextProcess].endTime = currentTime;
                processes[nextProcess].turnaroundTime = processes[nextProcess].endTime - processes[nextProcess].arrivalTime;
                processes[nextProcess].waitTime = processes[nextProcess].turnaroundTime - processes[nextProcess].burstTime;
            }
        } 
        
		// If no process is ready to execute
		else {
			// Find the next available process with the highest priority (i.e., the earliest arrival time)
        	handleIdleTime(processes, ganttChart, currentTime);
		}
  }
}

void MLQ(vector<Process>& processes, vector<pair<char, int>>& ganttChart, vector<int>& mlq)
{
	unsigned int p1, p2, prioP1, prioP2, qTP1, qTP2;
	p1 = mlq[0];
	p2 = mlq[1];
	prioP1 = mlq[2];
	prioP2 = mlq[3];
	qTP1 = mlq[4];
	qTP2 = mlq[5];
	cout << "MLQ OUTPUT";
}
void MLQF(vector<Process>& processes, vector<pair<char, int>>& ganttChart, vector<int>& mlfq)
{
	unsigned int p1, p2, prioP1, prioP2, qTP1, qTP2;
	p1 = mlfq[0];
	p2 = mlfq[1];
	prioP1 = mlfq[2];
	prioP2 = mlfq[3];
	qTP1 = mlfq[4];
	qTP2 = mlfq[5];
	cout << "MLFQ OUTPUT";
}


