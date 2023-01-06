#pragma once
#include <fstream>
#include <set>

#include "lab.hpp"

std::pair<std::vector<int>, double> shrtstPath(int start, int dest, std::vector<std::vector<double>>& graph, std::set<int> visited);
std::vector<int> solve(int numberOfNodes, int start, int dest, result lab_data);
