#include "solver.hpp"
using namespace std;
// struct
// {
// 	vector< vector<int> > paths;
// 	vector<double> path_lengths;
// 	set<int> start_neigh;
// 	set<int> end_neigh;
// 	int path_depth;
// 	int solution_no = -1;
// } solutions;

// pair<vector<int>, double> shrtstPath(int start, int dest, vector<vector<double>>& graph, set<int> visited)
// {
// 	if (graph[start][dest] != -1) // jest juz bezposrednie polaczenie z koncem
// 	{
// 		++solutions.solution_no;
// 		solutions.paths.insert(solutions.paths.begin(), vector<int>());
// 		solutions.path_depth = 1;
// 		cout << start << "znaleziono \t";
// 		cout << solutions.path_depth << '\t' << solutions.solution_no << '\n';
// 		return pair<vector<int>, double>(vector<int>(1,dest), graph[start][dest]);
// 	}
// 	visited.insert(start); // do odwiedzonych wierzcholkow dodajemy obecny
// 	pair<vector<int>, double> minResult (vector<int>(), double(~(unsigned int)0)), currentResult;
// 	for (short opt = 0; opt < graph[start].size(); ++opt) // dla punktu startowego
// 	{
// 		if (graph[start][opt] != -1 && visited.count(opt) == false) // sprawdzamy dostepne polaczenia
// 		{
// 			//cout << string(visited.size(), '\t') << "Wywolywanie: " << opt << '\n';
// 			currentResult = shrtstPath(opt, dest, graph, visited); // dla kazdego sasiada sprawdzamy jego sasiadow
// 				// solutions.paths.insert(solutions.paths.end(), currentResult.first);
// 				// solutions.path_lengths.insert(solutions.path_lengths.end(), currentResult.second);
// 			//cout << string(visited.size(), '\t') << "Wynik: " << currentResult.second << endl;
// 			if (currentResult.first.size() == solutions.path_depth && solutions.solution_no != -1)
// 			{
// 				cout << start << "\t\t";
// 				cout << ++solutions.path_depth << '\t' << solutions.solution_no << '\n';
// 				solutions.paths[solutions.solution_no].insert(solutions.paths[solutions.solution_no].begin() + solutions.path_depth -1, start);
// 				cout << "inserted";
// 			}
// 			if (currentResult.second+graph[start][opt] < minResult.second) // jesli obecna dlugosc < dotychczasowa minimalna
// 			{
// 				minResult = currentResult;
// 				minResult.second += graph[start][opt];
// 				minResult.first.insert(minResult.first.begin(), opt);

// 			}
			

// 		}
// 	}
// 	return minResult;
// }

pair<vector<int>, double> shrtstPath(int start, int dest, vector<vector<double>>& graph, set<int> visited)
{
	if (graph[start][dest] != -1) // jest juz bezposrednie polaczenie z koncem
		return pair<vector<int>, double>(vector<int>(1,dest), graph[start][dest]);
	visited.insert(start); // do odwiedzonych wierzcholkow dodajemy obecny
	pair<vector<int>, double> minResult (vector<int>(), double(~(unsigned int)0)), currentResult;
	for (short opt = 0; opt < graph[start].size(); ++opt) // dla punktu startowego
	{
		if (graph[start][opt] != -1 && visited.count(opt) == false) // sprawdzamy dostepne polaczenia
		{
			//cout << string(visited.size(), '\t') << "Wywolywanie: " << opt << '\n';
			currentResult = shrtstPath(opt, dest, graph, visited); // dla kazdego sasiada sprawdzamy jego sasiadow
				// solutions.paths.insert(solutions.paths.end(), currentResult.first);
				// solutions.path_lengths.insert(solutions.path_lengths.end(), currentResult.second);
			//cout << string(visited.size(), '\t') << "Wynik: " << currentResult.second << endl;
			if (currentResult.second+graph[start][opt] < minResult.second) // jesli obecna dlugosc < dotychczasowa minimalna
			{
				minResult = currentResult;
				minResult.second += graph[start][opt];
				minResult.first.insert(minResult.first.begin(), opt);
			}
		}
	}
	return minResult;
}

int solve(int numberOfNodes, int start, int dest, result lab_data)
{
	std::cout << lab_data->lab_str; 
	vector<vector<double>> graph;
	ifstream file;
	
	graph.push_back(vector<double>());
	for (short x = 0; x < numberOfNodes; ++x)
		graph[0].push_back(-1.0); // tworzymy pierwszy rzad
	for (short x = 1; x < numberOfNodes; ++x) // reszta rzedow to kopia pierwszego
		graph.push_back(graph[0]); // jest jakis problem z vector.resize()
	for (int i = 0; i < LAB_SIZE*LAB_SIZE; ++i)
		for (int j = 0; j < LAB_SIZE*LAB_SIZE; ++j)
			if ((*(lab_data->lab+i))[j])
			{
				graph[i][j] = (*(lab_data->lab+i))[j]; // wypelniamy graph danymi z pliku
				graph[j][i] = (*(lab_data->lab+i))[j];
			}
	short ctr = 0;
	// cout << '\t';
	// for (short x = 0; x < numberOfNodes; ++x){cout.width(8);cout << x;} 
	// for (auto i : graph)
	// {
	// 	cout << "\n\n";
	// 	cout.width(8);
	// 	cout << ctr++;
	// 	for (auto j : i)
	// 	{
	// 		cout.width(8);
	// 		cout << j;
	// 	}
	// }
	pair <vector<int>, double> path;
	path = shrtstPath(start, dest, graph, set<int>());
	path.first.insert(path.first.begin(), start);
	if (path.second != double(~(unsigned int)0))
	{
		cout << "dlugosc: " << path.second << endl << "sciezka: ";
		if (!path.first.empty())
			for (auto i : path.first)
				cout << i << " ";
		else cout << "bezposrednie polaczenie";
	}
	else cout << "brak polaczenia :(";
	cout << '\n';
	// cout << "a teraz sciezki: \n";
	// for (auto i : solutions.paths)
	// {
	// 	for (auto j : i)
	// 	{
	// 		cout << j << " ";
	// 	}
	// 	cout << '\n';
	// }
	return 0;
}
