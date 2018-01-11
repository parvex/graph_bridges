#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
using namespace std;
#include "Graph.h"


int main()
{
	int a, b, c;
	Graph g;
	cin >> c;
	for (int i = 0; i < c; ++i)
		g.addVertex(i);
	while(cin >> a)
	{
		cin >> b;
		g.addEdge(a, b);
	}
	if (g.amount == 0) return 0;
	vector<pair<int,int>> bridges;
	for (auto edge : g.edgeTab)
		if (isEdgeBridge(g, edge))
			bridges.push_back(edge);

	for (auto it : bridges)
	{
		cout << it.first << it.second << endl;
	}
	cin >> a;
	return 0;
}