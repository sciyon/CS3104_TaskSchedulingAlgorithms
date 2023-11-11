#pragma once

#include <vector>
#include <utility>
#include <iomanip>
#include <iostream>

struct Process {
    char label;
    int arrivalTime;
    int burstTime;
    int prioNum;
    int endTime;
    int turnaroundTime;
    int waitTime;
    int remainingBurstTime;
};

int findShortestRemainingTimeProcess(const std::vector<Process>& processes, int currentTime);
int findHighestPriorityProcess(const std::vector<Process>& processes, int currentTime);
void handleIdleTime(std::vector<Process>& processes, std::vector<std::pair<char, int>>& ganttChart, unsigned& currentTime);
