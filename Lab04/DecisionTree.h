#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Node
{
    string nameNode;
    vector<Node*> child;
};

struct ChildAttribute
{
    string nameChild;
    int numYes= 0;
    int numNo= 0;
    double entropy = 0;
};



struct AttributeTable
{
    string nameAttr;
    vector<ChildAttribute> table;
    double ae = 0;
    int pos =-1;
};

vector<string> classification;

bool readFile(vector<vector<string>>&,string);

//ID3
ChildAttribute createChildAttr(vector<vector<string>>,string,int);
AttributeTable createAttr(vector<vector<string>>,string,int);
vector<AttributeTable> createAttributeTable(vector<vector<string>>);
AttributeTable getBestAttr(vector<AttributeTable>);
Node* ID3Algo(vector<vector<string>>,vector<Node*>);

//Prediction
string Prediction(vector<vector<string>>,Node*,int);
void Tree2String(string &result, Node *root,int pos);