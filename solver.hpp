#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

#include "create_lab.hpp"

std::pair<std::vector<int>, double> shrtstPath(int start, int dest, std::vector<std::vector<double>>& graph, std::set<int> visited);
int solve(int numberOfNodes, int start, int dest, result lab_data);
