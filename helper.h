#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include "process_management.h"

void initTable(int numProcesses, std::vector<Process>& processes);
void initTablePrio(int numProcesses, std::vector<Process>& processes);
void printTable(std::vector<Process>& processes);
void printTablePrio(std::vector<Process>& processes);
void printResultTable(const std::vector<Process>& processes);
void printResultTablePrio(const std::vector<Process>& processes);
void printGanttChart(const std::vector<std::pair<char, int>>& ganttChart);
