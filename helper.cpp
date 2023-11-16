#include "helper.h"

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

void initTablePrio(int numProcesses, vector<Process>& processes) 
{
    // Shows and updates the table while inputting the values for arrival time and burst time
    for(int p = 0; p < numProcesses; p++) {
        system("cls");
        printTablePrio(processes);
        
        // Input values for arrival time and burst time
        cout << "P" << p + 1 << ": Enter Arrival time, Burst time and Priority number: ";
        cin >> processes[p].arrivalTime >> processes[p].burstTime >> processes[p].prioNum;
        processes[p].remainingBurstTime = processes[p].burstTime; // Initialize remaining burst time
    }

    system("cls");
    printTablePrio(processes);
}

int initTableRR(int numProcesses, vector<Process>& processes) 
{
	int timeQuant;
	
	cout << "Time Quantum: ";
	cin >> timeQuant;
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
    printTableMLQ(processes);
    
    return timeQuant;
}


void initTableMLQ(int numProcesses, vector<Process>& processes, vector<int>& mlq) 
{ 

	int x;
	cout << "Input # for Algorithm:\n";
	cout << "      1  -  FCFS:\n";
	cout << "      2  -  SJF:\n";
	cout << "      3  -  NPP:\n";
	cout << "      4  -  PP:\n";
	cout << "      5  -  RR:\n";
	cout << "      6  -  SRTF:\n";
	cout << "Process 1: ";
        cin >> x;
        mlq.push_back(x);
	cout << "Process 1 Priority: ";
        cin >> x;
        mlq.push_back(x);
	cout << "Process 2: ";
        cin >> x;
        mlq.push_back(x);
	cout << "Process 2 Priority: ";
        cin >> x;
        mlq.push_back(x);
	
	//If any of the processes are RR
	if(mlq[2] ==  5){
		cout << "Input quantum time for Algo 1 RR:";
        cin >> x;
        mlq.push_back(x);
	}
	if(mlq[3] ==  5){
		cout << "Input quantum time for Algo 2 RR:";
        cin >> x;
        mlq.push_back(x);
	}
	
	
	
    // Shows and updates the table while inputting the values for arrival time and burst time
    for(int p = 0; p < numProcesses; p++) {
        system("cls");
        printTable(processes);
        
        // Input values for arrival time and burst time
        cout << "P" << p + 1 << ": Enter Arrival,  Burst time, Priority Number, and Queue Level: ";
        cin >> processes[p].arrivalTime >> processes[p].burstTime >> processes[p].prioNum >> processes[p].queueLevel;
        processes[p].remainingBurstTime = processes[p].burstTime; // Initialize remaining burst time
    }

    system("cls");
    printTable(processes);
}


void initTableMLFQ(int numProcesses, vector<Process>& processes, vector<int>& mlfq) 
{ 
	int x;
	cout << "Input # for Algorithm:\n";
	cout << "      1  -  FCFS:\n";
	cout << "      2  -  SJF:\n";
	cout << "      3  -  NPP:\n";
	cout << "      4  -  PP:\n";
	cout << "      5  -  RR:\n";
	cout << "      6  -  SRTF:\n";
	cout << "Algo 1: ";
        cin >> x;
        mlfq.push_back(x);
	cout << "Algo 2: ";
        cin >> x;
        mlfq.push_back(x);
	cout << "Algo 3: ";
        cin >> x;
        mlfq.push_back(x);
	
	//If any of the processes are RR
	if(mlfq[0] ==  5){
		cout << "Input quantum time for Algo 1 RR:";
        cin >> x;
        mlfq.push_back(x);
	}
	if(mlfq[1] ==  5){
		cout << "Input quantum time for Algo 2 RR:";
        cin >> x;
        mlfq.push_back(x);
	}
	if(mlfq[3] ==  5){
		cout << "Input quantum time for Algo 3 RR:";
        cin >> x;
        mlfq.push_back(x);
	}
	
	
	
    // Shows and updates the table while inputting the values for arrival time and burst time
    for(int p = 0; p < numProcesses; p++) {
        system("cls");
        printTable(processes);
        
        // Input values for arrival time and burst time
        cout << "P" << p + 1 << ": Enter Arrival,  Burst time:";
        cin >> processes[p].arrivalTime >> processes[p].burstTime;
        processes[p].remainingBurstTime = processes[p].burstTime; // Initialize remaining burst time
    }

    system("cls");
    printTable(processes);
}


void printTable(vector<Process>& processes) 
{
    for(int p = 0; p < processes.size(); p++) {
        char label = 'A' + p;
        processes[p].label = label; // Set the process labels
    }

    cout << setw(10) << "Process" << std::setw(15) << "Arrival Time" << std::setw(15) << "Burst Time" << std::endl;
    for(const Process& process : processes) {
        cout << setw(10) << process.label << setw(15) << process.arrivalTime << setw(15) << process.burstTime << endl;
    }
}


void printTableMLQ(vector<Process>& processes) 
{
    for(int p = 0; p < processes.size(); p++) {
        char label = 'A' + p;
        processes[p].label = label; // Set the process labels
    }

    cout << setw(10) << "Process" << std::setw(15) << "Arrival Time" << std::setw(15) << "Burst Time" << std::setw(15) << "Priority Number" << std::setw(15) << "Queue Level" << std::endl;
    for(const Process& process : processes) {
        cout << setw(10) << process.label << setw(15) << process.arrivalTime << setw(15) << process.burstTime  << process.prioNum << setw(15) << process.queueLevel << setw(15)<< endl;
    }
}

void printTablePrio(vector<Process>& processes) 
{
    for(int p = 0; p < processes.size(); p++) {
        char label = 'A' + p;
        processes[p].label = label; // Set the process labels
    }

    cout << setw(10) << "Process" << std::setw(15) << "Arrival Time" << std::setw(15) << "Burst Time" << std::setw(15) << "Priority Number" << std::endl;
    for(const Process& process : processes) {
        cout << setw(10) << process.label << setw(15) << process.arrivalTime << setw(15) << process.burstTime << setw(15) << process.prioNum << endl;
    }
}

void printResultTable(const vector<Process>& processes) 
{
    cout << "\nResult Table:\n";
    cout << setw(10) << "Process" << setw(15) << "Arrival Time" << setw(15) << "Burst Time"
         << setw(15) << "End Time" << setw(17) << "Turnaround Time" << setw(15) << "Wait Time" << endl;

    for(const Process& process : processes) {
        cout << setw(10) << process.label << setw(15) << process.arrivalTime << setw(15) << process.burstTime
             << setw(15) << process.endTime << setw(17) << process.turnaroundTime << setw(15) << process.waitTime << endl;
    }
}

void printResultTablePrio(const vector<Process>& processes) 
{
    cout << "\nResult Table:\n";
    cout << setw(10) << "Process" << setw(15) << "Arrival Time" << setw(15) << "Burst Time" << setw(15) << "Priority"
         << setw(15) << "End Time" << setw(17) << "Turnaround Time" << setw(15) << "Wait Time" << endl;

    for(const Process& process : processes) {
        cout << setw(10) << process.label << setw(15) << process.arrivalTime << setw(15) << process.burstTime << setw(15) << process.prioNum
             << setw(15) << process.endTime << setw(17) << process.turnaroundTime << setw(15) << process.waitTime << endl;
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
