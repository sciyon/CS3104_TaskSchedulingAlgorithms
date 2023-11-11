#pragma once

const int SJF_OPTION = 1;
const int PPB_OPTION = 2;
const int SRTF_OPTION = 3;
const int MLFQ_OPTION = 4;
const int EXIT_OPTION = 5;


#include <iostream>
#include "scheduler.h"

void menu();
void run();
void displayMenu();
int getUserChoice();