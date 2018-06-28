#include "graph.h"
#include <fstream>

struct Data
{
	int source;
	int destination;
	int numNode;
	int algorithm;
};

bool downloadData(Data &inputData,vector<vector<bool>> &inputMatrix)
{
	int temp;
	ifstream inputFile("demo.txt");
	if(inputFile.is_open())
	{
		inputFile >> inputData.numNode;
		inputFile >> inputData.source;
		inputFile >> inputData.destination;
		inputFile >> inputData.algorithm;
		inputMatrix.resize(inputData.numNode);
		for(int i = 0 ; i < inputMatrix.size();i++)
			for(int j = 0; j < inputMatrix.size();j++)
			{
				inputFile >> temp;
				inputMatrix[i].push_back(temp);
			}
	}
}

int main(int argc, char const *argv[])
{
	vector<vector<bool>> inputMatrix;
	Data data;
	string lastResult;
	downloadData(data,inputMatrix);
	Graph graph(data.numNode,inputMatrix);
	if(data.algorithm == 1)
	{
		if(graph.DFS(data.source,data.destination))
		{
			graph.findPath(data.destination);
			lastResult = graph.getResult();
		}
		else
			lastResult = " Can not find the result !!!";
		cout << lastResult << endl;
	}
	if(data.algorithm == 0)
	{
		if(graph.BFS(data.source,data.destination))
		{
			graph.findPath(data.destination);
			lastResult = graph.getResult();
		}
		else
			lastResult = " Can not find the result !!!";
		cout << lastResult << endl;
	}
	return 0;
}