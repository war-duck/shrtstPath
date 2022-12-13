#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

pair<vector<int>, unsigned int> shrtstPath(int start, int dest, vector<vector<int>>& graph, set<int> visited)
{
	if (graph[start][dest] != -1)
		return pair<vector<int>, unsigned int>(vector<int>(), graph[start][dest]);
	
	visited.insert(start); // do odwiedzonych wierzcholkow dodajemy obecny
	pair<vector<int>, unsigned int> minResult (vector<int>(), INT_MAX), currentResult;
	for (short opt = 0; opt < graph[start].size(); ++opt) // dla punktu startowego
	{
		if (graph[start][opt] != -1 && visited.count(opt) == false) // sprawdzamy dostepne polaczenia
		{
			//cout << "Wywolywanie: " << opt;
			currentResult = shrtstPath(opt, dest, graph, visited); // dla kazdego sasiada sprawdzamy jego sasiadow
			//cout << " wynik: " << currentResult.second << endl;
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

int main()
{
	int numberOfNodes, start, dest, weight, graphNo;
	vector<vector<int>> graph;
	ifstream file;
	
	while (cout << "wybierz graf [1/2/3]: " && cin >> graphNo && (graphNo < 1 || graphNo > 3));
	file.open("graph"+to_string(graphNo)+".txt");
	file >> numberOfNodes;
	graph.push_back(vector<int>());
	for (short x = 0; x < numberOfNodes; ++x)
		graph[0].push_back(-1); // tworzymy pierwszy rzad
	for (short x = 1; x < numberOfNodes; ++x) // reszta rzedow to kopia pierwszego
		graph.push_back(graph[0]); // jest jakis problem z vector.resize()
	while (file >> weight && file >> start && file >> dest)
	{
		graph[start][dest] = weight; // wypelniamy graph danymi z pliku
		graph[dest][start] = weight;
	}
	short ctr = 0;
	cout << "  ";
	for (short x = 0; x < numberOfNodes; ++x){cout.width(4);cout << x;} 
	for (auto i : graph)
	{
		cout << "\n\n";
		cout.width(3);
		cout << ctr++;
		for (auto j : i)
		{
			cout.width(3);
			cout << j << " ";
		}
	}
	pair <vector<int>, int> path;
	cout << "\nskad: "; cin >> start;
	cout << "dokad: "; cin >> dest;
	if(start < numberOfNodes && dest < numberOfNodes)
		path = shrtstPath(start, dest, graph, set<int>());
	cout << "dlugosc: " << path.second << endl << "sciezka: ";
	if (!path.first.empty())
		for (auto i : path.first)
			cout << i << " ";
	else cout << "bezposrednie polaczenie";
	return 0;
}
