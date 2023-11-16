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
            case FCFS_OPTION:
            case SJF_OPTION :
            case NPPB_OPTION:
            case PPB_OPTION :
            case RR_OPTION:
            case SRTF_OPTION:
            case MLQ_OPTION :
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

    int numProcesses, timeQuant;
    cout << "How many processes? ";
    cin >> numProcesses;

    if(numProcesses <= 0) {
        cout << "Invalid number of processes" << endl;
        return;
    }
    
    vector<Process> processes(numProcesses);
		vector<pair<char, int>> ganttChart;    
    vector<int> mlq; 
    vector<int> mlfq;
    switch(option) {
    	case 1:
    		initTable(numProcesses, processes);
    		FCFS(processes, ganttChart);
    		printGanttChart(ganttChart);
    		printResultTable(processes);
    		break;
    	case 2:
    		initTable(numProcesses, processes);
    		SJF(processes, ganttChart);
    		printGanttChart(ganttChart);
    		printResultTable(processes);
    		break;
    	case 3:
    		initTablePrio(numProcesses, processes);
    		NPPB(processes, ganttChart);
    		printGanttChart(ganttChart);
    		printResultTablePrio(processes);
    		break;
    	case 4:
    		initTablePrio(numProcesses, processes);
    		PPB(processes, ganttChart);
    		printGanttChart(ganttChart);
    		printResultTablePrio(processes);
    		break;
    	case 5:
    		timeQuant = initTableRR(numProcesses, processes);
    		RR(processes, ganttChart, timeQuant);
    		printGanttChart(ganttChart);
    		printResultTable(processes);
    		break;
    	case 6:
    		initTable(numProcesses, processes);
    		SRTF(processes, ganttChart);
    		printGanttChart(ganttChart);
    		printResultTable(processes);
    		break;
    	case 7:
    		initTableMLQ(numProcesses, processes, mlq);
				MLQ(processes, ganttChart, mlq);
    		printGanttChart(ganttChart);
    		printResultTable(processes);
    		break;
    	case 8:
    		initTableMLFQ(numProcesses, processes, mlfq);
				MLQF(processes, ganttChart, mlfq);
    		printGanttChart(ganttChart);
    		printResultTable(processes);
    		break;
	}
    
    system("pause");
}

void displayMenu() 
{
    cout << "-----------------------------------------" << endl;
    cout << "|       CPU Scheduling Algorithms       |" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "|   1. First Come First Serve           |" << endl;
    cout << "|   2. Shortest Job First               |" << endl;
    cout << "|   3. Non-preemptive Priority Based    |" << endl;
    cout << "|   4. Preemptive Priority Based        |" << endl;
    cout << "|   5. Round Robin                      |" << endl;
    cout << "|   6. Shortest Remaining Time First    |" << endl;
    cout << "|   7. Multilevel Queue                 |" << endl;
    cout << "|   8. Multilevel Feedback Queue        |" << endl;
    cout << "|   9. Exit                             |" << endl;
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
