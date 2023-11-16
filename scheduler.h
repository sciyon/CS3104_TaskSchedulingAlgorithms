#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include <conio.h>
#include <queue>
#include <algorithm>
#include "process_management.h"

void menu();
void run(int);
void FCFS(std::vector<Process>& processes, std::vector<std::pair<char, int>>& ganttChart);
void SJF(std::vector<Process>& processes, std::vector<std::pair<char, int>>& ganttChart);
void NPPB(std::vector<Process>& processes, std::vector<std::pair<char, int>>& ganttChart);
void PPB(std::vector<Process>& processes, std::vector<std::pair<char, int>>& ganttChart);
void RR(std::vector<Process>& processes, std::vector<std::pair<char, int>>& ganttChart, int timeQuantum);
void SRTF(std::vector<Process>& processes, std::vector<std::pair<char, int>>& ganttChart);
void MLQ(std::vector<Process>& processes, std::vector<std::pair<char, int>>& ganttChart, std::vector<int>& mlq);
void MLQF(std::vector<Process>& processes, std::vector<std::pair<char, int>>& ganttChart, std::vector<int>& mlfq);
