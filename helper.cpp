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