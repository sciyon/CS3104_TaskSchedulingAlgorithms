#include "scheduler.h"
#include "process.h"

using namespace std;

void menu() 
{
    int selection;
    bool exit = false;

    while (!exit) {
        cout << "-----------------------------------------" << endl;
        cout << "|               Algorithms              |" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "|   1. Shortest Job First               |" << endl;
        cout << "|   2. Priority Based                   |" << endl;
        cout << "|   3. Shortest Remaining Time First    |" << endl;
        cout << "|   4. Multilevel Feedback Queue        |" << endl;
        cout << "|   5. Exit                             |" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "\nEnter a selection: ";
        cin.clear();
        cin >> selection;


        if(selection > 0 && selection < 5) {
        	run(selection);  	
		} else if(selection == 5) {
			exit = true;
		} else {
			cout << "\nERROR: Invalid value. Please enter again." << endl;
			system("pause");
		}
		system("cls");
        cin.clear();
    }
}

void run(int option)
{
	system("cls");

    int numProcesses;
    cout << "How many processes? ";
    cin >> numProcesses;

    if(numProcesses <= 0) {
        cout << "Invalid number of processes" << endl;
        return;
    }
    
    vector<Process> processes(numProcesses);

    // Initialize the process arrival, burst time, and labels
    initTable(numProcesses, processes);

    vector<pair<char, int>> ganttChart;
    
    switch(option) {
    	case 1:
    		SJF(processes, ganttChart);
    		break;
    	case 2:
    		// PP(processes, ganttChart);
    		break;
    	case 3:
    		SRTF(processes, ganttChart);
    		break;
    	case 4:
    		// MLFQ(processes, ganttChart);
    		break;
	}

    // Print the Gantt chart and result table
    printGanttChart(ganttChart);
    printResultTable(processes);

    system("pause");
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

            //  If process has completed execution
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

void printGanttChart(const vector<pair<char, int>>& ganttChart) 
{
    cout << "\nGantt Chart:\n|";
    char currentLabel = ' ';
    int cumulativeDuration = 0;
    for (const auto& entry : ganttChart) {
        if (entry.first != currentLabel) {
            if (currentLabel != ' ') {
                cout << "(" << currentLabel << " " << cumulativeDuration << ") | ";
            }
            currentLabel = entry.first;
        }
        cumulativeDuration += entry.second;
    }
    cout << "(" << currentLabel << " " << cumulativeDuration << ") |" << endl;
}
