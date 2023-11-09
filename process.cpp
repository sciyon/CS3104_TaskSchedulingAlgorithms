#include "process.h"

using namespace std;

void initTable(int numProcesses, vector<Process>& processes) 
{
    // Shows and updates the table while inputting the values for arrival time and burst time
    for(int p = 0; p < numProcesses; p++) {
        system("cls");
        printTable(processes);
        
        // Input values for arrival time and burst time
        cout << "P" << p + 1 << ": Enter Arrival and Burst time: ";
        cin >> processes[p].arrivalTime >> processes[p].burstTime;
        processes[p].remainingBurstTime = processes[p].burstTime; // Initialize remaining burst time
    }

    system("cls");
    printTable(processes);
}

void printTable(vector<Process>& processes) 
{
    for (int p = 0; p < processes.size(); p++) {
        char label = 'A' + p;
        processes[p].label = label; // Set the process labels
    }

    cout << setw(10) << "Process" << std::setw(15) << "Arrival Time" << std::setw(15) << "Burst Time" << std::endl;
    for (const Process& process : processes) {
        cout << setw(10) << process.label << setw(15) << process.arrivalTime << setw(15) << process.burstTime << endl;
    }
}


void printResultTable(const vector<Process>& processes) 
{
    cout << "\nResult Table:\n";
    cout << setw(10) << "Process" << setw(15) << "Arrival Time" << setw(15) << "Burst Time"
         << setw(15) << "End Time" << setw(17) << "Turnaround Time" << setw(15) << "Wait Time" << endl;

    for (const Process& process : processes) {
        cout << setw(10) << process.label << setw(15) << process.arrivalTime << setw(15) << process.burstTime
             << setw(15) << process.endTime << setw(17) << process.turnaroundTime << setw(15) << process.waitTime << endl;
    }
}

bool compareProcesses(const Process& a, const Process& b) 
{
    return a.label < b.label;
}

// Function to find the process with the shortest remaining burst time among available processes
int findShortestRemainingTimeProcess(const vector<Process>& processes, int currentTime) 
{
    int shortestTime = INT_MAX;
    int nextProcess = -1;

    for (unsigned p = 0; p < processes.size(); p++) {
    	// Check if the process has arrived, its remaining burst time is shorter, and it has remaining work to be done
        if (processes[p].arrivalTime <= currentTime && processes[p].remainingBurstTime < shortestTime &&
		    processes[p].remainingBurstTime > 0) {
		    
		    // Check if the current process has a shorter burst time or if its arrival time is lower
		    if (processes[p].remainingBurstTime < shortestTime ||
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
