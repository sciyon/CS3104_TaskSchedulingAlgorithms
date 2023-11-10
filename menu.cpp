#include "menu.h"
#include "process_management.h"
#include "scheduler.h"
#include "helper.h"

using namespace std;

void menu() 
{
    int selection;
    bool exit = false;

    while(!exit) {
        displayMenu();
        selection = getUserChoice();
        
        switch (selection) {
            case SJF_OPTION:
            case PPB_OPTION:
            case SRTF_OPTION:
            case MLFQ_OPTION:
                run(selection);
                break;
            case EXIT_OPTION:
                exit = true;
                break;
            default:
                cout << "\nERROR: Invalid value. Please enter again." << endl;
                break;
        }
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
	vector<pair<char, int>> ganttChart;    
    
    switch(option) {
    	case 1:
    		initTable(numProcesses, processes);
    		SJF(processes, ganttChart);
    		printGanttChart(ganttChart);
    		printResultTable(processes);
    		break;
    	case 2:
    		initTablePrio(numProcesses, processes);
    		PPB(processes, ganttChart);
    		printGanttChart(ganttChart);
    		printResultTablePrio(processes);
    		break;
    	case 3:
    		initTable(numProcesses, processes);
    		SRTF(processes, ganttChart);
    		printGanttChart(ganttChart);
    		printResultTable(processes);
    		break;
    	case 4:
    		// MLFQ(processes, ganttChart);
    		break;
	}
    
    system("pause");
}

void displayMenu() 
{
    cout << "-----------------------------------------" << endl;
    cout << "|       CPU Scheduling Algorithms       |" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "|   1. Shortest Job First               |" << endl;
    cout << "|   2. Preemptive Priority Based        |" << endl;
    cout << "|   3. Shortest Remaining Time First    |" << endl;
    cout << "|   4. Multilevel Feedback Queue        |" << endl;
    cout << "|   5. Exit                             |" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "\nEnter a selection: ";
}

int getUserChoice() 
{
    int selection;

    cin >> selection;
    system("cls");

    return selection;
}
