#include "menu.h"
#include "scheduler.h"
#include "process_management.h"
#include "helper.h"

using namespace std;

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
    		if (processes[nextProcess].remainingBurstTime == 0) {
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


