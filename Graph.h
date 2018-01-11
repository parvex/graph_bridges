#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
using namespace std;

struct Vertex {
	vector<int> edges;
	int nr;

	Vertex(int n) : nr(n) {}
	Vertex(const Vertex& v) : edges(v.edges), nr(v.nr) {}
};

class Graph
{
public:
	typedef map<int, Vertex*> vmap;

	vmap vertexes;
	vector<pair<int, int> > edgeTab;
	int amount = 0;
	Graph() {}
	Graph(int n) 
	{
		for(int i = 0 ; i < n; ++i)
			addVertex(i);
	}
	~Graph()
	{
		for(auto vpoint: vertexes)
			delete vpoint.second;
	}
	void addVertex(int n)
	{
		vmap::iterator itr = vertexes.find(n);
		if (itr == vertexes.end())
		{
			Vertex* v;
			v = new Vertex(n);
			vertexes[n] = v;
			++amount;
			return;
		}
		cout << "\nVertex already exists!";
	}


	void addEdge(int from, int to)
	{
		Vertex *f = (vertexes.find(from)->second);
		Vertex *t = (vertexes.find(to)->second);
		edgeTab.push_back(make_pair(from, to));
		f->edges.push_back(to);
		t->edges.push_back(from);
	}

	Graph(const Graph& g) : edgeTab(g.edgeTab), amount(g.amount)
	{
		for (auto vIt : g.vertexes)
			vertexes[vIt.second->nr] = new Vertex(*(vIt.second));
	}

	void deleteVertexes(int n, int y)
	{
		auto edgeIt = edgeTab.begin();
		while (edgeIt != edgeTab.end())
			if (edgeIt->first == n || edgeIt->second == n || edgeIt->first == y || edgeIt->second == y)
			{
				if (edgeIt->first != n && edgeIt->first != n && edgeIt->first != y && edgeIt->first != y)
				{
					for (auto vEdgeIt = vertexes[edgeIt->first]->edges.begin(); vEdgeIt != vertexes[edgeIt->first]->edges.end(); ++vEdgeIt)
						if (*vEdgeIt == n || *vEdgeIt == y)
						{
							vertexes[edgeIt->first]->edges.erase(vEdgeIt);
							break;
						}
				}
				else if (edgeIt->second != y && edgeIt->second != y && edgeIt->second != y && edgeIt->second != y)
				{
					for (auto vEdgeIt = vertexes[edgeIt->second]->edges.begin(); vEdgeIt != vertexes[edgeIt->second]->edges.end(); ++vEdgeIt)
						if (*vEdgeIt == n || *vEdgeIt == y)
						{
							vertexes[edgeIt->second]->edges.erase(vEdgeIt);
							break;
						}
				}
				edgeIt = edgeTab.erase(edgeIt);
			}
			else edgeIt++;
			vertexes.erase(n);
			vertexes.erase(y);
			amount -= 2;
	}

};



bool isGraphConnected(Graph& g)
{
	if (g.amount == 0) return true;
	queue<int> queue;
	bool* visited = new bool[g.amount + 2]{};
	int visamount = 0;
	queue.push((*g.vertexes.begin()).second->nr);
	visited[(*g.vertexes.begin()).second->nr] = true;
	++visamount;
	int nr;
	while (queue.size())
	{
		nr = queue.front();
		queue.pop();
		for (int& v : g.vertexes[nr]->edges)
		{
			if (visited[v] == true) continue;
			queue.push(v);
			visited[v] = true;
			++visamount;
		}
	}
	delete visited;
	return visamount == g.amount;
}

bool isEdgeBridge(Graph g, const pair<int, int>& edge)
{
	g.deleteVertexes(edge.first, edge.second);
	return !isGraphConnected(g);
}

