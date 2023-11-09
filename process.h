#pragma once

#include <vector>
#include <utility>
#include <iomanip>
#include <iostream>

struct Process {
    char label;
    int arrivalTime;
    int burstTime;
    int endTime;
    int turnaroundTime;
    int waitTime;
    int remainingBurstTime;
};

void initTable(int numProcesses, std::vector<Process>& processes);
void printTable(std::vector<Process>& processes);
void printResultTable(const std::vector<Process>& processes);
bool compareProcesses(const Process& a, const Process& b);
int findShortestRemainingTimeProcess(const std::vector<Process>& processes, int currentTime);
void handleIdleTime(std::vector<Process>& processes, std::vector<std::pair<char, int>>& ganttChart, unsigned& currentTime);
