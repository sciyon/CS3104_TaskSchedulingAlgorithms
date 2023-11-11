#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include <conio.h>
#include "process_management.h"

void menu();
void run(int);
void SJF(std::vector<Process>& processes, std::vector<std::pair<char, int>>& ganttChart);
void PPB(std::vector<Process>& processes, std::vector<std::pair<char, int>>& ganttChart);
void SRTF(std::vector<Process>& processes, std::vector<std::pair<char, int>>& ganttChart);
