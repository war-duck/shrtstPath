#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <Windows.h>
#define LAB_SIZE 8

typedef struct a
{
    int start;
    int dest;
    std::string lab_str;
    double (*lab)[LAB_SIZE*LAB_SIZE];
}* result;

void create_lab (double lab[LAB_SIZE*LAB_SIZE][LAB_SIZE*LAB_SIZE], std::string *lab_str, int start, int end);
void add_start_end (std::string *lab_str, int* start, int* end);
void add_path_anim (std::string* lab_str, std::vector<int> path);
result create_paths();

