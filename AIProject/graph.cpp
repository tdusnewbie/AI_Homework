#include "graph.h"

Graph::Graph(int num,vector<vector<bool>> inputMatrix)
{
	numNode = num;
	matrix = inputMatrix;
	result = "";
	cost = 0;
}

Graph::~Graph()
{

}

string Graph::getResult()
{
	return result;
}

int Graph::getCost()
{
	return cost;
}

bool Graph::BFS(int source,int destination)
{
	if(source == destination)
	{
		result = destination;
		return true;
	}
	bool *existed = new bool [numNode];
	for(int i = 0; i < numNode;i++)
		existed[i] = false;
	list<int> queue;
	Node node;
	queue.push_back(source);
	existed[source] = true;
	while(!queue.empty())
	{
		source = queue.front();
		queue.pop_front();
		for(int i = 0; i < numNode;i++)
			if(matrix[source][i] == 1 && existed[i] == false)
			{
				node.parent = source;
				node.value = i;
				path.push_back(node) ;
				queue.push_back(i);
				existed[i] = true;
				if(i == destination) return true;
			}
	}
	if(path.empty())
		return false;
}

bool Graph::DFS(int source, int destination)
{
	if(source == destination)
	{
		result = destination;
		return true;
	}
	bool *existed = new bool [numNode];
	for(int i = 0; i < numNode;i++)
		existed[i] = false;
	list<int> stack;
	Node node;
	stack.push_back(source);
	existed[source] = true;
	while(!stack.empty())
	{
		source = stack.back();
		stack.pop_back();
		for(int i = numNode; i >= 0;i--)
			if(matrix[source][i] == 1 && existed[i] == false)
			{
				node.parent = source;
				node.value = i;
				path.push_back(node) ;
				stack.push_back(i);
				existed[i] = true;
				if(i == destination) return true;
			}
	}
	if(path.empty())
		return false;
}

void Graph::findPath(int destination)
{
	Node node;
	while(!path.empty())
	{
		node = path.back();
		if(destination == node.value)
		{
			cost ++;
			destination = node.parent;
			result = '-' + to_string(node.value) + result;
			if(path.size() == 1)
				result = to_string(node.parent) + result;
		}
		path.pop_back();
	}
}

/*int main()
{
	int num;
	string temp;
	cout << "Nhap so node : ";
	cin >> num;
	Graph graph(num);
	if(graph.DFS(0,5))
	{
		graph.findPath(5);
		temp = graph.getResult();
	}
	cout << "Duong di can tim la : "<< temp << endl;
	cout << "So chi phi la " << graph.getCost() << endl;
	return 0;
}
*/
/*
0
Print 0
Push 1 => (1,0)
Pop0 

1
Print 1
Push 2 => (2,1)
Push 3 => (3,1)
Push 4 => (4,1)
Pop 1

2 3 4
Print 2
Pop 2

3 4
Print 3 
Push 5 => (5,3)
Pop 3

4 5
Print 4 
Pop 4

5
Print 5
Pop 5
=>
*/

/*
0: 1
1: 2 3 4
2: 
3: 4 5
4: 
5: 2
*/