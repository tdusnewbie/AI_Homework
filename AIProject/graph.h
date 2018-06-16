#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

struct Node
{
	int value;
	int parent;
};

class Graph
{
private:
	int numNode;
	vector<vector<bool>> matrix;
	list<Node> path;
	string result;
	int cost;
public:
	Graph(int,vector<vector<bool>>);
	~Graph();
	void printMatrix();
	string getResult();
	int getCost();
	void findPath(int);
	bool BFS(int,int);
	bool DFS(int,int);
};