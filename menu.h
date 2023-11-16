#pragma once

const int FCFS_OPTION = 1;
const int SJF_OPTION = 2;
const int NPPB_OPTION = 3;
const int PPB_OPTION = 4;
const int RR_OPTION = 5;
const int SRTF_OPTION = 6;
const int MLQ_OPTION = 7;
const int MLFQ_OPTION = 8;
const int EXIT_OPTION = 9;


#include <iostream>
#include "scheduler.h"

void menu();
void run();
void displayMenu();
int getUserChoice();
