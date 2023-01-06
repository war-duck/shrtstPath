#pragma once
#include <cstdio>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#define LAB_SIZE 10

typedef struct a
{
    int start;
    int dest;
    std::string lab_str;
    double (*lab)[LAB_SIZE*LAB_SIZE];
}* result;

void create_lab (double lab[LAB_SIZE*LAB_SIZE][LAB_SIZE*LAB_SIZE], std::string *lab_str, int start, int end);
void print_lab (double lab[LAB_SIZE*LAB_SIZE][LAB_SIZE*LAB_SIZE]);
void add_start_end (std::string *lab_str, int* start, int* end);

result create_paths();

